#include "ConstructionEquipment.h"
#include <iomanip>

ConstructionEquipment::ConstructionEquipment(int id,
                                             const std::string& model,
                                             const std::string& regNumber,
                                             const std::string& siteName,
                                             double hourlyRate,
                                             double hoursWorked,
                                             EquipmentStatus status)
    : id_(id),
      model_(model),
      regNumber_(regNumber),
      siteName_(siteName),
      hourlyRate_(hourlyRate),
      hoursWorked_(hoursWorked),
      status_(status) {}

double ConstructionEquipment::calculateTotalCost() const {
    return hourlyRate_ * hoursWorked_;
}

void ConstructionEquipment::displayDetails() const {
    std::cout << "------------------------------------------------------------\n"
              << "Инв. номер:      " << id_ << "\n"
              << "Тип техники:     " << getTypeName() << "\n"
              << "Модель:          " << model_ << "\n"
              << "Гос. номер:      " << regNumber_ << "\n"
              << "Объект:          " << siteName_ << "\n"
              << "Почасовая ставка:" << std::fixed << std::setprecision(2) << hourlyRate_ << " руб/ч\n"
              << "Отработано:      " << hoursWorked_ << " ч\n"
              << "Стоимость работ: " << calculateTotalCost() << " руб\n"
              << "Статус:          " << statusToString(status_) << "\n"
              << "Спец. параметры: " << getSpecialParamsString() << "\n"
              << "------------------------------------------------------------\n";
}

void ConstructionEquipment::saveToFile(std::ostream& out) const {
    out << id_ << ";"
        << static_cast<int>(getType()) << ";"
        << getTypeName() << ";"
        << model_ << ";"
        << regNumber_ << ";"
        << siteName_ << ";"
        << std::fixed << std::setprecision(2) << hourlyRate_ << ";"
        << hoursWorked_ << ";"
        << calculateTotalCost() << ";"
        << static_cast<int>(status_) << ";"
        << statusToString(status_) << ";"
        << getSpecialParamsString() << "\n";
}

std::string ConstructionEquipment::statusToString(EquipmentStatus st) {
    switch (st) {
    case EquipmentStatus::IN_OPERATION:     return "В работе";
    case EquipmentStatus::UNDER_MAINTENANCE:return "На ТО";
    case EquipmentStatus::STANDBY:          return "В резерве";
    case EquipmentStatus::AVAILABLE:        return "Доступна";
    default:                                return "Неизвестно";
    }
}

std::string ConstructionEquipment::typeToString(EquipmentType t) {
    switch (t) {
    case EquipmentType::EXCAVATOR:      return "Экскаватор";
    case EquipmentType::TOWER_CRANE:    return "Башенный кран";
    case EquipmentType::BULLDOZER:      return "Бульдозер";
    case EquipmentType::CONCRETE_MIXER: return "Бетоносмеситель";
    case EquipmentType::DUMP_TRUCK:     return "Самосвал";
    default:                            return "Техника";
    }
}

void ConstructionEquipment::printTableHeader() {
    std::cout << std::string(126, '=') << "\n";
    std::cout << std::left
              << std::setw(6)  << " ID" << " | "
              << std::setw(16) << "Тип" << " | "
              << std::setw(18) << "Модель" << " | "
              << std::setw(12) << "Гос. номер" << " | "
              << std::setw(18) << "Объект" << " | "
              << std::right
              << std::setw(9)  << "Ставка" << " | "
              << std::setw(7)  << "Часы" << " | "
              << std::setw(12) << "Стоимость" << " | "
              << std::left
              << std::setw(12) << "Статус"
              << "\n";
    std::cout << std::string(126, '-') << "\n";
}

void ConstructionEquipment::printTableRow() const {
    std::cout << std::left
              << " " << std::setw(5) << id_ << " | "
              << std::setw(16) << getTypeName() << " | "
              << std::setw(18) << (model_.size() > 17 ? model_.substr(0, 14) + "..." : model_) << " | "
              << std::setw(12) << regNumber_ << " | "
              << std::setw(18) << (siteName_.size() > 17 ? siteName_.substr(0, 14) + "..." : siteName_) << " | "
              << std::right
              << std::fixed << std::setprecision(1)
              << std::setw(9)  << hourlyRate_ << " | "
              << std::setw(7)  << hoursWorked_ << " | "
              << std::setw(12) << calculateTotalCost() << " | "
              << std::left
              << std::setw(12) << statusToString(status_)
              << "\n";
}
