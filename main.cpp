#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

#include "Input.h"
#include "ConstructionEquipment.h"
#include "DerivedEquipment.h"
#include "EquipmentSpecs.h"
#include "Factories.h"
#include "EquipmentRegistry.h"
#include "EquipmentManager.h"

void menuAddEquipment(EquipmentManager& manager) {
    while (true) {
        clearScreen();
        std::cout << "============================================================\n"
                  << "   ДОБАВЛЕНИЕ ТЕХНИКИ: ВЫБОР ПАТТЕРНА КОНСТРУИРОВАНИЯ       \n"
                  << "============================================================\n"
                  << "1. Паттерн 1: «Фабричный метод» (Factory Method по умолчанию)\n"
                  << "2. Паттерн 2: «Фабричный метод с аргументами» (Иерархия Spec)\n"
                  << "3. Паттерн 2 (вариация): «Фабрика с va_list» (Переменное число аргументов)\n"
                  << "4. Паттерн 3: «Фабричный конструктор» (Динамический реестр типов)\n"
                  << "5. Паттерн 5: «Полиморфное копирование» (Клонирование существующей)\n"
                  << "0. Вернуться в главное меню\n"
                  << "------------------------------------------------------------\n";

        int choice = readInt(std::cin, "Выберите способ конструирования (0-5): ", 0, 5);
        if (choice == 0) return;

        if (choice == 1) {

            std::cout << "\n--- Паттерн 1: Фабричный метод ---\n"
                      << "1. Экскаватор\n"
                      << "2. Башенный кран\n"
                      << "3. Бульдозер\n"
                      << "4. Бетоносмеситель\n"
                      << "5. Самосвал\n";
            int typeChoice = readInt(std::cin, "Выберите тип техники (1-5): ", 1, 5);
            auto item = SimpleEquipmentFactory::create(static_cast<EquipmentType>(typeChoice));
            if (item) {
                int newId = manager.generateNextId();
                item->setId(newId);
                std::cout << "Сконструирован объект типа: " << item->getTypeName() << "\n";
                std::string site = readLine(std::cin, "Введите название строительного объекта: ");
                item->setSiteName(site);
                manager.addEquipment(std::move(item));
                std::cout << "[OK] Техника успешно добавлена в компанию под ID " << newId << "!\n";
            }
            pauseScreen();
        }
        else if (choice == 2) {

            std::cout << "\n--- Паттерн 2: Фабрика с иерархией спецификаций (Spec) ---\n"
                      << "1. Экскаватор\n"
                      << "2. Башенный кран\n"
                      << "3. Бульдозер\n"
                      << "4. Бетоносмеситель\n"
                      << "5. Самосвал\n";
            int typeChoice = readInt(std::cin, "Выберите тип техники (1-5): ", 1, 5);

            int id = manager.generateNextId();
            std::string model = readLine(std::cin, "Марка и модель: ");
            std::string reg = readLine(std::cin, "Гос. регистрационный номер: ");
            std::string site = readLine(std::cin, "Строительный объект: ");
            double rate = readDouble(std::cin, "Почасовая ставка (руб/ч): ", 10.0, 10000.0);
            double hours = readDouble(std::cin, "Отработано часов: ", 0.0, 10000.0);

            std::unique_ptr<ConstructionEquipment> item = nullptr;

            if (typeChoice == 1) {
                ExcavatorSpec spec;
                spec.id = id; spec.model = model; spec.regNumber = reg;
                spec.siteName = site; spec.hourlyRate = rate; spec.hoursWorked = hours;
                spec.bucketCapacity = readDouble(std::cin, "Объем ковша (м³): ", 0.1, 20.0);
                spec.maxDiggingDepth = readDouble(std::cin, "Макс. глубина копания (м): ", 0.5, 30.0);
                item = ParameterizedEquipmentFactory::create(spec);
            }
            else if (typeChoice == 2) {
                TowerCraneSpec spec;
                spec.id = id; spec.model = model; spec.regNumber = reg;
                spec.siteName = site; spec.hourlyRate = rate; spec.hoursWorked = hours;
                spec.boomReach = readDouble(std::cin, "Вылет стрелы (м): ", 10.0, 150.0);
                spec.maxCapacity = readDouble(std::cin, "Грузоподъемность (т): ", 1.0, 100.0);
                item = ParameterizedEquipmentFactory::create(spec);
            }
            else if (typeChoice == 3) {
                BulldozerSpec spec;
                spec.id = id; spec.model = model; spec.regNumber = reg;
                spec.siteName = site; spec.hourlyRate = rate; spec.hoursWorked = hours;
                spec.bladeWidth = readDouble(std::cin, "Ширина отвала (м): ", 1.0, 10.0);
                spec.enginePowerHp = readDouble(std::cin, "Мощность двигателя (л.с.): ", 50.0, 1500.0);
                item = ParameterizedEquipmentFactory::create(spec);
            }
            else if (typeChoice == 4) {
                ConcreteMixerSpec spec;
                spec.id = id; spec.model = model; spec.regNumber = reg;
                spec.siteName = site; spec.hourlyRate = rate; spec.hoursWorked = hours;
                spec.drumVolume = readDouble(std::cin, "Объем смесительного барабана (м³): ", 1.0, 30.0);
                spec.waterTankCapacity = readDouble(std::cin, "Емкость бака для воды (л): ", 50.0, 3000.0);
                item = ParameterizedEquipmentFactory::create(spec);
            }
            else if (typeChoice == 5) {
                DumpTruckSpec spec;
                spec.id = id; spec.model = model; spec.regNumber = reg;
                spec.siteName = site; spec.hourlyRate = rate; spec.hoursWorked = hours;
                spec.payloadCapacity = readDouble(std::cin, "Грузоподъемность кузова (т): ", 1.0, 200.0);
                spec.bodyVolume = readDouble(std::cin, "Объем кузова (м³): ", 1.0, 100.0);
                item = ParameterizedEquipmentFactory::create(spec);
            }

            if (item) {
                manager.addEquipment(std::move(item));
                std::cout << "[OK] Объект сконструирован через Parameterized Factory и сохранен!\n";
            }
            pauseScreen();
        }
        else if (choice == 3) {

            std::cout << "\n--- Паттерн 2 (вариация): Фабрика с va_list (Пример №2 методички) ---\n"
                      << "1. Экскаватор (автоматические параметры ковша)\n"
                      << "2. Башенный кран (автоматические параметры стрелы)\n"
                      << "3. Бульдозер (автоматические параметры отвала)\n"
                      << "4. Бетоносмеситель (автоматические параметры барабана)\n"
                      << "5. Самосвал (автоматические параметры кузова)\n";
            int typeChoice = readInt(std::cin, "Выберите тип техники (1-5): ", 1, 5);

            int id = manager.generateNextId();
            std::string model = readLine(std::cin, "Модель: ");
            std::string reg = readLine(std::cin, "Гос. номер: ");
            std::string site = readLine(std::cin, "Объект: ");
            double rate = readDouble(std::cin, "Ставка (руб/ч): ", 10.0, 5000.0);
            double hours = readDouble(std::cin, "Часы: ", 0.0, 5000.0);

            std::unique_ptr<ConstructionEquipment> item = nullptr;
            if (typeChoice == 1) {
                item = VariadicEquipmentFactory::createWithArgs(
                    EquipmentType::EXCAVATOR, id, model.c_str(), reg.c_str(), site.c_str(),
                    rate, hours, 1.4, 6.8
                );
            } else if (typeChoice == 2) {
                item = VariadicEquipmentFactory::createWithArgs(
                    EquipmentType::TOWER_CRANE, id, model.c_str(), reg.c_str(), site.c_str(),
                    rate, hours, 75.0, 14.0
                );
            } else if (typeChoice == 3) {
                item = VariadicEquipmentFactory::createWithArgs(
                    EquipmentType::BULLDOZER, id, model.c_str(), reg.c_str(), site.c_str(),
                    rate, hours, 4.1, 220.0
                );
            } else if (typeChoice == 4) {
                item = VariadicEquipmentFactory::createWithArgs(
                    EquipmentType::CONCRETE_MIXER, id, model.c_str(), reg.c_str(), site.c_str(),
                    rate, hours, 12.0, 900.0
                );
            } else if (typeChoice == 5) {
                item = VariadicEquipmentFactory::createWithArgs(
                    EquipmentType::DUMP_TRUCK, id, model.c_str(), reg.c_str(), site.c_str(),
                    rate, hours, 28.0, 18.0
                );
            }

            if (item) {
                manager.addEquipment(std::move(item));
                std::cout << "[OK] Объект успешно сконструирован через Variadic Factory (va_list)!\n";
            }
            pauseScreen();
        }
        else if (choice == 4) {

            std::cout << "\n--- Паттерн 3: Динамический реестр типов (EquipmentRegistry) ---\n";
            const auto& regEntries = EquipmentRegistry::instance().getEntries();
            std::cout << "Зарегистрированные в реестре типы техники:\n";
            for (const auto& entry : regEntries) {
                std::cout << "  [" << entry.first << "] " << entry.second.typeName << "\n";
            }

            int typeId = readInt(std::cin, "Введите идентификатор типа из реестра (1-5): ", 1, 5);
            auto item = EquipmentRegistry::instance().create(typeId);
            if (item) {
                int newId = manager.generateNextId();
                item->setId(newId);
                std::string site = readLine(std::cin, "Введите строительный объект для техники: ");
                item->setSiteName(site);
                manager.addEquipment(std::move(item));
                std::cout << "[OK] Объект сконструирован через динамический реестр типов (ID " << newId << ")!\n";
            } else {
                std::cout << "Ошибка: тип не зарегистрирован в реестре.\n";
            }
            pauseScreen();
        }
        else if (choice == 5) {

            if (manager.getCount() == 0) {
                std::cout << "Ошибка: база пуста, нет объектов для копирования.\n";
                pauseScreen();
                continue;
            }
            manager.displayAll();
            int id = readInt(std::cin, "Введите ID техники, которую нужно клонировать: ", 1, 999999);
            manager.demonstratePolymorphicCloning(id);
            pauseScreen();
        }
    }
}

