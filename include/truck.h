/**
 * @file truck.h
 */

#ifndef TRUCK_H_INCLUDED
#define TRUCK_H_INCLUDED

#include "currency.h"
#include "cargo.h"
#include "Time.h"

#include <vector>
#include <utility>

/**
 * @brief Superclass of all transports of the company.
 * @ref   Cargo
 * @ref   Currency
 */

typedef utils::ufloat<float> Distance;

class Truck {
public:
    /** @brief Class to store number plates. */
    class NumberPlate{
    public:
        class Number: public utils::string_regex{
        public:
            /** @brief   Regular expression string that describes a valid number plate. */
            static const std::string REGEX_STR;
            /** @brief   Empty constructor. */
            explicit Number();
            /**
             * @brief   Constructs from string containing number plate.
             * @param   number  String with numberplate
             */
            explicit Number(const std::string &plate);
            Number& operator=(const std::string &s);
        };
        /*
        enum Country : int{
            Portugal = 0
        };
        */
    private:
        Number number_;
        //Country country_;
    public:
        explicit NumberPlate();
        explicit NumberPlate(const Number &number);
        explicit operator std::string() const;
        bool operator< (const NumberPlate &n) const;
        bool operator==(const NumberPlate &n) const;

        friend std::istream& operator>>(std::istream &is,       NumberPlate &n);
        friend std::ostream& operator<<(std::ostream &os, const NumberPlate &n);
    };
    class Category: public utils::string_regex{
    public:
        static const std::string REGEX_STR;
        explicit Category();
        explicit Category(const std::string &category);
        Category& operator=(const std::string &category);
    };
    enum Fuel : int{
        Gasoline = 0,
        Diesel,
        Biodiesel,
        Gas,
        Hydrogen,
        Electric,
        Hybrid
    };
    enum Type{
        truck
    };
private:
    //std::vector<Event> logs_;
    NumberPlate number_plate_;
    Time plate_register_date_;
    Fuel fuel_;
    Distance max_reach_;
    Category category_; //A,B,C,D

    //second in pair is cost per kilometer of transporting a given Cargo
    std::vector<CargoTrans*> cargo_;

public:
    Truck(){}
    /**
     * @brief Copy Constructor.
     * @param truck Truck that will be used to form the new truck
     */
    Truck(const Truck& t);
    /**
     * @brief Constructor of all information of a general truck.
     * @param max_weight    Maximum weight the truck can transport
     * @param max_reach     Maximum distance for the transport
     * @param taxes         Tax that needs to be paid
     */
    Truck(const NumberPlate &number_plate, const Time     &plate_register_date,
          const Fuel        &fuel        , const Distance &max_reach          ,
          const Category    &category    , std::vector<CargoTrans*> cargo);
    virtual ~Truck(){}

    const NumberPlate& get_id() const{ return number_plate_; }

    virtual Type get_type(void) const;

    static Fuel processFuel(const std::string &s);

    /** @brief   Overload of <em> operator>> </em>. */
    friend std::istream& operator>>(std::istream &is,       Truck &t);
    /** @brief   Overload of <em> operator<< </em>. */
    friend std::ostream& operator<<(std::ostream &os, const Truck &t);

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    bool in(std::istream &is, std::ostream &os);
};

#endif /* end of include guard: TRUCK_H_INCLUDED */
