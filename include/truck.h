/**
 * @file truck.h
 */

#ifndef TRUCK_H_INCLUDED
#define TRUCK_H_INCLUDED

#include "currency.h"
#include "Cargo.h"

#include <vector>
#include <utility>

/**
 * @brief Superclass of all transports of the company.
 * @ref   Cargo
 * @ref   Currency
 */
class Truck {
public:
    typedef std::string NumberPlate;
    typedef std::string Category;
    typedef std::string Fuel;
private:
    //std::vector<Event> logs_;
    NumberPlate number_plate_;
    Time plate_register_date_;
    std::string fuel_;
    float max_reach_;
    Category category_ //A,B,C,D

    //second in pair is cost per kilometer of transporting a given Cargo
    std::vector< std::pair<Cargo, Currency> > cargo_;

public:
    /**
     * @brief Copy Constructor.
     * @param truck Truck that will be used to form the new truck
     */
    Truck(const Truck& truck);

    /**
     * @brief Constructor of all information of a general truck.
     * @param max_weight    Maximum weight the truck can transport
     * @param max_reach     Maximum distance for the transport
     * @param taxes         Tax that needs to be paid
     */
    Truck(const NumberPlate &number_plate, const Time &plate_register_date,
          const );

    /**
     * @brief Gets the maximum weight the truck can transport
     * @return Maximum weight
     */
    unsigned int getMaxWeight(void) const;

    /**
     * @brief Sets the maximum weight the truck can transport
     * @param max_weight Maximum weight to be set to
     */
    void setMaxWeight(unsigned int max_weight);

    /**
     * @brief Get price of the transport.
     * @return  Currency price
     */
    Currency getPrice();

    /**
     * @brief Gets the current total weight in the truck.
     * @return Total weight of cargo
     */
    float getTotalWeight(void) const;

    /**
     * @brief Get type of truck.
     * @return  Truck type
     */
    virtual Truck::Type get_type(void) const = 0;

    /**
     * @brief Adds cargo to the truck
     * @param cargo Cargo to be added
     * @throws <em>std::invalid_argument</em> If cargo is invalid for this type of truck
     * @return 0 if cargo was added, non-zero if not added but cargo is valid
     */
    virtual bool addCargo(const Cargo& cargo) = 0;

    /**
     * @brief Removes cargo from truck
     * @return Iterator to the next cargo
     * @throws InvalidIterator If iterator is out of the range
     */
    std::vector<Cargo>::iterator removeCargo(std::vector<Cargo>::const_iterator it);

    /**
     * @brief Removes all cargo from truck
     */
    void clearCargo(void);

    /**
     * @brief Get an iterator to the begin of the cargo of the truck
     * @return <em>cargo.begin()</em> Begin of the cargo
     */
    std::vector<Cargo>::iterator cargoBegin(void);

    /**
     * @brief Get an iterator to the end of the cargo of the truck
     * @return <em>cargo.end()</em> End of the cargo
     */
    std::vector<Cargo>::iterator cargoEnd(void);
};

/**
 * @class RefrigeratorTruck
 * @brief Truck with freezing camera allowing transport of products that require specific temperature ranges.
 */
class RefrigeratorTruck : public Truck {
protected:
    float temperature_;
private:
    /**
     * @brief Updates price values
     */
    void updatePrice(void);
public:

    /**
     * @brief Copy constructor.
     * As this constructor uses a general truck, temperature will be set to ambient temperature (20ºC).
     * @param truck Truck that will be used to form the new truck
     */
    RefrigeratorTruck(const Truck& truck);

    /**
     * @brief Copy Constructor.
     * @param truck RefrigeratorTruck that will be used to form the new truck
     */
    RefrigeratorTruck(const RefrigeratorTruck& truck);

    /**
     * @brief Constructor of all information of a refrigerator truck.
     * @param max_weight    Maximum weight the truck can transport
     * @param max_reach     Maximum distance for the transport
     * @param taxes         Tax that needs to be paid
     * @param temperature   Temperature of the refrigerator camera
     */
    RefrigeratorTruck(unsigned int max_weight, unsigned int max_reach, float taxes, float temperature);

