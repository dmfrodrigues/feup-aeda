/**
 * @file Cargo.h
 */

#ifndef CARGO_H_INCLUDED
#define CARGO_H_INCLUDED

#include "currency.h"

#include <utility>
#include <stdexcept>

/**
 * @brief Cargo
 */
class Cargo {
public:
    /**
     * @enum Type
     * @brief Types of cargo
     */
    enum Type {
        Normal = 0,
        Animal,
        Refrigerated,
        Dangerous,
    };

    /**
     * @enum DangerLevel
     * @brief Dangerous Goods Classification.
     */
    enum DangerLevel {
        None = 0,
        Miscellaneous,
        Gases,
        Flammable_Liq,
        Flammable_Sol,
        Oxydizing_Agents,
        Explosives,
        Corrosive,
        Toxic,
        Radioactive,
    };
private:
    unsigned int quantity_;
    Type cargo_type_;
    DangerLevel danger_level_;
    float weight_; /// @brief Weight of an unit, total weight will be determined by the quantity and weight of an unit.
    std::pair<float, float> temperature_range_; /// @brief Range of temperature that cargo must be kept on.

public:

    /**
     * @brief Exception class for invalid temperature ranges
     */
    class InvalidTemperatureRange: public std::invalid_argument {
    private:
        std::pair<float, float> temperature_range_;
    public:
        /**
         * @brief Constructor accepting the pair of temperatures that caused the exception.
         * Sets the string returned by <em> std::exception::what() </em>.
         * @param temperature_range Temperature range
         */
        InvalidTemperatureRange(std::pair<float, float> temperature_range);
        /**
         * @brief Constructor accepting the pair of temperatures as separate values that caused the exception.
         * Sets the string returned by <em> std::exception::what() </em>.
         * @param min_temp Minimum temperature
         * @param max_temp Maximum temperature
         */
        InvalidTemperatureRange(float min_temp, float max_temp);

        /**
         * @brief Gets the temperature range from which the exception was built.
         * @return Temperature range as a pair
         */
        std::pair<float, float> getTemperatureRange(void) const;
    };

    /**
     * @brief Invalid weight exception
     */
    class InvalidWeight: public std::invalid_argument {
    private:
        float weight_;
    public:
        /**
         * @brief Constructor accepting the value of weight that caused the exception.
         * Sets the string returned by <em> std::exception::what() </em>.
         * @param weight Weight value that caused exception
         */
        InvalidWeight(float weight);

        /**
         * @brief Gets the weight value from which the exception was built.
         * @return Weight
         */
        float getWeight(void) const;
    };

    /**
     * @brief Default constructor.
     */
    Cargo();

    /**
     * @brief Constructs a cargo.
     * @param quantity Quantity of cargo
     * @param cargo_type Type of cargo
     * @param danger_level Danger level of the cargo
     * @param weight Weight of an unit of cargo
     * @param temperature_range Range of temperature that cargo must be kept on
     * @ref DangerLevel
     * @throws InvalidTemperatureRange If the temperature range is invalid.
     * @throws InvalidWeight If the weight value is invalid.
     */
    Cargo(unsigned int          quantity,     Cargo::Type  cargo_type,
          Cargo::DangerLevel    danger_level, float        weight,
          std::pair<float, float> temperature_range);

    /**
     * @brief Constructs a cargo.
     * @param quantity Quantity of cargo
     * @param cargo_type Type of cargo
     * @param danger_level Danger level of the cargo
     * @param weight Weight of an unit of cargo
     * @param min_temp Minimum temperature that cargo must be kept on
     * @param max_temp Maximum temperature that cargo must be kept on
     * @ref DangerLevel
     * @throws InvalidTemperatureRange If the temperature range is invalid.
     * @throws InvalidWeight If the weight value is invalid.
     */
    Cargo(unsigned int          quantity,     Cargo::Type  cargo_type,
          Cargo::DangerLevel    danger_level, float        weight,
          float                 min_temp,     float        max_temp);

    /**
     * @brief Gets the quantity of cargo.
     * @return Quantity
     */
    unsigned int getQuantity(void) const;

    /**
     * @brief Sets the quantity of cargo.
     * @param quantity Quantity of cargo to be set to
     */
    void setQuantity(unsigned int quantity);

    /**
     * @brief Gets the value of the weight of an unit of cargo.
     * @return Weight
     */
    float getWeight(void) const;

    /**
     * @brief Sets the weight of an unit of cargo.
     * @param weight Weight to be set to
     * @throws InvalidWeight If the weight value is invalid.
     */
    void setWeight(float weight);

    /**
     * @brief Gets the type of cargo.
     * @return Type of cargo
     */
    Cargo::Type getType(void) const;

    /**
     * @brief Sets the type of cargo.
     * @param cargo_type Type of cargo to be set to
     * @throws <em>std::invalid_argument</em> If type can't be modified
     */
    void setType(Cargo::Type cargo_type);

    /**
     * @brief Gets the danger level of cargo
     * @return Danger Level of cargo
     */
    Cargo::DangerLevel getDangerLevel(void) const;

    /**
     * @brief Sets the danger level of cargo.
     * @param danger_level Danger level of cargo to be set to
     * @throws <em>std::invalid_argument</em> If danger level can't be modified
     */
    void setDangerLevel(Cargo::DangerLevel danger_level);

    /**
     * @brief Gets the temperature range that cargo must be kept on.
     * @return Temperature range
     */
    std::pair<float, float> getTemperatureRange(void) const;

    /**
     * @brief Gets the minimum temperature that cargo must be kept on.
     * @return Minimum temperature
     */
    float getMinTemp(void) const;

    /**
     * @brief Gets the maximum temperature that cargo must be kept on.
     * @return Maximum temperature
     */
    float getMaxTemp(void) const;

    /**
     * @brief Sets the temperature range to the pair of temperatures given.
     * @param temperature_range Temperature range that cargo must be kept on.
     * @throws InvalidTemperatureRange If the temperature range is invalid.
     * @throws <em>std::invalid_argument</em> If temperature range can't be modified
     */
    void setTemperatureRange(const std::pair<float, float> &temperature_range);

    /**
     * @brief Sets the temperature range to the pair of temperatures given.
     * @param min_temp Minimum temperature that cargo must be kept on
     * @param max_temp Maximum temperature that cargo must be kept on
     * @throws InvalidTemperatureRange If the temperature range is invalid.
     * @throws <em>std::invalid_argument</em> If temperature range can't be modified
     */
    void setTemperatureRange(float min_temp, float max_temp);

    /**
     * @brief Sets the minimum temperature of the range to the value given.
     * @param min_temp Minimum temperature that cargo must be kept on
     * @throws InvalidTemperatureRange If the temperature range is invalid.
     * @throws <em>std::invalid_argument</em> If temperature range can't be modified
     */
    void setMinTemp(float min_temp);

    /**
     * @brief Sets the minimum temperature of the range to the value given.
     * @param max_temp Minimum temperature that cargo must be kept on
     * @throws InvalidTemperatureRange If the temperature range is invalid.
     * @throws <em>std::invalid_argument</em> If temperature range can't be modified
     */
    void setMaxTemp(float max_temp);

    /**
     * @brief Gets the costs for transportation of cargo
     * @return Price of cargo
     */
    Currency getPrice(void) const;
};

#endif // CARGO_H_INCLUDED
