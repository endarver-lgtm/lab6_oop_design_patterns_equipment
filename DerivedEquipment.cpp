#include "DerivedEquipment.h"
#include "EquipmentRegistry.h"
#include <sstream>
#include <iomanip>

Excavator::Excavator(int id,
                     const std::string& model,
                     const std::string& regNumber,
                     const std::string& siteName,
                     double hourlyRate,
                     double hoursWorked,
                     EquipmentStatus status,
                     double bucketCapacity,
                     double maxDiggingDepth)
    : Cloner<Excavator>(id, model, regNumber, siteName, hourlyRate, hoursWorked, status),
      bucketCapacity_(bucketCapacity),
      maxDiggingDepth_(maxDiggingDepth) {}

std::string Excavator::getSpecialParamsString() const {
    std::ostringstream ss;
    ss << "Объем ковша: " << std::fixed << std::setprecision(2) << bucketCapacity_ << " м³, "
       << "Глубина копания: " << maxDiggingDepth_ << " м";
    return ss.str();
}

ExcavatorBucket* Excavator::createAttachment() const {
    return new ExcavatorBucket(bucketCapacity_, 5, "Hardox 450");
}

std::unique_ptr<ConstructionEquipment> Excavator::createDefault() {
    return std::make_unique<Excavator>();
}

void Excavator::Register() {
    EquipmentRegistry::instance().registerType(
        static_cast<int>(EquipmentType::EXCAVATOR),
        "Экскаватор",
        &Excavator::createDefault
    );
}

TowerCrane::TowerCrane(int id,
                       const std::string& model,
                       const std::string& regNumber,
                       const std::string& siteName,
                       double hourlyRate,
                       double hoursWorked,
                       EquipmentStatus status,
                       double boomReach,
                       double maxCapacity)
    : Cloner<TowerCrane>(id, model, regNumber, siteName, hourlyRate, hoursWorked, status),
      boomReach_(boomReach),
      maxCapacity_(maxCapacity) {}

std::string TowerCrane::getSpecialParamsString() const {
    std::ostringstream ss;
    ss << "Вылет стрелы: " << std::fixed << std::setprecision(1) << boomReach_ << " м, "
       << "Грузоподъемность: " << maxCapacity_ << " т";
    return ss.str();
}

CraneHook* TowerCrane::createAttachment() const {
    return new CraneHook(maxCapacity_, 4, true);
}

std::unique_ptr<ConstructionEquipment> TowerCrane::createDefault() {
    return std::make_unique<TowerCrane>();
}

void TowerCrane::Register() {
    EquipmentRegistry::instance().registerType(
        static_cast<int>(EquipmentType::TOWER_CRANE),
        "Башенный кран",
        &TowerCrane::createDefault
    );
}

Bulldozer::Bulldozer(int id,
                     const std::string& model,
                     const std::string& regNumber,
                     const std::string& siteName,
                     double hourlyRate,
                     double hoursWorked,
                     EquipmentStatus status,
                     double bladeWidth,
                     double enginePowerHp)
    : Cloner<Bulldozer>(id, model, regNumber, siteName, hourlyRate, hoursWorked, status),
      bladeWidth_(bladeWidth),
      enginePowerHp_(enginePowerHp) {}

std::string Bulldozer::getSpecialParamsString() const {
    std::ostringstream ss;
    ss << "Ширина отвала: " << std::fixed << std::setprecision(2) << bladeWidth_ << " м, "
       << "Мощность: " << std::setprecision(0) << enginePowerHp_ << " л.с.";
    return ss.str();
}

BulldozerBlade* Bulldozer::createAttachment() const {
    return new BulldozerBlade("Полусферический (Semi-U)", bladeWidth_, true);
}

std::unique_ptr<ConstructionEquipment> Bulldozer::createDefault() {
    return std::make_unique<Bulldozer>();
}

void Bulldozer::Register() {
    EquipmentRegistry::instance().registerType(
        static_cast<int>(EquipmentType::BULLDOZER),
        "Бульдозер",
        &Bulldozer::createDefault
    );
}

ConcreteMixer::ConcreteMixer(int id,
                             const std::string& model,
                             const std::string& regNumber,
                             const std::string& siteName,
                             double hourlyRate,
                             double hoursWorked,
                             EquipmentStatus status,
                             double drumVolume,
                             double waterTankCapacity)
    : Cloner<ConcreteMixer>(id, model, regNumber, siteName, hourlyRate, hoursWorked, status),
      drumVolume_(drumVolume),
      waterTankCapacity_(waterTankCapacity) {}

std::string ConcreteMixer::getSpecialParamsString() const {
    std::ostringstream ss;
    ss << "Объем барабана: " << std::fixed << std::setprecision(1) << drumVolume_ << " м³, "
       << "Бак для воды: " << std::setprecision(0) << waterTankCapacity_ << " л";
    return ss.str();
}

ConcreteChute* ConcreteMixer::createAttachment() const {
    return new ConcreteChute(3.5, true, 45.0);
}

std::unique_ptr<ConstructionEquipment> ConcreteMixer::createDefault() {
    return std::make_unique<ConcreteMixer>();
}

void ConcreteMixer::Register() {
    EquipmentRegistry::instance().registerType(
        static_cast<int>(EquipmentType::CONCRETE_MIXER),
        "Бетоносмеситель",
        &ConcreteMixer::createDefault
    );
}

DumpTruck::DumpTruck(int id,
                     const std::string& model,
                     const std::string& regNumber,
                     const std::string& siteName,
                     double hourlyRate,
                     double hoursWorked,
                     EquipmentStatus status,
                     double payloadCapacity,
                     double bodyVolume)
    : Cloner<DumpTruck>(id, model, regNumber, siteName, hourlyRate, hoursWorked, status),
      payloadCapacity_(payloadCapacity),
      bodyVolume_(bodyVolume) {}

std::string DumpTruck::getSpecialParamsString() const {
    std::ostringstream ss;
    ss << "Грузоподъемность: " << std::fixed << std::setprecision(1) << payloadCapacity_ << " т, "
       << "Объем кузова: " << bodyVolume_ << " м³";
    return ss.str();
}

TippingBody* DumpTruck::createAttachment() const {
    return new TippingBody(65.0, true, "Маятниковый с гидрозамком");
}

std::unique_ptr<ConstructionEquipment> DumpTruck::createDefault() {
    return std::make_unique<DumpTruck>();
}

void DumpTruck::Register() {
    EquipmentRegistry::instance().registerType(
        static_cast<int>(EquipmentType::DUMP_TRUCK),
        "Самосвал",
        &DumpTruck::createDefault
    );
}
