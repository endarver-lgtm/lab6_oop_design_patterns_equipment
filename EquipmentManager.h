#pragma once
#include <vector>
#include <memory>
#include <string>
#include "ConstructionEquipment.h"
#include "DerivedEquipment.h"

class EquipmentManager {
private:
    std::vector<std::unique_ptr<ConstructionEquipment>> equipmentList_;

public:
    EquipmentManager() = default;

    void addEquipment(std::unique_ptr<ConstructionEquipment> item);

    bool removeEquipmentById(int id);

    ConstructionEquipment* findEquipmentById(int id);
    const ConstructionEquipment* findEquipmentById(int id) const;

    bool existsId(int id) const;

    int generateNextId() const;

    size_t getCount() const { return equipmentList_.size(); }

    void displayAll() const;

    void displayDetailedById(int id) const;

    bool exportToFile(const std::string& filename) const;

    void seedDemoData();

    void demonstratePolymorphicFactory(int id) const;

    bool demonstratePolymorphicCloning(int id);
};
