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

typedef float Temperature;
typedef std::pair<Temperature,Temperature> TemperatureRange;
typedef float Weight;

class Cargo {
    friend void input_Cargo (std::istream &is,       Cargo *c);
    friend void output_Cargo(std::ostream &os, const Cargo *c);
public:
    /**
     * @enum Type
     * @brief Types of cargo
     */
    enum Type : int {
        Normal = 0,
        Animal,
        Refrigerated,
        Dangerous,
    };

    /**
     * @enum DangerLevel
     * @brief Dangerous Goods Classification.
     */
    enum DangerLevel : int {
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
    Weight weight_; /// @brief Weight of an unit, total weight will be determined by the quantity and weight of an unit.
    std::string description_;
protected:
    virtual void input (std::istream &is);
    virtual void output(std::ostream &os) const;
public:
    /** @brief Default constructor. */
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
    Cargo(Weight weight, const std::string &description);

    virtual Cargo::Type get_type() const{ return Cargo::Type::Normal; }
};

class CargoAnimal: public Cargo{
    friend void input_Cargo (std::istream &is,       Cargo *c);
    friend void output_Cargo(std::ostream &os, const Cargo *c);
protected:
    virtual void input (std::istream &is);
    virtual void output(std::ostream &os) const;
public:
    CargoAnimal():Cargo(){}
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
    CargoAnimal(Weight weight, const std::string &description);

    virtual Cargo::Type get_type() const{ return Cargo::Type::Animal; }
};

class CargoRefrigerated: public Cargo{
    friend void input_Cargo (std::istream &is,       Cargo *c);
    friend void output_Cargo(std::ostream &os, const Cargo *c);
private:
    TemperatureRange temperature_range_; /// @brief Range of temperature that cargo must be kept on.
protected:
    virtual void input (std::istream &is);
    virtual void output(std::ostream &os) const;
public:
    CargoRefrigerated():Cargo(){}
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
    CargoRefrigerated(Weight weight, const std::string &description, TemperatureRange temperature_range);

    virtual Cargo::Type get_type() const{ return Cargo::Type::Refrigerated; }
};

class CargoDangerous: public Cargo{
    friend void input_Cargo (std::istream &is,       Cargo *c);
    friend void output_Cargo(std::ostream &os, const Cargo *c);
private:
    DangerLevel danger_level_;
protected:
    virtual void input (std::istream &is);
    virtual void output(std::ostream &os) const;
public:
    CargoDangerous():Cargo(){}
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
    CargoDangerous(Weight weight, const std::string &description, DangerLevel danger_level);

    virtual Cargo::Type get_type() const{ return Cargo::Type::Dangerous; }
};

class CargoTrans: public Cargo{
    friend void input_CargoTrans (std::istream &is,       CargoTrans *c);
    friend void output_CargoTrans(std::ostream &os, const CargoTrans *c);
private:
    static const Currency price_base_;
    Currency expenses_per_km_;
protected:
    virtual void input (std::istream &is);
    virtual void output(std::ostream &os) const;
public:
    CargoTrans(){}
    CargoTrans(Weight weight, const std::string &description, Currency expenses_per_km);
};
const Currency CargoTrans::price_base_(100.0);

class CargoTransAnimal: public CargoTrans{
    friend void input_CargoTrans (std::istream &is,       CargoTrans *c);
    friend void output_CargoTrans(std::ostream &os, const CargoTrans *c);
private:
    static const Currency price_base_;
protected:
    virtual void input (std::istream &is);
    virtual void output(std::ostream &os) const;
public:
    CargoTransAnimal():CargoTrans(){}
    CargoTransAnimal(Weight weight, const std::string &description, Currency expenses_per_km);
    virtual Cargo::Type get_type() const{ return Cargo::Type::Animal; }
};
const Currency CargoTransAnimal::price_base_(150.0);

class CargoTransRefrigerated: public CargoTrans{
    friend void input_CargoTrans (std::istream &is,       CargoTrans *c);
    friend void output_CargoTrans(std::ostream &os, const CargoTrans *c);
private:
    TemperatureRange temperature_range_;
    static const Currency price_base_;
    static const Temperature reference_temperature_;
    Currency expenses_per_deg_;
protected:
    virtual void input (std::istream &is);
    virtual void output(std::ostream &os) const;
public:
    CargoTransRefrigerated():CargoTrans(){}
    CargoTransRefrigerated(float weight, const std::string &description, Currency expenses_per_km, Currency expenses_per_deg);
    virtual Cargo::Type get_type() const{ return Cargo::Type::Refrigerated; }
};
const Currency CargoTransRefrigerated::price_base_(200.0);
const Temperature CargoTransRefrigerated::reference_temperature_(20.0);

class CargoTransDangerous: public CargoTrans{
    friend void input_CargoTrans (std::istream &is,       CargoTrans *c);
    friend void output_CargoTrans(std::ostream &os, const CargoTrans *c);
private:
    static const Currency price_base_;
    DangerLevel danger_level_;
protected:
    virtual void input (std::istream &is);
    virtual void output(std::ostream &os) const;
public:
    CargoTransDangerous():CargoTrans(){}
    CargoTransDangerous(float weight, const std::string &description, Currency expenses_per_km, DangerLevel danger_level);
    virtual Cargo::Type get_type() const{ return Cargo::Type::Dangerous; }
};
const Currency CargoTransDangerous::price_base_(300.0);

#endif // CARGO_H_INCLUDED
