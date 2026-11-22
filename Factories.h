#pragma once
#include <memory>
#include <cstdarg>
#include "ConstructionEquipment.h"
#include "EquipmentSpecs.h"

class SimpleEquipmentFactory {
public:
    static std::unique_ptr<ConstructionEquipment> create(EquipmentType type);
};

class ParameterizedEquipmentFactory {
public:
    static std::unique_ptr<ConstructionEquipment> create(const EquipmentSpec& spec);
};

class VariadicEquipmentFactory {
public:

    static std::unique_ptr<ConstructionEquipment> createWithArgs(
        EquipmentType type,
        int id,
        const char* model,
        const char* regNumber,
        const char* siteName,
        double hourlyRate,
        double hoursWorked,
        ...
    );
};
