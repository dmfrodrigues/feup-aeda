#include "../include/truck.h"

#include "../include/utils.h"

/* Truck Superclass */
Truck::Truck(const Truck &truck):
    max_weight_(truck.max_weight_), max_reach_(truck.max_reach_), taxes_(truck.taxes_){}

Truck::Truck(unsigned int max_weight, unsigned int max_reach, float taxes):
    max_weight_(max_weight), max_reach_(max_reach), taxes_(taxes){}

unsigned int Truck::getMaxWeight() const { return max_weight_; }

void Truck::setMaxWeight(unsigned int max_weight) {
    max_weight_ = max_weight;
}

Currency Truck::getPrice() { updatePrice(); return price_; }

float Truck::getTotalWeight(void) const {
    float weight = 0;
    for (const Cargo &cargo : cargo_)
        weight += cargo.getWeight();

    return weight;
}

std::vector<Cargo>::iterator Truck::removeCargo(std::vector<Cargo>::const_iterator it) {
    if (it >= cargo_.end() || it < cargo_.begin()) throw utils::InvalidIterator();

    return cargo_.erase(it);
}

void Truck::clearCargo() { cargo_.clear(); }

std::vector<Cargo>::iterator Truck::cargoBegin() { return cargo_.begin(); }

std::vector<Cargo>::iterator Truck::cargoEnd() { return cargo_.end(); }

/* Refrigerator Truck */

void RefrigeratorTruck::updatePrice(void) {
    double price = 0;

    for (const Cargo& cargo : cargo_)
        price += cargo.getPrice().getCents();

    price += std::abs(temperature_ - 20) * 100 + max_reach_ * 100;
    price += price * taxes_;
    price_ = Currency(price);
}

RefrigeratorTruck::RefrigeratorTruck(const Truck &truck): Truck(truck), temperature_(20) {}

RefrigeratorTruck::RefrigeratorTruck(const RefrigeratorTruck &truck): Truck(truck), temperature_(truck.temperature_) {}

RefrigeratorTruck::RefrigeratorTruck(unsigned int max_weight, unsigned int max_reach, float taxes, float temperature):
    Truck(max_weight, max_reach, taxes), temperature_(temperature){}

Truck::Type RefrigeratorTruck::get_type(void) const { return Truck::Type::Refrigerator; }

float RefrigeratorTruck::getTemperature(void) const { return temperature_; }

void RefrigeratorTruck::setTemperature(float temperature) { temperature_ = temperature; }

bool RefrigeratorTruck::addCargo(const Cargo &cargo) {

    Cargo::Type type = cargo.getType();

    if (type == Cargo::Type::Normal) {
        if (temperature_ < 10 || temperature_ > 30)
            throw std::invalid_argument("Invalid cargo (normal cargo that is transported at ambient temperature on a refrigerator truck that isn't at ambient temperature.)");
    }

    if (type != Cargo::Type::Normal && type != Cargo::Type::Refrigerated)
        throw std::invalid_argument("Invalid cargo (cargo type not supported by this truck).");

    if (cargo.getDangerLevel() > Cargo::DangerLevel::Miscellaneous)
        throw std::invalid_argument("Invalid cargo (truck can't transport dangerous goods).");

    if (cargo.getMinTemp() > temperature_ || cargo.getMaxTemp() < temperature_)
        throw std::invalid_argument("Invalid cargo (temperature range needed for cargo not supported by this truck)");

    if (getTotalWeight() + cargo.getWeight()*cargo.getQuantity() > max_weight_)
        return 1;

    cargo_.push_back(cargo);
    return 0;
}

/* DangerousCargoTruck */

void DangerousCargoTruck::updatePrice(void) {
    double price = 0;

    for (const Cargo& cargo : cargo_)
        price += cargo.getPrice().getCents();

    price += max_danger_level_ * 1000 + max_reach_ * 100;
    price += price * taxes_;
    price_ = Currency(price);
}

DangerousCargoTruck::DangerousCargoTruck(const Truck &truck): Truck(truck), max_danger_level_(Cargo::DangerLevel::Gases) {}

DangerousCargoTruck::DangerousCargoTruck(const DangerousCargoTruck &truck): Truck(truck), max_danger_level_(truck.max_danger_level_) {}

DangerousCargoTruck::DangerousCargoTruck(unsigned int max_weight, unsigned int max_reach, float taxes, Cargo::DangerLevel max_danger_level):
    Truck(max_weight, max_reach, taxes), max_danger_level_(max_danger_level){}

Truck::Type DangerousCargoTruck::get_type(void) const { return Truck::Type::DangerousCargo; }

Cargo::DangerLevel DangerousCargoTruck::getMaxDangerLevel() const { return max_danger_level_; }

void DangerousCargoTruck::setMaxDangerLevel(Cargo::DangerLevel max_danger_level) { max_danger_level_ = max_danger_level; }

bool DangerousCargoTruck::addCargo(const Cargo &cargo) {

    Cargo::Type type = cargo.getType();

    if (type == Cargo::Type::Refrigerated) {
        if (cargo.getMinTemp() > 30 || cargo.getMaxTemp() < 10)
            throw std::invalid_argument("Invalid cargo (cargo needs temperature ranges not compatible with this truck)");
    }

    if (type == Cargo::Type::Animal)
        throw std::invalid_argument("Invalid cargo (cargo type not supported by this truck).");

    if (cargo.getDangerLevel() > max_danger_level_)
        throw std::invalid_argument("Invalid cargo (truck can't transport cargo with this danger level).");

    if (getTotalWeight() + cargo.getWeight()*cargo.getQuantity() > max_weight_)
        return 1;

    cargo_.push_back(cargo);
    return 0;
}

