/**
 * @file cargo.h
 */

#ifndef CARGO_H_INCLUDED
#define CARGO_H_INCLUDED

#include "currency.h"
#include "temperature.h"
#include "utils.h"

#include <utility>
#include <stdexcept>

typedef utils::ufloat<float> Weight;

/**
 * @brief Description of cargo that a client may request to transport.
 */
class Cargo {
    friend std::istream& input_Cargo (std::istream &is,       Cargo *&c);
    friend std::ostream& output_Cargo(std::ostream &os, const Cargo * c);
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
    static std::string type_string(const Type &t);
    static std::string dangerlevel_string(const DangerLevel &d);
private:
    Weight weight_; /// @brief Weight of an unit, total weight will be determined by the quantity and weight of an unit.
    std::string description_;
protected:
    virtual std::istream& input (std::istream &is);
    virtual std::ostream& output(std::ostream &os) const;
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
    virtual ~Cargo(){};

    const Weight&      get_weight     () const{ return weight_     ; }
    const std::string& get_description() const{ return description_; }

    virtual Cargo::Type get_type() const{ return Cargo::Type::Normal; }

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);
};

/**
 * @brief Description of animal cargo that a client may request to transport.
 */
class CargoAnimal: public Cargo{
    friend std::istream& input_Cargo (std::istream &is,       Cargo *&c);
    friend std::ostream& output_Cargo(std::ostream &os, const Cargo *c);
protected:
    virtual std::istream& input (std::istream &is);
    virtual std::ostream& output(std::ostream &os) const;
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

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);
};

/**
 * @brief Description of refrigerated cargo that a client may request to transport.
 */
class CargoRefrigerated: public Cargo{
    friend std::istream& input_Cargo (std::istream &is,       Cargo *&c);
    friend std::ostream& output_Cargo(std::ostream &os, const Cargo *c);
private:
    TemperatureRange temperature_range_; /// @brief Range of temperature that cargo must be kept on.
protected:
    virtual std::istream& input (std::istream &is);
    virtual std::ostream& output(std::ostream &os) const;
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
    const TemperatureRange& get_range() const{ return temperature_range_; }

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);
};

/**
 * @brief Description of dangerous cargo that a client may request to transport.
 */
class CargoDangerous: public Cargo{
    friend std::istream& input_Cargo (std::istream &is,       Cargo *&c);
    friend std::ostream& output_Cargo(std::ostream &os, const Cargo *c);
private:
    DangerLevel danger_level_;
protected:
    virtual std::istream& input (std::istream &is);
    virtual std::ostream& output(std::ostream &os) const;
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
    const Cargo::DangerLevel& get_dangerlevel() const{ return danger_level_; }

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);
};

/**
 * @brief Description of cargo that a truck can transport.
 */
class CargoTrans: public Cargo{
    friend std::istream& input_CargoTrans (std::istream &is,       CargoTrans *&c);
    friend std::ostream& output_CargoTrans(std::ostream &os, const CargoTrans *c);
private:
    static const Currency price_base_;
    Currency expenses_per_km_;
protected:
    virtual std::istream& input (std::istream &is);
    virtual std::ostream& output(std::ostream &os) const;
public:
    CargoTrans(){}
    CargoTrans(Weight weight, const std::string &description, Currency expenses_per_km);
    virtual const Currency& get_pricebase    () const{ return price_base_     ; }
    const Currency& get_expensesperkm() const{ return expenses_per_km_; }

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);
};

/**
 * @brief Description of animal cargo that a truck can transport.
 */
class CargoTransAnimal: public CargoTrans{
    friend std::istream& input_CargoTrans (std::istream &is,       CargoTrans *&c);
    friend std::ostream& output_CargoTrans(std::ostream &os, const CargoTrans *c);
private:
    static const Currency price_base_;
protected:
    virtual std::istream& input (std::istream &is);
    virtual std::ostream& output(std::ostream &os) const;
public:
    CargoTransAnimal():CargoTrans(){}
    CargoTransAnimal(Weight weight, const std::string &description, Currency expenses_per_km);
    virtual Cargo::Type get_type() const{ return Cargo::Type::Animal; }
    virtual const Currency& get_pricebase    () const{ return price_base_     ; }

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);
};

/**
 * @brief Description of refrigerated cargo that a truck can transport.
 */
class CargoTransRefrigerated: public CargoTrans{
    friend std::istream& input_CargoTrans (std::istream &is,       CargoTrans *&c);
    friend std::ostream& output_CargoTrans(std::ostream &os, const CargoTrans *c);
private:
    TemperatureRange temperature_range_;
    static const Currency price_base_;
    static const Temperature reference_temperature_;
    float temperature_factor_;
protected:
    virtual std::istream& input (std::istream &is);
    virtual std::ostream& output(std::ostream &os) const;
public:
    CargoTransRefrigerated():CargoTrans(){}
    CargoTransRefrigerated(Weight weight, const std::string &description, Currency expenses_per_km, float temperature_factor);
    virtual Cargo::Type get_type() const{ return Cargo::Type::Refrigerated; }
    const TemperatureRange& get_range() const{ return temperature_range_; }
    virtual const Currency& get_pricebase    () const{ return price_base_     ; }
    const Temperature& get_reference_temperature() const{ return reference_temperature_; }
    const float& get_temperaturefactor() const{ return temperature_factor_; }

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);
};

/**
 * @brief Description of dangerous that a truck can transport.
 */
class CargoTransDangerous: public CargoTrans{
    friend std::istream& input_CargoTrans (std::istream &is,       CargoTrans *&c);
    friend std::ostream& output_CargoTrans(std::ostream &os, const CargoTrans *c);
private:
    static const Currency price_base_;
    DangerLevel danger_level_;
protected:
    virtual std::istream& input (std::istream &is);
    virtual std::ostream& output(std::ostream &os) const;
public:
    CargoTransDangerous():CargoTrans(){}
    CargoTransDangerous(Weight weight, const std::string &description, Currency expenses_per_km, DangerLevel danger_level);
    virtual Cargo::Type get_type() const{ return Cargo::Type::Dangerous; }
    virtual const Currency& get_pricebase    () const{ return price_base_     ; }
    const Cargo::DangerLevel& get_dangerlevel() const{ return danger_level_; }

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);
};

#endif // CARGO_H_INCLUDED