    /**
     * @brief Get type of truck.
     * @return  Truck::Type::Refrigerator
     */
    Truck::Type get_type(void) const;

    /**
     * @brief Gets the temperature of the refrigerator camera.
     * @return Temperature of camera
     */
    float getTemperature(void) const;

    /**
     * @brief Sets the temperature of the refrigerator camera to new value given.
     * @param temperature Temperature to be set to
     */
    void setTemperature(float temperature);

    /**
     * @brief Adds cargo to the truck
     * Cargo temperature range must contain the temperature of the camera and danger level below or equal <em>Cargo::DangerLevel::Miscellaneous</em> to be added
     * @param cargo Cargo to be added
     * @throws <em>std::invalid_argument</em> If cargo is invalid for this type of truck
     * @return 0 if cargo was added, non-zero if not added but cargo is valid
     */
    bool addCargo(const Cargo& cargo);

};

/**
 * @class   DangerousCargoTruck
 * @brief Truck that has capacity of transporting dangerous goods.
 */
class DangerousCargoTruck : public Truck {
protected:
    Cargo::DangerLevel max_danger_level_;
private:
    /**
     * @brief Updates price values
     */
    void updatePrice(void);
public:
    /**
     * @brief Copy constructor.
     * As this constructor uses a general truck, the maximum danger level will be set to <em>Cargo::DangerLevel::Gases</em>.
     * @param truck Truck that will be used to form the new truck
     */
    DangerousCargoTruck(const Truck& truck);

    /**
     * @brief Copy Constructor.
     * @param truck DangerousCargoTruck that will be used to form the new truck
     */
    DangerousCargoTruck(const DangerousCargoTruck& truck);

    /**
     * @brief Constructor of all information of a dangerous cargo truck.
     * @param max_weight        Maximum weight the truck can transport
     * @param max_reach         Maximum distance for the transport
     * @param taxes             Tax that needs to be paid
     * @param max_danger_level  Maximum danger level the truck is capable of transporting
     */
    DangerousCargoTruck(unsigned int max_weight, unsigned int max_reach, float taxes, Cargo::DangerLevel max_danger_level);

    /**
     * @brief Get type of truck.
     * @return  Truck::Type::DangerousCargo
     */
    Truck::Type get_type(void) const;

    /**
     * @brief Gets the maximum danger level of cargo that the truck can transport
     * @return Maximum danger level
     */
    Cargo::DangerLevel getMaxDangerLevel(void) const;

    /**
     * @brief Sets the maximum danger level of cargo the truck can transport
     * @param max_danger_level Maximum danger level to be set to
     */
    void setMaxDangerLevel(Cargo::DangerLevel max_danger_level);

    /**
     * @brief Adds cargo to the truck
     * Cargo danger level range must be lower or equal to the maximum danger level the truck is able to transport to be added.
     * @param cargo Cargo to be added
     * @throws <em>std::invalid_argument</em> If cargo is invalid for this type of truck
     * @return 0 if cargo was added, non-zero if not added but cargo is valid
     */
    bool addCargo(const Cargo& cargo);
};

/**
 * @class   %AnimalTruck
 * @brief Truck that has capacity of transporting animals.
 */
class AnimalTruck : public Truck {

    /**
     * @brief Updates price values
     */
    void updatePrice(void);
public:
    /**
     * @brief Copy constructor.
     * @param truck Truck that will be used to form the new truck
     */
    AnimalTruck(const Truck& truck);

    /**
     * @brief Constructor of all information of a animal truck.
     * @param max_weight    Maximum weight the truck can transport
     * @param max_reach     Maximum distance for the transport
     * @param taxes         Tax that needs to be paid
     */
    AnimalTruck(unsigned int max_weight, unsigned int max_reach, float taxes);

    /**
     * @brief Get type of truck.
     * @return  Truck::Type::Animal
     */
    Truck::Type get_type() const;

