#include "Factories.h"
#include "DerivedEquipment.h"
#include <iostream>

std::unique_ptr<ConstructionEquipment> SimpleEquipmentFactory::create(EquipmentType type) {
    switch (type) {
    case EquipmentType::EXCAVATOR:
        return std::make_unique<Excavator>();
    case EquipmentType::TOWER_CRANE:
        return std::make_unique<TowerCrane>();
    case EquipmentType::BULLDOZER:
        return std::make_unique<Bulldozer>();
    case EquipmentType::CONCRETE_MIXER:
        return std::make_unique<ConcreteMixer>();
    case EquipmentType::DUMP_TRUCK:
        return std::make_unique<DumpTruck>();
    default:
        return nullptr;
    }
}

std::unique_ptr<ConstructionEquipment> ParameterizedEquipmentFactory::create(const EquipmentSpec& spec) {
    switch (spec.getType()) {
    case EquipmentType::EXCAVATOR: {
        const auto& s = static_cast<const ExcavatorSpec&>(spec);
        return std::make_unique<Excavator>(
            s.id, s.model, s.regNumber, s.siteName,
            s.hourlyRate, s.hoursWorked, s.status,
            s.bucketCapacity, s.maxDiggingDepth
        );
    }
    case EquipmentType::TOWER_CRANE: {
        const auto& s = static_cast<const TowerCraneSpec&>(spec);
        return std::make_unique<TowerCrane>(
            s.id, s.model, s.regNumber, s.siteName,
            s.hourlyRate, s.hoursWorked, s.status,
            s.boomReach, s.maxCapacity
        );
    }
    case EquipmentType::BULLDOZER: {
        const auto& s = static_cast<const BulldozerSpec&>(spec);
        return std::make_unique<Bulldozer>(
            s.id, s.model, s.regNumber, s.siteName,
            s.hourlyRate, s.hoursWorked, s.status,
            s.bladeWidth, s.enginePowerHp
        );
    }
    case EquipmentType::CONCRETE_MIXER: {
        const auto& s = static_cast<const ConcreteMixerSpec&>(spec);
        return std::make_unique<ConcreteMixer>(
            s.id, s.model, s.regNumber, s.siteName,
            s.hourlyRate, s.hoursWorked, s.status,
            s.drumVolume, s.waterTankCapacity
        );
    }
    case EquipmentType::DUMP_TRUCK: {
        const auto& s = static_cast<const DumpTruckSpec&>(spec);
        return std::make_unique<DumpTruck>(
            s.id, s.model, s.regNumber, s.siteName,
            s.hourlyRate, s.hoursWorked, s.status,
            s.payloadCapacity, s.bodyVolume
        );
    }
    default:
        return nullptr;
    }
}

std::unique_ptr<ConstructionEquipment> VariadicEquipmentFactory::createWithArgs(
    EquipmentType type,
    int id,
    const char* model,
    const char* regNumber,
    const char* siteName,
    double hourlyRate,
    double hoursWorked,
    ...
) {
    va_list args;
    va_start(args, hoursWorked);

    std::unique_ptr<ConstructionEquipment> result = nullptr;

    switch (type) {
    case EquipmentType::EXCAVATOR: {
        double bucketCap = va_arg(args, double);
        double maxDepth = va_arg(args, double);
        result = std::make_unique<Excavator>(
            id, model, regNumber, siteName, hourlyRate, hoursWorked,
            EquipmentStatus::AVAILABLE, bucketCap, maxDepth
        );
        break;
    }
    case EquipmentType::TOWER_CRANE: {
        double boomReach = va_arg(args, double);
        double maxCap = va_arg(args, double);
        result = std::make_unique<TowerCrane>(
            id, model, regNumber, siteName, hourlyRate, hoursWorked,
            EquipmentStatus::AVAILABLE, boomReach, maxCap
        );
        break;
    }
    case EquipmentType::BULLDOZER: {
        double bladeWidth = va_arg(args, double);
        double engineHp = va_arg(args, double);
        result = std::make_unique<Bulldozer>(
            id, model, regNumber, siteName, hourlyRate, hoursWorked,
            EquipmentStatus::AVAILABLE, bladeWidth, engineHp
        );
        break;
    }
    case EquipmentType::CONCRETE_MIXER: {
        double drumVol = va_arg(args, double);
        double waterCap = va_arg(args, double);
        result = std::make_unique<ConcreteMixer>(
            id, model, regNumber, siteName, hourlyRate, hoursWorked,
            EquipmentStatus::AVAILABLE, drumVol, waterCap
        );
        break;
    }
    case EquipmentType::DUMP_TRUCK: {
        double payload = va_arg(args, double);
        double bodyVol = va_arg(args, double);
        result = std::make_unique<DumpTruck>(
            id, model, regNumber, siteName, hourlyRate, hoursWorked,
            EquipmentStatus::AVAILABLE, payload, bodyVol
        );
        break;
    }
    default:
        break;
    }

    va_end(args);
    return result;
}
