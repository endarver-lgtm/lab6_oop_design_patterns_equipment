#include "EquipmentRegistry.h"
#include <iostream>
#include <stdexcept>

EquipmentRegistry& EquipmentRegistry::instance() {
    static EquipmentRegistry reg;
    return reg;
}

void EquipmentRegistry::registerType(int typeId, const std::string& typeName, EquipmentCreator creator) {
    if (!creator) return;
    entries_[typeId] = RegistryEntry{ typeId, typeName, creator };
}

std::unique_ptr<ConstructionEquipment> EquipmentRegistry::create(int typeId) const {
    auto it = entries_.find(typeId);
    if (it != entries_.end() && it->second.creator) {
        return it->second.creator();
    }
    return nullptr;
}

bool EquipmentRegistry::isRegistered(int typeId) const {
    return entries_.find(typeId) != entries_.end();
}
