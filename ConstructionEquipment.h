#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "EquipmentAttachments.h"

enum class EquipmentStatus {
    IN_OPERATION = 1,
    UNDER_MAINTENANCE,
    STANDBY,
    AVAILABLE
};

enum class EquipmentType {
    EXCAVATOR = 1,
    TOWER_CRANE,
    BULLDOZER,
    CONCRETE_MIXER,
    DUMP_TRUCK
};

class ConstructionEquipment {
protected:
    int id_;
    std::string model_;
    std::string regNumber_;
    std::string siteName_;
    double hourlyRate_;
    double hoursWorked_;
    EquipmentStatus status_;

public:
    ConstructionEquipment(int id,
                          const std::string& model,
                          const std::string& regNumber,
                          const std::string& siteName,
                          double hourlyRate,
                          double hoursWorked,
                          EquipmentStatus status = EquipmentStatus::AVAILABLE);

    virtual ~ConstructionEquipment() = default;

    int getId() const { return id_; }
    const std::string& getModel() const { return model_; }
    const std::string& getRegNumber() const { return regNumber_; }
    const std::string& getSiteName() const { return siteName_; }
    double getHourlyRate() const { return hourlyRate_; }
    double getHoursWorked() const { return hoursWorked_; }
    EquipmentStatus getStatus() const { return status_; }

    void setId(int id) { id_ = id; }
    void setModel(const std::string& m) { model_ = m; }
    void setRegNumber(const std::string& r) { regNumber_ = r; }
    void setSiteName(const std::string& s) { siteName_ = s; }
    void setHourlyRate(double rate) { hourlyRate_ = rate; }
    void setHoursWorked(double h) { hoursWorked_ = h; }
    void setStatus(EquipmentStatus st) { status_ = st; }

    virtual double calculateTotalCost() const;

    virtual EquipmentType getType() const = 0;
    virtual std::string getTypeName() const = 0;

    virtual std::string getSpecialParamsString() const = 0;

    virtual void displayDetails() const;

    virtual void saveToFile(std::ostream& out) const;

    virtual EquipmentAttachment* createAttachment() const = 0;

    virtual std::unique_ptr<ConstructionEquipment> clone() const = 0;

    static std::string statusToString(EquipmentStatus st);
    static std::string typeToString(EquipmentType t);
    static void printTableHeader();
    void printTableRow() const;
};