void menuEditEquipment(EquipmentManager& manager) {
    if (manager.getCount() == 0) {
        std::cout << "\nБаза строительной техники пуста.\n";
        pauseScreen();
        return;
    }

    manager.displayAll();
    int id = readInt(std::cin, "Введите ID техники для редактирования: ", 1, 999999);
    ConstructionEquipment* item = manager.findEquipmentById(id);
    if (!item) {
        std::cout << "Ошибка: техника с инвентарным номером " << id << " не найдена.\n";
        pauseScreen();
        return;
    }

    std::cout << "\nТекущие параметры объекта:\n";
    item->displayDetails();

    std::cout << "\n--- Что вы хотите изменить? ---\n"
              << "1. Модель\n"
              << "2. Гос. регистрационный номер\n"
              << "3. Строительный объект\n"
              << "4. Почасовую ставку\n"
              << "5. Отработанные часы\n"
              << "6. Статус занятости\n"
              << "7. Специальные параметры типа\n"
              << "0. Отмена\n";
    int editChoice = readInt(std::cin, "Ваш выбор: ", 0, 7);

    switch (editChoice) {
    case 1: {
        std::string m = readLine(std::cin, "Новая модель: ");
        item->setModel(m);
        std::cout << "[OK] Модель обновлена.\n";
        break;
    }
    case 2: {
        std::string r = readLine(std::cin, "Новый гос. номер: ");
        item->setRegNumber(r);
        std::cout << "[OK] Гос. номер обновлен.\n";
        break;
    }
    case 3: {
        std::string s = readLine(std::cin, "Новый объект: ");
        item->setSiteName(s);
        std::cout << "[OK] Строительный объект обновлен.\n";
        break;
    }
    case 4: {
        double rate = readDouble(std::cin, "Новая почасовая ставка (руб/ч): ", 1.0, 50000.0);
        item->setHourlyRate(rate);
        std::cout << "[OK] Ставка обновлена.\n";
        break;
    }
    case 5: {
        double hours = readDouble(std::cin, "Новое кол-во часов: ", 0.0, 50000.0);
        item->setHoursWorked(hours);
        std::cout << "[OK] Часы обновлены.\n";
        break;
    }
    case 6: {
        std::cout << "1. В работе\n2. На ТО\n3. В резерве\n4. Доступна\n";
        int st = readInt(std::cin, "Новый статус (1-4): ", 1, 4);
        item->setStatus(static_cast<EquipmentStatus>(st));
        std::cout << "[OK] Статус обновлен.\n";
        break;
    }
    case 7: {

        if (auto* exc = dynamic_cast<Excavator*>(item)) {
            exc->setBucketCapacity(readDouble(std::cin, "Новый объем ковша (м³): ", 0.1, 25.0));
            exc->setMaxDiggingDepth(readDouble(std::cin, "Новая глубина копания (м): ", 0.5, 30.0));
        } else if (auto* crane = dynamic_cast<TowerCrane*>(item)) {
            crane->setBoomReach(readDouble(std::cin, "Новый вылет стрелы (м): ", 5.0, 150.0));
            crane->setMaxCapacity(readDouble(std::cin, "Новая грузоподъемность (т): ", 0.5, 150.0));
        } else if (auto* bull = dynamic_cast<Bulldozer*>(item)) {
            bull->setBladeWidth(readDouble(std::cin, "Новая ширина отвала (м): ", 1.0, 15.0));
            bull->setEnginePowerHp(readDouble(std::cin, "Новая мощность двигателя (л.с.): ", 30.0, 2000.0));
        } else if (auto* mix = dynamic_cast<ConcreteMixer*>(item)) {
            mix->setDrumVolume(readDouble(std::cin, "Новый объем барабана (м³): ", 1.0, 40.0));
            mix->setWaterTankCapacity(readDouble(std::cin, "Новая емкость бака для воды (л): ", 50.0, 5000.0));
        } else if (auto* dump = dynamic_cast<DumpTruck*>(item)) {
            dump->setPayloadCapacity(readDouble(std::cin, "Новая грузоподъемность (т): ", 1.0, 300.0));
            dump->setBodyVolume(readDouble(std::cin, "Новый объем кузова (м³): ", 1.0, 150.0));
        }
        std::cout << "[OK] Специальные параметры успешно обновлены.\n";
        break;
    }
    default:
        std::cout << "Редактирование отменено.\n";
        break;
    }

    pauseScreen();
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    Excavator::Register();
    TowerCrane::Register();
    Bulldozer::Register();
    ConcreteMixer::Register();
    DumpTruck::Register();

    EquipmentManager manager;
    manager.seedDemoData();

    bool running = true;
    while (running) {
        clearScreen();
        std::cout << "========================================================================\n"
                  << "        ЛАБОРАТОРНАЯ РАБОТА №6. ПАТТЕРНЫ ПРОЕКТИРОВАНИЯ В С++           \n"
                  << " Вариант 10: Учет занятости строительной техники в строительной компании\n"
                  << "========================================================================\n"
                  << "[1] Просмотр парка техники компании (Таблица)\n"
                  << "[2] Добавить единицу техники (Паттерны конструирования)\n"
                  << "[3] Удалить технику из базы по инвентарному номеру (ID)\n"
                  << "[4] Редактировать данные строительной техники по ID\n"
                  << "[5] Просмотреть подробные характеристики техники по ID\n"
                  << "[6] Паттерн 4: «Полиморфная фабрика» (Создание навесного оборудования)\n"
                  << "[7] Паттерн 5: «Полиморфное копирование» (CRTP-клон техники)\n"
                  << "[8] Экспорт базы техники в файл отчета\n"
                  << "[9] Перезагрузить демонстрационный набор данных (5 видов техники)\n"
                  << "[0] Выход из программы\n"
                  << "========================================================================\n";

        int mainChoice = readInt(std::cin, "Выберите пункт меню (0-9): ", 0, 9);

        switch (mainChoice) {
        case 1:
            clearScreen();
            std::cout << "--- РЕЕСТР ЗАНЯТОСТИ СТРОИТЕЛЬНОЙ ТЕХНИКИ В КОМПАНИИ ---\n";
            manager.displayAll();
            pauseScreen();
            break;

        case 2:
            menuAddEquipment(manager);
            break;

        case 3: {
            clearScreen();
            if (manager.getCount() == 0) {
                std::cout << "База пуста, удалять нечего.\n";
            } else {
                manager.displayAll();
                int id = readInt(std::cin, "Введите инвентарный номер (ID) для удаления: ", 1, 999999);
                if (askYesNo(std::cin, "Вы уверены, что хотите списать данную технику? (y/n): ")) {
                    if (manager.removeEquipmentById(id)) {
                        std::cout << "[OK] Техника с ID " << id << " успешно списана из базы.\n";
                    } else {
                        std::cout << "Ошибка: техника с ID " << id << " не найдена.\n";
                    }
                } else {
                    std::cout << "Списание отменено пользователем.\n";
                }
            }
            pauseScreen();
            break;
        }

        case 4:
            clearScreen();
            menuEditEquipment(manager);
            break;

        case 5: {
            clearScreen();
            if (manager.getCount() == 0) {
                std::cout << "База строительной техники пуста.\n";
            } else {
                manager.displayAll();
                int id = readInt(std::cin, "Введите ID техники для детального просмотра: ", 1, 999999);
                manager.displayDetailedById(id);
            }
            pauseScreen();
            break;
        }

        case 6: {
            clearScreen();
            if (manager.getCount() == 0) {
                std::cout << "База пуста. Сначала добавьте технику.\n";
            } else {
                manager.displayAll();
                int id = readInt(std::cin, "Введите ID техники для создания навесного оборудования: ", 1, 999999);
                manager.demonstratePolymorphicFactory(id);
            }
            pauseScreen();
            break;
        }

        case 7: {
            clearScreen();
            if (manager.getCount() == 0) {
                std::cout << "База пуста. Нечего клонировать.\n";
            } else {
                manager.displayAll();
                int id = readInt(std::cin, "Введите ID техники для создания полиморфного CRTP-клона: ", 1, 999999);
                manager.demonstratePolymorphicCloning(id);
            }
            pauseScreen();
            break;
        }

        case 8: {
            clearScreen();
            std::string filename = readLine(std::cin, "Введите имя файла для экспорта (по умолчанию 'equipment_report.txt'): ");
            if (filename.empty()) filename = "equipment_report.txt";
            if (manager.exportToFile(filename)) {
                std::cout << "[OK] Отчет успешно сохранен в файл: " << filename << "\n";
            } else {
                std::cout << "Ошибка: не удалось открыть файл для записи.\n";
            }
            pauseScreen();
            break;
        }

        case 9: {
            clearScreen();
            if (askYesNo(std::cin, "Перезагрузить базу демонстрационными данными? Текущие данные будут сброшены (y/n): ")) {
                manager.seedDemoData();
                std::cout << "[OK] Демонстрационный набор данных успешно загружен (5 видов техники).\n";
            }
            pauseScreen();
            break;
        }

        case 0:
            if (askYesNo(std::cin, "Вы действительно хотите выйти из программы? (y/n): ")) {
                running = false;
                std::cout << "\nПрограмма завершена. До свидания!\n";
            }
            break;
        }
    }

    return 0;
}
