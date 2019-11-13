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
    /// @brief Convert type to string to show in tables
    static std::string type_string(const Type &t);
    /// @brief Convert danger level to string to show in tables
    static std::string dangerlevel_string(const DangerLevel &d);
private:
    /// @brief Weight of an unit, total weight will be determined by the quantity and weight of an unit.
    Weight W_;
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
     * @param W Weight of an unit of cargo
     * @param Tr Range of temperature that cargo must be kept on
     * @ref DangerLevel
     * @throws InvalidTemperatureRange If the temperature range is invalid.
     * @throws InvalidWeight If the weight value is invalid.
     */
    Cargo(Weight W, const std::string &description);
    /** @brief Destructor */
    virtual ~Cargo(){};
    /// @brief Get weight
    const Weight&      get_W          () const{ return W_                ; }
    /// @brief Get description
    const std::string& get_description() const{ return description_      ; }
    /// @brief Get type
    virtual Cargo::Type get_type      () const{ return Cargo::Type::Normal; }

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
     * @param W Weight of an unit of cargo
     * @param Tr Range of temperature that cargo must be kept on
     * @ref DangerLevel
     * @throws InvalidTemperatureRange If the temperature range is invalid.
     * @throws InvalidWeight If the weight value is invalid.
     */
    CargoAnimal(Weight W, const std::string &description);
    /// @brief Get type
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
    TemperatureRange Tr_; /// @brief Range of temperature that cargo must be kept on.
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
     * @param W Weight of an unit of cargo
     * @param Tr Range of temperature that cargo must be kept on
     * @ref DangerLevel
     * @throws InvalidTemperatureRange If the temperature range is invalid.
     * @throws InvalidWeight If the weight value is invalid.
     */
    CargoRefrigerated(Weight W, const std::string &description, TemperatureRange Tr);
    /// @brief Get type
    virtual Cargo::Type get_type() const{ return Cargo::Type::Refrigerated; }
    /// @brief Get temperature range
    const TemperatureRange& get_Tr() const{ return Tr_; }

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
     * @param W Weight of an unit of cargo
     * @param Tr Range of temperature that cargo must be kept on
     * @ref DangerLevel
     * @throws InvalidTemperatureRange If the temperature range is invalid.
     * @throws InvalidWeight If the weight value is invalid.
     */
    CargoDangerous(Weight W, const std::string &description, DangerLevel danger_level);
    /// @brief Get type
    virtual Cargo::Type get_type() const{ return Cargo::Type::Dangerous; }
    /// @brief Get danger level
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
    static const Currency P_B_;
    double E_D_;
protected:
    virtual std::istream& input (std::istream &is);
    virtual std::ostream& output(std::ostream &os) const;
public:
    /** @brief Empty constructor */
    CargoTrans(){}
    CargoTrans(Weight W, const std::string &description, Currency E_D);
    /// @brief Get price base
    virtual const Currency& get_P_B    () const{ return P_B_     ; }
    /// @brief Get expenses per km
    const double& get_E_D() const{ return E_D_; }

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
    /// @brief Return true if this cargo description can carry a given cargo
    virtual bool can_carry(const Cargo *p) const;
    /// @brief Get real amount of expenses per km.
    virtual Currency get_E(Distance D, Weight W) const;
    /// @brief Get real price.
    virtual Currency get_P(Distance D, Weight W) const;
};

/**
 * @brief Description of animal cargo that a truck can transport.
 */
class CargoTransAnimal: public CargoTrans{
    friend std::istream& input_CargoTrans (std::istream &is,       CargoTrans *&c);
    friend std::ostream& output_CargoTrans(std::ostream &os, const CargoTrans *c);
private:
    static const Currency P_B_;
protected:
    virtual std::istream& input (std::istream &is);
    virtual std::ostream& output(std::ostream &os) const;
public:
    CargoTransAnimal():CargoTrans(){}
    CargoTransAnimal(Weight W, const std::string &description, Currency E_D);
    /// @brief Get type
    virtual Cargo::Type get_type() const{ return Cargo::Type::Animal; }
    virtual const Currency& get_P_B    () const{ return P_B_     ; }

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
    /// @brief Return true if this cargo description can carry a given cargo
    virtual bool can_carry(const Cargo *p) const;
    /// @brief Get real amount of expenses per km.
    virtual Currency get_E(Distance D, Weight W) const;
    /// @brief Get real price.
    virtual Currency get_P(Distance D, Weight W) const;
};

/**
 * @brief Description of refrigerated cargo that a truck can transport.
 */
class CargoTransRefrigerated: public CargoTrans{
    friend std::istream& input_CargoTrans (std::istream &is,       CargoTrans *&c);
    friend std::ostream& output_CargoTrans(std::ostream &os, const CargoTrans *c);
private:
    TemperatureRange Tr_;
    static const Currency P_B_;
    static const Temperature T0_;
    double E_T_;
protected:
    virtual std::istream& input (std::istream &is);
    virtual std::ostream& output(std::ostream &os) const;
public:
    CargoTransRefrigerated():CargoTrans(){}
    CargoTransRefrigerated(Weight W, const std::string &description, Currency E_D, float E_T);
    /// @brief Get type
    virtual Cargo::Type get_type() const{ return Cargo::Type::Refrigerated; }
    const TemperatureRange& get_Tr() const{ return Tr_; }
    virtual const Currency& get_P_B    () const{ return P_B_     ; }
    const Temperature& get_T0() const{ return T0_; }
    const double& get_E_T() const{ return E_T_; }

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
    /// @brief Return true if this cargo description can carry a given cargo
    virtual bool can_carry(const Cargo *p) const;
    /// @brief Get real amount of expenses.
    virtual Currency get_E(Distance D, Weight W) const;
    /// @brief Get real price.
    virtual Currency get_P(Distance D, Weight W) const;
};

/**
 * @brief Description of dangerous that a truck can transport.
 */
class CargoTransDangerous: public CargoTrans{
    friend std::istream& input_CargoTrans (std::istream &is,       CargoTrans *&c);
    friend std::ostream& output_CargoTrans(std::ostream &os, const CargoTrans *c);
private:
    static const Currency P_B_;
    DangerLevel danger_level_;
protected:
    virtual std::istream& input (std::istream &is);
    virtual std::ostream& output(std::ostream &os) const;
public:
    CargoTransDangerous():CargoTrans(){}
    CargoTransDangerous(Weight W, const std::string &description, Currency E_D, DangerLevel danger_level);
    /// @brief Get type
    virtual Cargo::Type get_type() const{ return Cargo::Type::Dangerous; }
    virtual const Currency& get_P_B    () const{ return P_B_     ; }
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
    /// @brief Return true if this cargo description can carry a given cargo
    virtual bool can_carry(const Cargo *p) const;
    /// @brief Get real amount of expenses per km.
    virtual Currency get_E(Distance D, Weight W) const;
    /// @brief Get real price.
    virtual Currency get_P(Distance D, Weight W) const;
};

#endif // CARGO_H_INCLUDED
