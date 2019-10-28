/**
 * @file truck.h
 *
 *
 */

#ifndef TRUCK_H_INCLUDED
#define TRUCK_H_INCLUDED

#include "currency.h"

#include <vector>
#include <utility>

/**
 * @brief Dangerous Goods Classification.
 */
enum DangerLevel {
    Explosives = 1,
    Gases,
    Flammable_Liq,
    Flammable_Sol,
    Oxydizing_Agents,
    Toxic,
    Radioactive,
    Corrosive,
    Miscellaneous
};

/**
 * @class %Truck
 * @brief Superclass of all transports of the company.
 */
class Truck {
protected:
    std::vector<Event> logs_;
    unsigned int max_capacity_;
    Currency price_;
    unsigned int max_reach_;
    double taxes_;

public:
    class Event;

    /**
     * @brief Constructor of all information of a general truck.
     * @param max_capacity  Maximum capacity of truck
     * @param price         Price for the transport of merchandise
     * @param max_reach     Maximum distance the truck can travel
     * @param taxes         Tax that needs to be paid
     * @see   %Currency
     */
    Truck(unsigned int max_capacity, const Currency &price,
          unsigned int max_reach,          double   taxes);

    /**
     * @brief Get price of the transport.
     * @return  %Currency price
     */
    virtual Currency getPrice() const = 0;

    /**
     * @brief Types of trucks
     */
    enum Type {
        Refrigerator,
        DangerousCargo,
        Animal,
        Normal
    };

    /**
     * @brief Get type of truck.
     * @return  %Truck type
     */
    virtual Truck::Type get_type() const = 0;
};

/**
 * @class %RefrigeratorTruck
 * @brief Truck with freezing camera allowing transport of products that require specific temperature ranges.
 */
class RefrigeratorTruck : public Truck {
private:
    std::pair<float, float> temperature_range_;

public:
    /**
     * @brief Constructor of all information of a refrigerator truck.
     * @param max_capacity      Maximum capacity of truck
     * @param price             Price for the transport of merchandise
     * @param max_reach         Maximum distance the truck can travel
     * @param taxes             Tax that needs to be paid
     * @param temperature_range Pair containing the temperature range
     * @see   %Currency
     */
    RefrigeratorTruck(unsigned int max_capacity, const Currency &price,
                      unsigned int max_reach,          double   taxes,
                      const    std::pair<float, float> &temperature_range);

    /**
     * @brief Constructor of all information of a refrigerator truck.
     * @param max_capacity      Maximum capacity of truck
     * @param price             Price for the transport of merchandise
     * @param max_reach         Maximum distance the truck can travel
     * @param taxes             Tax that needs to be paid
     * @param min_temp          Minimum temperature of freezing camera
     * @param max_temp          Maximum temperature of freezing camera
     * @see   %Currency
     */
    RefrigeratorTruck(unsigned int max_capacity, const Currency &price,
                      unsigned int max_reach,          double   taxes,
                      float        min_temp,           float    max_temp);

    /**
     * @brief Get price for service involving refrigeration.
     * @return  %Currency price
     */
    Currency getPrice() const;

    /**
     * @brief Get type of truck.
     * @return  %Truck::Type::Refrigerator
     */
    Truck::Type get_type() const;

};

/**
 * @class   %DangerousCargoTruck
 * @brief Truck that has capacity of transporting dangerous goods.
 */
class DangerousCargoTruck : public Truck {
private:
    DangerLevel danger_level_;

public:
    /**
     * @brief Constructor of all information of a dangerous cargo truck.
     * @param max_capacity      Maximum capacity of truck
     * @param price             Price for the transport of merchandise
     * @param max_reach         Maximum distance the truck can travel
     * @param taxes             Tax that needs to be paid
     * @param danger_level      Classification of dangerous good being transported
     * @see   %Currency
     */
    DangerousCargoTruck(unsigned int max_capacity, const Currency &price,
                        unsigned int max_reach,          double   taxes,
                        DangerLevel  danger_level);

    /**
     * @brief Get price for service involving dangerous goods.
     * @return  %Currency price
     */
    Currency getPrice() const;

    /**
     * @brief Get danger level of merchandise transported by the truck
     * @return  %DangerLevel level
     */
    DangerLevel getDangerLevel() const;

    /**
     * @brief Get type of truck.
     * @return  %Truck::Type::DangerousCargo
     */
    Truck::Type get_type() const;
};

/**
 * @class   %AnimalTruck
 * @brief Truck that has capacity of transporting animals.
 */
class AnimalTruck : public Truck {
private:
    unsigned int animal_weight_;

public:
    /**
     * @brief Constructor of all information of a animal transport truck.
     * @param max_capacity      Maximum capacity of truck
     * @param price             Price for the transport of merchandise
     * @param max_reach         Maximum distance the truck can travel
     * @param taxes             Tax that needs to be paid
     * @param animal_weight     Weight of an individual animal being transported
     * @see   %Currency
     */
    AnimalTruck(unsigned int max_capacity, const Currency &price,
                unsigned int max_reach,          double   taxes,
                unsigned int animal_weight);

    /**
     * @brief Get price for service involving animal transport.
     * @return  %Currency price
     */
    Currency getPrice() const;

    /**
     * @brief Get type of truck.
     * @return  %Truck::Type::Animal
     */
    Truck::Type get_type() const

};

class NormalTruck : public Truck {
public:
    /**
     * @brief Constructor of all information of a normal truck.
     * @param max_capacity      Maximum capacity of truck
     * @param price             Price for the transport of merchandise
     * @param max_reach         Maximum distance the truck can travel
     * @param taxes             Tax that needs to be paid
     * @see   %Currency
     */
    NormalTruck(unsigned int max_capacity, const Currency &price,
                unsigned int max_reach,          double   taxes);

    /**
     * @brief Get price for normal service.
     * @return  %Currency price
     */
    Currency getPrice() const;

    /**
     * @brief Get type of truck.
     * @return  %Truck::Type::Normal
     */
    Truck::Type get_type() const;

};



#endif /* end of include guard: TRUCK_H_INCLUDED */
