#include "../include/Cargo.h"

#include <cmath>
#include <algorithm>

Cargo::InvalidTemperatureRange::InvalidTemperatureRange(std::pair<float, float> temperature_range):
    std::invalid_argument("One of the values of the range is invalid (range must have minimum temperature lower or equal to maximum temperature)"),
    temperature_range_(temperature_range){}

Cargo::InvalidTemperatureRange::InvalidTemperatureRange(float min_temp, float max_temp):
    std::invalid_argument("One of the values of the range is invalid (range must have minimum temperature lower or equal to maximum temperature)"),
    temperature_range_(min_temp, max_temp){}

std::pair<float, float> Cargo::InvalidTemperatureRange::getTemperatureRange() const { return temperature_range_; }

Cargo::InvalidWeight::InvalidWeight(float weight):
    std::invalid_argument("Weight value is invalid (weight of cargo must be greater or equal than 0)"),
    weight_(weight){}

float Cargo::InvalidWeight::getWeight() const { return weight_; }

Cargo::Cargo(): quantity_(0), cargo_type_(Cargo::Type::Normal),
                danger_level_(Cargo::DangerLevel::None), weight_(0.0f),
                temperature_range_(0.0f, 0.0f){}

Cargo::Cargo(unsigned int       quantity,     Cargo::Type cargo_type,
             Cargo::DangerLevel danger_level, float       weight,
             std::pair<float, float> temperature_range):
             quantity_(quantity), cargo_type_(cargo_type),
             danger_level_(danger_level) {

            if (weight < 0) throw InvalidWeight(weight);

            if (temperature_range.first > temperature_range.second) throw InvalidTemperatureRange(temperature_range);

            weight_ = weight;
            temperature_range_ = temperature_range;
}

Cargo::Cargo(unsigned int       quantity,     Cargo::Type cargo_type,
             Cargo::DangerLevel danger_level, float       weight,
             float              min_temp,     float       max_temp):
             quantity_(quantity), cargo_type_(cargo_type),
             danger_level_(danger_level) {

             if (weight < 0) throw InvalidWeight(weight);

             if (min_temp > max_temp) throw InvalidTemperatureRange(min_temp, max_temp);

             weight_ = weight;
             temperature_range_.first = min_temp;
             temperature_range_.second = max_temp;
}

unsigned int Cargo::getQuantity() const { return quantity_; }

void Cargo::setQuantity(unsigned int quantity) { quantity_ = quantity; }

float Cargo::getWeight() const { return weight_; }

void Cargo::setWeight(float weight) {
    if (weight < 0) throw InvalidWeight(weight);
    weight_ = weight;
}

Cargo::Type Cargo::getType() const { return cargo_type_; }

void Cargo::setType(Cargo::Type cargo_type) { cargo_type_ = cargo_type; }

Cargo::DangerLevel Cargo::getDangerLevel() const { return danger_level_; }

void Cargo::setDangerLevel(Cargo::DangerLevel danger_level) { danger_level_ = danger_level; }

std::pair<float, float> Cargo::getTemperatureRange() const { return temperature_range_; }

float Cargo::getMinTemp() { return temperature_range_.first; }

float Cargo::getMaxTemp() { return temperature_range_.second; }

void Cargo::setTemperatureRange(const std::pair<float, float> &temperature_range) {
    if (temperature_range.first > temperature_range.second) throw InvalidTemperatureRange(temperature_range);

    temperature_range_ = temperature_range;
}

void Cargo::setTemperatureRange(float min_temp, float max_temp) {
    if (min_temp > max_temp) throw InvalidTemperatureRange(min_temp, max_temp);

    temperature_range_.first = min_temp;
    temperature_range_.second = max_temp;
}

void Cargo::setMinTemp(float min_temp) {
    if (min_temp > temperature_range_.second) throw InvalidTemperatureRange(min_temp, temperature_range_.second);

    temperature_range_.first = min_temp;
}

void Cargo::setMaxTemp(float max_temp) {
    if (max_temp < temperature_range_.first) throw InvalidTemperatureRange(temperature_range_.first, max_temp);

    temperature_range_.second = max_temp;
}

Currency Cargo::getPrice(void) const {
    return Currency(quantity_ * (weight_ * 20 + cargo_type_ * cargo_type_ * 100 + danger_level_ * 1000 +
                    100/(1+temperature_range_.second - temperature_range_.first)*std::max(std::abs(temperature_range_.first-20), std::abs(temperature_range_.second-20))));
}