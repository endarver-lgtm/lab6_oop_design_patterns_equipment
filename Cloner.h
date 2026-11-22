#pragma once
#include <memory>
#include "ConstructionEquipment.h"

template <typename Derived, typename Base = ConstructionEquipment>
class Cloner : public Base {
public:
    using Base::Base;

    std::unique_ptr<ConstructionEquipment> clone() const override {
        return std::make_unique<Derived>(*static_cast<const Derived*>(this));
    }
};
