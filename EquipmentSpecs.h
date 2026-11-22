#pragma once
#include <string>
#include "ConstructionEquipment.h"

class EquipmentSpec {
public:
    virtual ~EquipmentSpec() = default;
    virtual EquipmentType getType() const = 0;

    int id = 0;
    std::string model;
    std::string regNumber;
    std::string siteName;
    double hourlyRate = 0.0;
    double hoursWorked = 0.0;
    EquipmentStatus status = EquipmentStatus::AVAILABLE;
};

class ExcavatorSpec : public EquipmentSpec {
public:
    EquipmentType getType() const override { return EquipmentType::EXCAVATOR; }
    double bucketCapacity = 1.0;
    double maxDiggingDepth = 5.0;
};

class TowerCraneSpec : public EquipmentSpec {
public:
    EquipmentType getType() const override { return EquipmentType::TOWER_CRANE; }
    double boomReach = 50.0;
    double maxCapacity = 10.0;
};

class BulldozerSpec : public EquipmentSpec {
public:
    EquipmentType getType() const override { return EquipmentType::BULLDOZER; }
    double bladeWidth = 3.5;
    double enginePowerHp = 180.0;
};

class ConcreteMixerSpec : public EquipmentSpec {
public:
    EquipmentType getType() const override { return EquipmentType::CONCRETE_MIXER; }
    double drumVolume = 9.0;
    double waterTankCapacity = 600.0;
};

class DumpTruckSpec : public EquipmentSpec {
public:
    EquipmentType getType() const override { return EquipmentType::DUMP_TRUCK; }
    double payloadCapacity = 25.0;
    double bodyVolume = 15.0;
};
