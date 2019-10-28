#include "../include/truck.h"

/* Truck Superclass */

Truck::Truck(unsigned int max_capacity, const Currency &price,
             unsigned int max_reach,          double   taxes):
             max_capacity_(max_capacity), price_(price),
             max_reach_(max_reach), taxes_(taxes) {}

/* Refrigerator Truck */

RefrigeratorTruck::RefrigeratorTruck(unsigned int max_capacity, const Currency &price,
                                     unsigned int max_reach,          double   taxes,
                                     const    std::pair<float, float> &temperature_range):
                                     max_capacity_(max_capacity), price_(price),
                                     max_reach_(max_reach), taxes_(taxes),
                                     temperature_range_(temperature_range){}

RefrigeratorTruck::RefrigeratorTruck(unsigned int max_capacity, const Currency &price,
                                     unsigned int max_reach,          double   taxes,
                                     float        min_temp,           float    max_temp):
                                     max_capacity_(max_capacity), price_(price),
                                     max_reach_(max_reach), taxes_(taxes),
                                     temperature_range_(std::makepair(min_temp, max_temp)){}

Currency RefrigeratorTruck::getPrice() const {
    return price_;
}

Truck::Type RefrigeratorTruck::Truck::get_type() const {
    return Truck::Type::Refrigerator;
}

/* Dangerous Cargo Truck */
DangerousCargoTruck::DangerousCargoTruck(unsigned int max_capacity, const Currency &price,
                                         unsigned int max_reach,          double   taxes,
                                         DangerLevel  danger_level):
                                         max_capacity_(max_capacity), price_(price),
                                         max_reach_(max_reach), taxes_(taxes),
                                         danger_level_(danger_level){}

Currency DangerousCargoTruck::getPrice() const {
    return price_;
}

Truck::Type DangerousCargoTruck::Truck::get_type() const {
    return Truck::Type::DangerousCargo;
}

/* Animal Truck */
AnimalTruck::AnimalTruck(unsigned int max_capacity, const Currency &price,
                         unsigned int max_reach,          double   taxes,
                         unsigned int animal_weight):
                         max_capacity_(max_capacity), price_(price),
                         max_reach_(max_reach), taxes_(taxes),
                         animal_weight_(animal_weight){}

Currency AnimalTruck::getPrice() const {
    return price_;
}

Truck::Type AnimalTruck::get_type() const {
    return Truck::Type::Animal;
}

/* Normal Truck */
NormalTruck(unsigned int max_capacity, const Currency &price,
            unsigned int max_reach,          double   taxes):
            max_capacity_(max_capacity), price_(price),
            max_reach_(max_reach), taxes_(taxes){}

Currency NormalTruck::getPrice() const {
    return price_;
}

Truck::Type NormalTruck::get_type() const {
    return Truck::Type::Normal;
}