    /**
     * @brief Adds cargo to the truck
     * Cargo danger level range must be lower or equal <em>Cargo::DangerLevel::Miscellaneous</em> to be added.
     * @param cargo Cargo to be added
     * @throws <em>std::invalid_argument</em> If cargo is invalid for this type of truck
     * @return 0 if cargo was added, non-zero if not added but cargo is valid
     */
    bool addCargo(const Cargo& cargo);


};

class NormalTruck : public Truck {

    /**
     * @brief Updates price values
     */
    void updatePrice(void);
public:
    /**
     * @brief Copy constructor.
     * @param truck Truck that will be used to form the new truck
     */
    NormalTruck(const Truck& truck);

    /**
     * @brief Constructor of all information of a normal truck.
     * @param max_weight    Maximum weight the truck can transport
     * @param max_reach     Maximum distance for the transport
     * @param taxes         Tax that needs to be paid
     */
    NormalTruck(unsigned int max_weight, unsigned int max_reach, float taxes);

    /**
     * @brief Get type of truck.
     * @return  Truck::Type::Normal
     */
    Truck::Type get_type() const;

    /**
     * @brief Adds cargo to the truck
     * Cargo danger level range must be lower or equal <em>Cargo::DangerLevel::None</em> to be added.
     * @param cargo Cargo to be added
     * @throws <em>std::invalid_argument</em> If cargo is invalid for this type of truck
     * @return 0 if cargo was added, non-zero if not added but cargo is valid
     */
    bool addCargo(const Cargo& cargo);

};

class DangerousRefrigeratorTruck: public DangerousCargoTruck, protected RefrigeratorTruck {
    /**
     * @brief Updates price values
     */
    void updatePrice(void);
public:

    /**
     * @brief Copy constructor.
     * As this constructor uses a general truck, the maximum danger level will be set to <em>Cargo::DangerLevel::Gases</em>
     * and the temperature to ambient temperature (20ºC).
     * @param truck Truck that will be used to form the new truck
     */
    DangerousRefrigeratorTruck(const Truck& truck);

    /**
     * @brief Copy constructor.
     * As this constructor uses a refrigerator truck, the maximum danger level will be set to <em>Cargo::DangerLevel::Gases</em>.
     * @param truck RefrigeratorTruck that will be used to form the new truck
     */
    DangerousRefrigeratorTruck(const RefrigeratorTruck& truck);

    /**
     * @brief Copy Constructor.
     * As this constructor uses a dangerous cargo truck, temperature will be set to ambient temperature (20ºC)
     * @param truck DangerousCargoTruck that will be used to form the new truck
     */
    DangerousRefrigeratorTruck(const DangerousCargoTruck& truck);

    /**
     * @brief Copy Constructor.
     * @param truck DangerousRefrigeratorTruck that will be used to form the new truck
     */
    DangerousRefrigeratorTruck(const DangerousRefrigeratorTruck& truck);

    /**
     * @brief Constructor of all information of a refrigerator truck.
     * @param max_weight    Maximum weight the truck can transport
     * @param max_reach     Maximum distance for the transport
     * @param taxes         Tax that needs to be paid
     * @param temperature   Temperature of the refrigerator camera
     * @param max_danger_level  Maximum danger level the truck is capable of transporting
     */
    DangerousRefrigeratorTruck(unsigned int max_weight, unsigned int max_reach, float taxes, float temperature, Cargo::DangerLevel max_danger_level);

    /**
     * @brief Get type of truck.
     * @return  Truck::Type::DangerousRefrigerator
     */
    Truck::Type get_type() const;

    /**
     * @brief Adds cargo to the truck
     * Cargo danger level range must be lower or equal to the maximum danger level the truck is able to transport and
     * the temperature range of the cargo must contain the temperature of the camera of the truck to be added.
     * @param cargo Cargo to be added
     * @throws <em>std::invalid_argument</em> If cargo is invalid for this type of truck
     * @return 0 if cargo was added, non-zero if not added but cargo is valid
     */
    bool addCargo(const Cargo& cargo);
};


#endif /* end of include guard: TRUCK_H_INCLUDED */
