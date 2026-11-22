#pragma once
#include <map>
#include <string>
#include <memory>
#include "ConstructionEquipment.h"

using EquipmentCreator = std::unique_ptr<ConstructionEquipment>(*)();

struct RegistryEntry {
    int typeId;
    std::string typeName;
    EquipmentCreator creator;
};

class EquipmentRegistry {
private:
    std::map<int, RegistryEntry> entries_;

    EquipmentRegistry() = default;

public:

    EquipmentRegistry(const EquipmentRegistry&) = delete;
    EquipmentRegistry& operator=(const EquipmentRegistry&) = delete;

    static EquipmentRegistry& instance();

    void registerType(int typeId, const std::string& typeName, EquipmentCreator creator);

    std::unique_ptr<ConstructionEquipment> create(int typeId) const;

    bool isRegistered(int typeId) const;

    const std::map<int, RegistryEntry>& getEntries() const { return entries_; }

    size_t count() const { return entries_.size(); }
};
