#include "Cargo.h"

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

void Cargo::setType(Cargo::Type cargo_type) {

    if (cargo_type == Cargo::Type::Animal || cargo_type == Cargo::Type::Refrigerated)
        if (danger_level_ > DangerLevel::Miscellaneous)
            throw std::invalid_argument("New cargo type doesn't support high danger level.");

    if (cargo_type == Cargo::Type::Normal)
        if (danger_level_ != DangerLevel::None)
            throw std::invalid_argument("New cargo type doesn't support any danger level (must be DangerLevel::None).");

    if (cargo_type != Cargo::Type::Refrigerated)
        if (temperature_range_.first > 30 || temperature_range_.second < 10)
            throw std::invalid_argument("New cargo type doesn't support this temperature range (must be around ambient temperature).");

    cargo_type_ = cargo_type;
}

Cargo::DangerLevel Cargo::getDangerLevel() const { return danger_level_; }

void Cargo::setDangerLevel(Cargo::DangerLevel danger_level) {

    if (cargo_type_ == Cargo::Type::Animal || cargo_type_ == Cargo::Type::Refrigerated)
        if (danger_level > DangerLevel::Miscellaneous)
            throw std::invalid_argument("New danger level isn't supported by this type of cargo.");

    if (cargo_type_ == Cargo::Type::Normal)
        if (danger_level != DangerLevel::None)
            throw std::invalid_argument("New danger level isn't supported by this type of cargo (must be DangerLevel::None).");

    danger_level_ = danger_level;
}

std::pair<float, float> Cargo::getTemperatureRange() const { return temperature_range_; }

float Cargo::getMinTemp() const { return temperature_range_.first; }

float Cargo::getMaxTemp() const { return temperature_range_.second; }

void Cargo::setTemperatureRange(const std::pair<float, float> &temperature_range) {
    if (temperature_range.first > temperature_range.second) throw InvalidTemperatureRange(temperature_range);

    if (cargo_type_ != Cargo::Type::Refrigerated)
        if (temperature_range.first > 30 || temperature_range.second < 10)
            throw std::invalid_argument("Temperature range not valid for this type of cargo, must be around ambient temperature.");

    temperature_range_ = temperature_range;
}

void Cargo::setTemperatureRange(float min_temp, float max_temp) {
    if (min_temp > max_temp) throw InvalidTemperatureRange(min_temp, max_temp);

    if (cargo_type_ != Cargo::Type::Refrigerated)
        if (min_temp > 30 || max_temp < 10)
            throw std::invalid_argument("Temperature range not valid for this type of cargo, must be around ambient temperature.");

    temperature_range_.first = min_temp;
    temperature_range_.second = max_temp;
}

void Cargo::setMinTemp(float min_temp) {
    if (min_temp > temperature_range_.second) throw InvalidTemperatureRange(min_temp, temperature_range_.second);

    if (cargo_type_ != Cargo::Type::Refrigerated)
        if (min_temp > 30)
            throw std::invalid_argument("Temperature range not valid for this type of cargo, must be around ambient temperature.");

    temperature_range_.first = min_temp;
}

void Cargo::setMaxTemp(float max_temp) {
    if (max_temp < temperature_range_.first) throw InvalidTemperatureRange(temperature_range_.first, max_temp);

    if (cargo_type_ != Cargo::Type::Refrigerated)
        if (max_temp < 10)
            throw std::invalid_argument("Temperature range not valid for this type of cargo, must be around ambient temperature.");

    temperature_range_.second = max_temp;
}

Currency Cargo::getPrice(void) const {
    return Currency(quantity_ * (weight_ * 20 + cargo_type_ * cargo_type_ * 100 + danger_level_ * 1000 +
                    100/(1+temperature_range_.second - temperature_range_.first)*std::max(std::abs(temperature_range_.first-20), std::abs(temperature_range_.second-20))));
}
