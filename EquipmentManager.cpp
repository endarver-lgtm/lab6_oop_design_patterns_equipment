#include "EquipmentManager.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

void EquipmentManager::addEquipment(std::unique_ptr<ConstructionEquipment> item) {
    if (!item) return;
    equipmentList_.push_back(std::move(item));
}

bool EquipmentManager::removeEquipmentById(int id) {
    auto it = std::remove_if(equipmentList_.begin(), equipmentList_.end(),
        [id](const std::unique_ptr<ConstructionEquipment>& item) {
            return item && item->getId() == id;
        });
    if (it != equipmentList_.end()) {
        equipmentList_.erase(it, equipmentList_.end());
        return true;
    }
    return false;
}

ConstructionEquipment* EquipmentManager::findEquipmentById(int id) {
    for (auto& item : equipmentList_) {
        if (item && item->getId() == id) {
            return item.get();
        }
    }
    return nullptr;
}

const ConstructionEquipment* EquipmentManager::findEquipmentById(int id) const {
    for (const auto& item : equipmentList_) {
        if (item && item->getId() == id) {
            return item.get();
        }
    }
    return nullptr;
}

bool EquipmentManager::existsId(int id) const {
    return findEquipmentById(id) != nullptr;
}

int EquipmentManager::generateNextId() const {
    int maxId = 100;
    for (const auto& item : equipmentList_) {
        if (item && item->getId() > maxId) {
            maxId = item->getId();
        }
    }
    return maxId + 1;
}

void EquipmentManager::displayAll() const {
    if (equipmentList_.empty()) {
        std::cout << "\nБаза строительной техники пуста.\n";
        return;
    }

    ConstructionEquipment::printTableHeader();
    double totalHours = 0.0;
    double totalCost = 0.0;

    for (const auto& item : equipmentList_) {
        if (item) {
            item->printTableRow();
            totalHours += item->getHoursWorked();
            totalCost += item->calculateTotalCost();
        }
    }
    std::cout << std::string(126, '=') << "\n";
    std::cout << "ИТОГО по парку техники: "
              << "Единиц: " << equipmentList_.size() << " шт | "
              << "Отработано часов: " << std::fixed << std::setprecision(1) << totalHours << " ч | "
              << "Суммарная наработка: " << std::fixed << std::setprecision(2) << totalCost << " руб.\n";
}

void EquipmentManager::displayDetailedById(int id) const {
    const ConstructionEquipment* item = findEquipmentById(id);
    if (!item) {
        std::cout << "Ошибка: техника с инвентарным номером " << id << " не найдена.\n";
        return;
    }
    item->displayDetails();
}

bool EquipmentManager::exportToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        return false;
    }

    out << "ОТЧЕТ ПО УЧЕТУ ЗАНЯТОСТИ СТРОИТЕЛЬНОЙ ТЕХНИКИ\n";
    out << "Компания: ООО «СтройТехИнвест»\n";
    out << "Всего единиц техники: " << equipmentList_.size() << "\n\n";
    out << "ID;TypeID;TypeName;Model;RegNumber;SiteName;HourlyRate;HoursWorked;TotalCost;StatusID;StatusName;SpecialParams\n";

    for (const auto& item : equipmentList_) {
        if (item) {
            item->saveToFile(out);
        }
    }

    return true;
}

void EquipmentManager::seedDemoData() {
    equipmentList_.clear();

    equipmentList_.push_back(std::make_unique<Excavator>(
        101, "CAT 320D", "1234 AA-7", "ЖК «Северный Берег»", 130.0, 52.0,
        EquipmentStatus::IN_OPERATION, 1.3, 6.7
    ));

    equipmentList_.push_back(std::make_unique<TowerCrane>(
        102, "Liebherr 280 EC-H", "2345 AB-7", "ЖК «Минск-Мир»", 195.0, 84.0,
        EquipmentStatus::IN_OPERATION, 70.0, 12.0
    ));

    equipmentList_.push_back(std::make_unique<Bulldozer>(
        103, "Komatsu D65EX-16", "3456 AC-7", "Трасса М-1 Реконструкция", 145.0, 38.5,
        EquipmentStatus::STANDBY, 3.86, 205.0
    ));

    equipmentList_.push_back(std::make_unique<ConcreteMixer>(
        104, "КАМАЗ-65201 (TIGARBO)", "4567 AE-7", "Мостовой переход р. Свислочь", 115.0, 62.0,
        EquipmentStatus::IN_OPERATION, 10.0, 800.0
    ));

    equipmentList_.push_back(std::make_unique<DumpTruck>(
        105, "МАЗ-650128", "5678 AM-7", "Микрорайон «Лошица-9»", 95.0, 71.0,
        EquipmentStatus::AVAILABLE, 20.0, 12.5
    ));
}

void EquipmentManager::demonstratePolymorphicFactory(int id) const {
    const ConstructionEquipment* item = findEquipmentById(id);
    if (!item) {
        std::cout << "Ошибка: техника с инвентарным номером " << id << " не найдена.\n";
        return;
    }

    std::cout << "\n============================================================\n";
    std::cout << "ДЕМОНСТРАЦИЯ ПАТТЕРНА «ПОЛИМОРФНАЯ ФАБРИКА» (Методичка, стр. 9-11)\n";
    std::cout << "============================================================\n";
    std::cout << "Родительская единица техники: " << item->getTypeName()
              << " (" << item->getModel() << ", Гос. № " << item->getRegNumber() << ")\n";
    std::cout << "Механизм: виртуальный метод createAttachment() использует\n"
              << "КОВАРИАНТНЫЕ ВОЗВРАЩАЕМЫЕ ТИПЫ (Covariant Return Types),\n"
              << "создавая строго специфичное навесное оборудование без dynamic_cast!\n\n";

    std::unique_ptr<EquipmentAttachment> attachment(item->createAttachment());
    if (attachment) {
        attachment->displayAttachmentInfo();
        std::cout << "\n[OK] Навесное оборудование успешно сконструировано и протестировано (автоматическая RAII-очистка).\n";
    }
}

bool EquipmentManager::demonstratePolymorphicCloning(int id) {
    ConstructionEquipment* original = findEquipmentById(id);
    if (!original) {
        std::cout << "Ошибка: техника с инвентарным номером " << id << " не найдена.\n";
        return false;
    }

    std::cout << "\n============================================================\n";
    std::cout << "ДЕМОНСТРАЦИЯ ПАТТЕРНА «ПОЛИМОРФНОЕ КОПИРОВАНИЕ» (Методичка, стр. 11-15)\n";
    std::cout << "============================================================\n";
    std::cout << "Клонируемый оригинал: ID " << original->getId()
              << " | " << original->getTypeName() << " " << original->getModel() << "\n";
    std::cout << "Механизм: рекурсивный шаблон CRTP Cloner<Derived, Base>\n"
              << "выполняет глубокое полиморфное копирование через вызов clone()\n"
              << "по указателю на абстрактный базовый класс ConstructionEquipment!\n\n";

    std::unique_ptr<ConstructionEquipment> cloneItem = original->clone();
    int newId = generateNextId();
    cloneItem->setId(newId);
    cloneItem->setSiteName(original->getSiteName() + " (Участок №2)");
    cloneItem->setHoursWorked(0.0);
    cloneItem->setStatus(EquipmentStatus::AVAILABLE);

    std::cout << "Создан полиморфный клон-дубликат для переброски на новый участок:\n";
    cloneItem->displayDetails();

    addEquipment(std::move(cloneItem));
    std::cout << "[OK] Полиморфный клон успешно добавлен в компанию под ID " << newId << ".\n";
    return true;
}
