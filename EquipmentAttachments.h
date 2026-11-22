#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

class EquipmentAttachment {
public:
    virtual ~EquipmentAttachment() = default;
    virtual std::string getAttachmentName() const = 0;
    virtual std::string getSpecifications() const = 0;
    virtual void displayAttachmentInfo() const {
        std::cout << "Навесное оборудование: " << getAttachmentName() << "\n"
                  << "  Характеристики: " << getSpecifications() << "\n";
    }
};

class ExcavatorBucket : public EquipmentAttachment {
private:
    double volumeM3_;
    int teethCount_;
    std::string materialGrade_;
public:
    ExcavatorBucket(double volumeM3 = 1.2, int teethCount = 5, const std::string& grade = "Hardox 450")
        : volumeM3_(volumeM3), teethCount_(teethCount), materialGrade_(grade) {}

    std::string getAttachmentName() const override {
        return "Усиленный ковш экскаватора";
    }

    std::string getSpecifications() const override {
        std::ostringstream ss;
        ss << "Объем: " << std::fixed << std::setprecision(2) << volumeM3_ << " м³, "
           << "Кол-во зубьев: " << teethCount_ << " шт, "
           << "Сталь: " << materialGrade_;
        return ss.str();
    }

    double getVolume() const { return volumeM3_; }
    int getTeethCount() const { return teethCount_; }
};

class CraneHook : public EquipmentAttachment {
private:
    double maxLoadTon_;
    int reevingParts_;
    bool hasSafetyLatch_;
public:
    CraneHook(double maxLoadTon = 10.0, int reevingParts = 4, bool hasSafetyLatch = true)
        : maxLoadTon_(maxLoadTon), reevingParts_(reevingParts), hasSafetyLatch_(hasSafetyLatch) {}

    std::string getAttachmentName() const override {
        return "Грузовая крюковая обойма крана";
    }

    std::string getSpecifications() const override {
        std::ostringstream ss;
        ss << "Грузоподъемность подвески: " << std::fixed << std::setprecision(1) << maxLoadTon_ << " т, "
           << "Запасовка каната: " << reevingParts_ << "-кратная, "
           << "Предохранительный замок: " << (hasSafetyLatch_ ? "Есть" : "Нет");
        return ss.str();
    }

    double getMaxLoad() const { return maxLoadTon_; }
};

class BulldozerBlade : public EquipmentAttachment {
private:
    std::string bladeType_;
    double bladeWidthM_;
    bool hasRipper_;
public:
    BulldozerBlade(const std::string& type = "Полусферический (Semi-U)", double widthM = 3.8, bool hasRipper = true)
        : bladeType_(type), bladeWidthM_(widthM), hasRipper_(hasRipper) {}

    std::string getAttachmentName() const override {
        return "Бульдозерный рабочий отвал";
    }

    std::string getSpecifications() const override {
        std::ostringstream ss;
        ss << "Тип отвала: " << bladeType_ << ", "
           << "Ширина: " << std::fixed << std::setprecision(2) << bladeWidthM_ << " м, "
           << "Задний рыхлитель: " << (hasRipper_ ? "Установлен" : "Отсутствует");
        return ss.str();
    }

    double getWidth() const { return bladeWidthM_; }
};

class ConcreteChute : public EquipmentAttachment {
private:
    double chuteLengthM_;
    bool hasFlexibleHose_;
    double dischargeRateM3h_;
public:
    ConcreteChute(double lengthM = 3.5, bool hasHose = true, double rateM3h = 45.0)
        : chuteLengthM_(lengthM), hasFlexibleHose_(hasHose), dischargeRateM3h_(rateM3h) {}

    std::string getAttachmentName() const override {
        return "Поворотный разгрузочный лоток бетоносмесителя";
    }

    std::string getSpecifications() const override {
        std::ostringstream ss;
        ss << "Длина лотка: " << std::fixed << std::setprecision(1) << chuteLengthM_ << " м, "
           << "Гибкий рукав: " << (hasFlexibleHose_ ? "Да" : "Нет") << ", "
           << "Пропускная способность: " << dischargeRateM3h_ << " м³/ч";
        return ss.str();
    }

    double getChuteLength() const { return chuteLengthM_; }
};

class TippingBody : public EquipmentAttachment {
private:
    double maxTiltAngleDeg_;
    bool hasExhaustHeating_;
    std::string tailgateType_;
public:
    TippingBody(double angleDeg = 65.0, bool heating = true, const std::string& tailgate = "Автоматический маятниковый")
        : maxTiltAngleDeg_(angleDeg), hasExhaustHeating_(heating), tailgateType_(tailgate) {}

    std::string getAttachmentName() const override {
        return "Самосвальная платформа с гидроподъемником";
    }

    std::string getSpecifications() const override {
        std::ostringstream ss;
        ss << "Угол опрокидывания: " << std::fixed << std::setprecision(1) << maxTiltAngleDeg_ << "°, "
           << "Обогрев выхлопными газами: " << (hasExhaustHeating_ ? "Да" : "Нет") << ", "
           << "Борт: " << tailgateType_;
        return ss.str();
    }

    double getTiltAngle() const { return maxTiltAngleDeg_; }
};
