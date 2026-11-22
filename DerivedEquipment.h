#pragma once
#include "Cloner.h"
#include "EquipmentAttachments.h"

class Excavator : public Cloner<Excavator> {
private:
    double bucketCapacity_;
    double maxDiggingDepth_;

public:
    Excavator(int id = 101,
              const std::string& model = "CAT 320D",
              const std::string& regNumber = "1234 AA-7",
              const std::string& siteName = "ЖК «Северный Берег»",
              double hourlyRate = 120.0,
              double hoursWorked = 45.0,
              EquipmentStatus status = EquipmentStatus::IN_OPERATION,
              double bucketCapacity = 1.2,
              double maxDiggingDepth = 6.5);

    EquipmentType getType() const override { return EquipmentType::EXCAVATOR; }
    std::string getTypeName() const override { return "Экскаватор"; }
    std::string getSpecialParamsString() const override;

    double getBucketCapacity() const { return bucketCapacity_; }
    double getMaxDiggingDepth() const { return maxDiggingDepth_; }
    void setBucketCapacity(double c) { bucketCapacity_ = c; }
    void setMaxDiggingDepth(double d) { maxDiggingDepth_ = d; }

    ExcavatorBucket* createAttachment() const override;

    static std::unique_ptr<ConstructionEquipment> createDefault();
    static void Register();
};

class TowerCrane : public Cloner<TowerCrane> {
private:
    double boomReach_;
    double maxCapacity_;

public:
    TowerCrane(int id = 102,
               const std::string& model = "Liebherr 280 EC-H",
               const std::string& regNumber = "2345 AB-7",
               const std::string& siteName = "ЖК «Минск-Мир»",
               double hourlyRate = 180.0,
               double hoursWorked = 60.0,
               EquipmentStatus status = EquipmentStatus::IN_OPERATION,
               double boomReach = 70.0,
               double maxCapacity = 12.0);

    EquipmentType getType() const override { return EquipmentType::TOWER_CRANE; }
    std::string getTypeName() const override { return "Башенный кран"; }
    std::string getSpecialParamsString() const override;

    double getBoomReach() const { return boomReach_; }
    double getMaxCapacity() const { return maxCapacity_; }
    void setBoomReach(double r) { boomReach_ = r; }
    void setMaxCapacity(double c) { maxCapacity_ = c; }

    CraneHook* createAttachment() const override;

    static std::unique_ptr<ConstructionEquipment> createDefault();
    static void Register();
};

class Bulldozer : public Cloner<Bulldozer> {
private:
    double bladeWidth_;
    double enginePowerHp_;

public:
    Bulldozer(int id = 103,
              const std::string& model = "Komatsu D65EX",
              const std::string& regNumber = "3456 AC-7",
              const std::string& siteName = "Трасса М-1 Реконструкция",
              double hourlyRate = 140.0,
              double hoursWorked = 35.0,
              EquipmentStatus status = EquipmentStatus::STANDBY,
              double bladeWidth = 3.86,
              double enginePowerHp = 205.0);

    EquipmentType getType() const override { return EquipmentType::BULLDOZER; }
    std::string getTypeName() const override { return "Бульдозер"; }
    std::string getSpecialParamsString() const override;

    double getBladeWidth() const { return bladeWidth_; }
    double getEnginePowerHp() const { return enginePowerHp_; }
    void setBladeWidth(double w) { bladeWidth_ = w; }
    void setEnginePowerHp(double p) { enginePowerHp_ = p; }

    BulldozerBlade* createAttachment() const override;

    static std::unique_ptr<ConstructionEquipment> createDefault();
    static void Register();
};

class ConcreteMixer : public Cloner<ConcreteMixer> {
private:
    double drumVolume_;
    double waterTankCapacity_;

public:
    ConcreteMixer(int id = 104,
                  const std::string& model = "КАМАЗ-65201 (TIGARBO)",
                  const std::string& regNumber = "4567 AE-7",
                  const std::string& siteName = "Мостовой переход р. Свислочь",
                  double hourlyRate = 110.0,
                  double hoursWorked = 50.0,
                  EquipmentStatus status = EquipmentStatus::IN_OPERATION,
                  double drumVolume = 10.0,
                  double waterTankCapacity = 800.0);

    EquipmentType getType() const override { return EquipmentType::CONCRETE_MIXER; }
    std::string getTypeName() const override { return "Бетоносмеситель"; }
    std::string getSpecialParamsString() const override;

    double getDrumVolume() const { return drumVolume_; }
    double getWaterTankCapacity() const { return waterTankCapacity_; }
    void setDrumVolume(double v) { drumVolume_ = v; }
    void setWaterTankCapacity(double w) { waterTankCapacity_ = w; }

    ConcreteChute* createAttachment() const override;

    static std::unique_ptr<ConstructionEquipment> createDefault();
    static void Register();
};

class DumpTruck : public Cloner<DumpTruck> {
private:
    double payloadCapacity_;
    double bodyVolume_;

public:
    DumpTruck(int id = 105,
              const std::string& model = "МАЗ-650128",
              const std::string& regNumber = "5678 AM-7",
              const std::string& siteName = "Микрорайон «Лошица-9»",
              double hourlyRate = 95.0,
              double hoursWorked = 75.0,
              EquipmentStatus status = EquipmentStatus::AVAILABLE,
              double payloadCapacity = 20.0,
              double bodyVolume = 12.5);

    EquipmentType getType() const override { return EquipmentType::DUMP_TRUCK; }
    std::string getTypeName() const override { return "Самосвал"; }
    std::string getSpecialParamsString() const override;

    double getPayloadCapacity() const { return payloadCapacity_; }
    double getBodyVolume() const { return bodyVolume_; }
    void setPayloadCapacity(double p) { payloadCapacity_ = p; }
    void setBodyVolume(double v) { bodyVolume_ = v; }

    TippingBody* createAttachment() const override;

    static std::unique_ptr<ConstructionEquipment> createDefault();
    static void Register();
};