/* Animal Truck */

void AnimalTruck::updatePrice(void) {
    double price = 0;

    for (const Cargo& cargo : cargo_)
        price += cargo.getPrice().getCents();

    price += max_reach_ * 300;
    price += price * taxes_;
    price_ = Currency(price);
}

AnimalTruck::AnimalTruck(const Truck &truck): Truck(truck) {}

AnimalTruck::AnimalTruck(unsigned int max_weight, unsigned int max_reach, float taxes):
    Truck(max_weight, max_reach, taxes){}

Truck::Type AnimalTruck::get_type(void) const { return Truck::Type::Animal; }

bool AnimalTruck::addCargo(const Cargo &cargo) {

    Cargo::Type type = cargo.getType();

    if (type != Cargo::Type::Normal && type != Cargo::Type::Animal)
        throw std::invalid_argument("Invalid cargo (type of cargo not supported by this truck).");

    if (cargo.getDangerLevel() > Cargo::DangerLevel::Miscellaneous)
        throw std::invalid_argument("Invalid cargo (truck can't transport dangerous goods).");

    if (getTotalWeight() + cargo.getWeight()*cargo.getQuantity() > max_weight_)
        return 1;

    cargo_.push_back(cargo);
    return 0;
}

/* Normal Truck */

void NormalTruck::updatePrice(void) {
    double price = 0;

    for (const Cargo& cargo : cargo_)
        price += cargo.getPrice().getCents();

    price += max_reach_ * 50;
    price += price * taxes_;
    price_ = Currency(price);
}

NormalTruck::NormalTruck(const Truck &truck): Truck(truck){}

NormalTruck::NormalTruck(unsigned int max_weight, unsigned int max_reach, float taxes):
    Truck(max_weight, max_reach, taxes){}

Truck::Type NormalTruck::get_type() const { return Truck::Type::Normal; }

bool NormalTruck::addCargo(const Cargo &cargo) {

    Cargo::Type type = cargo.getType();

    if (type != Cargo::Type::Normal)
        throw std::invalid_argument("Invalid cargo (type of cargo not supported by this truck).");

    if (cargo.getDangerLevel() > Cargo::DangerLevel::None)
        throw std::invalid_argument("Invalid cargo (truck can't transport dangerous goods).");

    if (getTotalWeight() + cargo.getWeight()*cargo.getQuantity() > max_weight_)
        return 1;

    cargo_.push_back(cargo);
    return 0;
}

/* DangerousRefrigeratorTruck */

void DangerousRefrigeratorTruck::updatePrice(void) {
    double price = 0;

    for (const Cargo& cargo : DangerousCargoTruck::cargo_)
        price += cargo.getPrice().getCents();

    price += max_danger_level_ * 1500 + std::abs(temperature_ - 20) * 200 + DangerousCargoTruck::max_reach_ * 200;
    price += price * DangerousCargoTruck::taxes_;
    DangerousCargoTruck::price_ = Currency(price);
}

DangerousRefrigeratorTruck::DangerousRefrigeratorTruck(const Truck &truck): RefrigeratorTruck(truck), DangerousCargoTruck(truck) {}

DangerousRefrigeratorTruck::DangerousRefrigeratorTruck(const RefrigeratorTruck &truck): RefrigeratorTruck(truck), DangerousCargoTruck(truck) {}

DangerousRefrigeratorTruck::DangerousRefrigeratorTruck(const DangerousCargoTruck &truck): RefrigeratorTruck(truck), DangerousCargoTruck(truck) {}

DangerousRefrigeratorTruck::DangerousRefrigeratorTruck(const DangerousRefrigeratorTruck &truck): RefrigeratorTruck(truck), DangerousCargoTruck(truck) {}

DangerousRefrigeratorTruck::DangerousRefrigeratorTruck(unsigned int max_weight, unsigned int max_reach, float taxes,
                                                       float temperature, Cargo::DangerLevel max_danger_level):
                                                       RefrigeratorTruck(max_weight, max_reach, taxes, temperature),
                                                       DangerousCargoTruck(max_weight, max_reach, taxes, max_danger_level){}

Truck::Type DangerousRefrigeratorTruck::get_type() const { return Truck::Type::DangerousRefrigerator; }

bool DangerousRefrigeratorTruck::addCargo(const Cargo &cargo) {
    Cargo::Type type = cargo.getType();

    if (type == Cargo::Type::Animal)
        throw std::invalid_argument("Invalid cargo (cargo type not supported by this truck).");

    if (type == Cargo::Type::Normal)
        if (temperature_ < 10 || temperature_ > 30)
            throw std::invalid_argument("Invalid cargo (normal cargo that is transported at ambient temperature on a refrigerator truck that isn't at ambient temperature.)");

    if (cargo.getDangerLevel() > max_danger_level_)
        throw std::invalid_argument("Invalid cargo (truck can't transport cargo with this danger level).");


    if (cargo.getMinTemp() > temperature_ || cargo.getMaxTemp() < temperature_)
        throw std::invalid_argument("Invalid cargo (temperature range needed for cargo not supported by this truck)");

    if (DangerousCargoTruck::getTotalWeight() + cargo.getWeight()*cargo.getQuantity() > DangerousCargoTruck::max_weight_)
        return 1;

    DangerousCargoTruck::cargo_.push_back(cargo);
    return 0;
}