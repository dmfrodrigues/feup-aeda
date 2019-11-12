#include "cargo.h"

#include <cmath>
#include <algorithm>
#include "utils.h"

const Currency    CargoTrans            ::price_base_(100.0);
const Currency    CargoTransAnimal      ::price_base_(150.0);
const Currency    CargoTransRefrigerated::price_base_(200.0);
const Temperature CargoTransRefrigerated::reference_temperature_(20.0);
const Currency    CargoTransDangerous   ::price_base_(300.0);

std::istream& input_Cargo(std::istream &is,       Cargo *&c){
    if(c != NULL) delete c;
    unsigned t; is >> t;
    switch(t){
        case Cargo::Type::Normal      : c = new Cargo            (); break;
        case Cargo::Type::Animal      : c = new CargoAnimal      (); break;
        case Cargo::Type::Refrigerated: c = new CargoRefrigerated(); break;
        case Cargo::Type::Dangerous   : c = new CargoDangerous   (); break;
        default: is.setstate(std::ios::failbit);
    }
    return c->input(is);
}

std::ostream& output_Cargo(std::ostream &os, const Cargo *c){
    if(c == NULL) throw std::invalid_argument("*c is a null pointer");
    os << (int)c->get_type() << "\n";
    return c->output(os);
}

std::string Cargo::type_string(const Type &t){
    switch(t){
        case Cargo::Type::Normal      : return "Normal"      ;
        case Cargo::Type::Animal      : return "Animal"      ;
        case Cargo::Type::Refrigerated: return "Refrigerated";
        case Cargo::Type::Dangerous   : return "Dangerous"   ;
        default: throw std::invalid_argument("invalid Cargo::Type");
    }
}

std::string Cargo::dangerlevel_string(const DangerLevel &d){
    switch(d){
        case Cargo::DangerLevel::None            : return "None"            ;
        case Cargo::DangerLevel::Miscellaneous   : return "Miscellaneous"   ;
        case Cargo::DangerLevel::Gases           : return "Gases"           ;
        case Cargo::DangerLevel::Flammable_Liq   : return "Flammable_Liq"   ;
        case Cargo::DangerLevel::Flammable_Sol   : return "Flammable_Sol"   ;
        case Cargo::DangerLevel::Oxydizing_Agents: return "Oxydizing_Agents";
        case Cargo::DangerLevel::Explosives      : return "Explosives"      ;
        case Cargo::DangerLevel::Corrosive       : return "Corrosive"       ;
        case Cargo::DangerLevel::Toxic           : return "Toxic"           ;
        case Cargo::DangerLevel::Radioactive     : return "Radioactive"     ;
        default: throw std::invalid_argument("invalid Cargo::DangerLevel");
    }
}

Cargo::Cargo(): weight_(0){}
Cargo::Cargo(Weight weight, const std::string &description):weight_(weight), description_(description){}
std::istream& Cargo::input(std::istream &is){
    try{
        std::string s;
        is >> weight_;
        is >> s; description_ = utils::urldecode(s);
    }catch(...){
        is.setstate(std::ios::failbit);
    }
    return is;
}
std::ostream& Cargo::output(std::ostream &os) const{
    os << weight_                        << "\n"
       << utils::urlencode(description_);
    return os;
}

bool Cargo::in(std::istream &is, std::ostream &os) {
    if (!utils::input("Weight: ", weight_, is, os)||
        !utils::input("Description: ", description_, is, os)) return false;
    return true;
}

bool Cargo::edit(int property, std::istream &is, std::ostream &os) {
    switch(property) {
    case 0:
        if (!utils::input("Weight: ", weight_, is, os))             return false;
        else                                                        return true;
        break;
    case 1:
        if (!utils::input("Description: ", description_, is, os))   return false;
        else                                                        return true;
        break;
    default:
        return false;
        break;
    }
}

CargoAnimal::CargoAnimal(Weight weight, const std::string &description):Cargo(weight, description){}
std::istream& CargoAnimal::input(std::istream &is){
    return Cargo::input(is);
}
std::ostream& CargoAnimal::output(std::ostream &os) const{
    return Cargo::output(os);
}

bool CargoAnimal::in(std::istream &is, std::ostream &os) {
    return Cargo::in(is, os);
}

bool CargoAnimal::edit(int property, std::istream &is, std::ostream &os) {
    return Cargo::edit(property, is, os);
}

CargoRefrigerated::CargoRefrigerated(Weight weight, const std::string &description, TemperatureRange temperature_range):
    Cargo(weight, description), temperature_range_(temperature_range){}
std::istream& CargoRefrigerated::input(std::istream &is){
    Cargo::input(is);
    is >> temperature_range_;
    return is;
}
std::ostream& CargoRefrigerated::output(std::ostream &os) const{
    Cargo::output(os); os << "\n";
    os << temperature_range_;
    return os;
}

bool CargoRefrigerated::in(std::istream &is, std::ostream &os) {
    if(!Cargo::in(is, os)) return false;

    while (true) {
        try {
            float tmin, tmax;
            if (!utils::input("Minimum temperature: ", tmin, is, os)||
                !utils::input("Maximum temperature: ", tmax, is, os)) return false;

            TemperatureRange temp_range = TemperatureRange(Temperature(tmin), Temperature(tmax));

            temperature_range_ = temp_range;
            return true;
        } catch (TemperatureRange::InvalidTemperatureRange &itr) {
            std::cout << "Error: " << itr.what() << "\n";
        } catch (Temperature::InvalidTemperature &it) {
            std::cout << it.what() << "\n";
        } catch (...) {
            std::cout << "Error: Invalid input\n";
        }
    }
}

bool CargoRefrigerated::edit(int property, std::istream &is, std::ostream &os) {
    if (property < 2)
        if (!Cargo::edit(property, is, os)) return false;

    switch (property) {
    case 2:
        while (true) {
            try {
                float tmin, tmax;
                if (!utils::input("Minimum temperature: ", tmin, is, os)||
                    !utils::input("Maximum temperature: ", tmax, is, os)) return false;

                TemperatureRange temp_range = TemperatureRange(Temperature(tmin), Temperature(tmax));

                temperature_range_ = temp_range;
                return true;
            } catch (TemperatureRange::InvalidTemperatureRange &itr) {
                std::cout << "Error: " << itr.what() << "\n";
            } catch (Temperature::InvalidTemperature &it) {
                std::cout << it.what() << "\n";
            } catch (...) {
                std::cout << "Error: Invalid input\n";
            }
        }
        break;
    default:
        return false;
        break;
    }
}

CargoDangerous::CargoDangerous(Weight weight, const std::string &description, DangerLevel danger_level):
    Cargo(weight, description), danger_level_(danger_level){}
std::istream& CargoDangerous::input(std::istream &is){
    Cargo::input(is);
    unsigned i; is >> i; danger_level_ = static_cast<Cargo::DangerLevel>(i);
    return is;
}
std::ostream& CargoDangerous::output(std::ostream &os) const{
    Cargo::output(os); os << "\n";
    os << (int)danger_level_;
    return os;
}

bool CargoDangerous::in(std::istream &is, std::ostream &os) {
    if(!Cargo::in(is, os)) return false;
    std::string input;
    std::string msg = "Danger Levels -> None(0) | Miscellaneous(1) | Gases(2)\n"
                      "                 Flammable Liquids(3) | Flammable Solids(4) | Oxydizing Agents(5)\n"
                      "                 Explosives(6) | Corrosive(7) | Toxic (8) | Radioactive(9)\nDanger Level: ";
    while (true) {
        if (!utils::input(msg, input, is, os)) return false;
        utils::to_lower(input);
        if (input == "none"                 ||  input == "0")   { danger_level_ = Cargo::DangerLevel::None;             break; }
        if (input == "miscellaneous"        ||  input == "1")   { danger_level_ = Cargo::DangerLevel::Miscellaneous;    break; }
        if (input == "gases"                ||  input == "2")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
        if (input == "flammable liquids"    ||  input == "3")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
        if (input == "flammable solids"     ||  input == "4")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
        if (input == "oxydizing agents"     ||  input == "5")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
        if (input == "explosives"           ||  input == "6")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
        if (input == "corrosive"            ||  input == "7")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
        if (input == "toxic"                ||  input == "8")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
        if (input == "radioactive"          ||  input == "9")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
        else { std::cout << "Error: Invalid danger level.\n"; }
    }
    return true;
}

bool CargoDangerous::edit(int property, std::istream &is, std::ostream &os) {
    if (property < 2)
        if (!Cargo::edit(property, is, os)) return false;

    switch (property) {
    case 2:
        {
            std::string input;
            std::string msg = "Danger Levels -> None(0) | Miscellaneous(1) | Gases(2)\n"
                              "                 Flammable Liquids(3) | Flammable Solids(4) | Oxydizing Agents(5)\n"
                              "                 Explosives(6) | Corrosive(7) | Toxic (8) | Radioactive(9)\nDanger Level: ";
            while (true) {
                if (!utils::input(msg, input, is, os)) return false;
                utils::to_lower(input);
                if (input == "none"                 ||  input == "0")   { danger_level_ = Cargo::DangerLevel::None;             break; }
                if (input == "miscellaneous"        ||  input == "1")   { danger_level_ = Cargo::DangerLevel::Miscellaneous;    break; }
                if (input == "gases"                ||  input == "2")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
                if (input == "flammable liquids"    ||  input == "3")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
                if (input == "flammable solids"     ||  input == "4")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
                if (input == "oxydizing agents"     ||  input == "5")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
                if (input == "explosives"           ||  input == "6")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
                if (input == "corrosive"            ||  input == "7")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
                if (input == "toxic"                ||  input == "8")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
                if (input == "radioactive"          ||  input == "9")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
                else { std::cout << "Error: Invalid danger level.\n"; }
            }
            return true;
        }
        break;
    default:
        return false;
        break;
    }
}

std::istream& input_CargoTrans(std::istream &is,       CargoTrans* &c){
    if(c != NULL) delete c;
    int t; is >> t;
    switch(t){
        case Cargo::Type::Normal      : c = new CargoTrans            (); break;
        case Cargo::Type::Animal      : c = new CargoTransAnimal      (); break;
        case Cargo::Type::Refrigerated: c = new CargoTransRefrigerated(); break;
        case Cargo::Type::Dangerous   : c = new CargoTransDangerous   (); break;
        default: is.setstate(std::ios::failbit); break;
    }
    return c->input(is);
}

std::ostream& output_CargoTrans(std::ostream &os, const CargoTrans *c){
    if(c == NULL) throw std::invalid_argument("*c is a null pointer");
    os << (int)c->get_type() << "\n";
    return c->output(os);
}

CargoTrans::CargoTrans(Weight weight, const std::string &description, Currency expenses_per_km):
    Cargo(weight, description), expenses_per_km_(expenses_per_km){}
std::istream& CargoTrans::input(std::istream &is){
    Cargo::input(is);
    is >> expenses_per_km_;
    return is;
}
std::ostream& CargoTrans::output(std::ostream &os) const{
    Cargo::output(os); os << "\n";
    os << expenses_per_km_;
    return os;
}

bool CargoTrans::in(std::istream &is, std::ostream &os) {
    if(!Cargo::in(is, os)) return false;
    if(!utils::input("Expenses per kilometer: ", expenses_per_km_, is, os)) return false;
    else                                                                    return true;
}

bool CargoTrans::edit(int property, std::istream &is, std::ostream &os) {
    if (property < 2)
        if (!Cargo::edit(property, is, os)) return false;

    switch (property) {
    case 2:
        std::cout << "Error: Base price can't be changed.\n";
        return false;
        break;
    case 3:
        if(!utils::input("Expenses per kilometer: ", expenses_per_km_, is, os)) return false;
        else                                                                    return true;
        break;
    default:
        return false;
        break;
    }
}

CargoTransAnimal::CargoTransAnimal(Weight weight, const std::string &description, Currency expenses_per_km):
    CargoTrans(weight, description, expenses_per_km){}
std::istream& CargoTransAnimal::input(std::istream &is){
    return CargoTrans::input(is);
}
std::ostream& CargoTransAnimal::output(std::ostream &os) const{
    return CargoTrans::output(os);
}

bool CargoTransAnimal::in(std::istream &is, std::ostream &os) {
    return CargoTrans::in(is, os);
}

bool CargoTransAnimal::edit(int property, std::istream &is, std::ostream &os) {
    return CargoTrans::edit(property, is, os);
}

CargoTransRefrigerated::CargoTransRefrigerated(Weight weight, const std::string &description, Currency expenses_per_km, float temperature_factor):
    CargoTrans(weight, description, expenses_per_km), temperature_factor_(temperature_factor){}
std::istream& CargoTransRefrigerated::input(std::istream &is){
    CargoTrans::input(is);
    is >> temperature_factor_;
    return is;
}
std::ostream& CargoTransRefrigerated::output(std::ostream &os) const{
    CargoTrans::output(os); os << "\n";
    os << temperature_factor_;
    return os;
}

bool CargoTransRefrigerated::in(std::istream &is, std::ostream &os) {
    if(!CargoTrans::in(is, os)) return false;

    while (true) {
        try {
            float tmin, tmax;
            if (!utils::input("Minimum temperature: ", tmin, is, os)||
                !utils::input("Maximum temperature: ", tmax, is, os)) return false;

            TemperatureRange temp_range = TemperatureRange(Temperature(tmin), Temperature(tmax));

            temperature_range_ = temp_range;
            break;
        } catch (TemperatureRange::InvalidTemperatureRange &itr) {
            std::cout << "Error: " << itr.what() << "\n";
        } catch (Temperature::InvalidTemperature &it) {
            std::cout << it.what() << "\n";
        } catch (...) {
            std::cout << "Error: Invalid input\n";
        }
    }

    if (!utils::input("Temperature factor: ", temperature_factor_, is, os)) return false;
    else                                                                    return true;
}

bool CargoTransRefrigerated::edit(int property, std::istream &is, std::ostream &os) {
    if (property < 3)
        if (!CargoTrans::edit(property, is, os)) return false;

    switch (property) {
    case 4:
        while (true) {
            try {
                float tmin, tmax;
                if (!utils::input("Minimum temperature: ", tmin, is, os)||
                    !utils::input("Maximum temperature: ", tmax, is, os)) return false;

                TemperatureRange temp_range = TemperatureRange(Temperature(tmin), Temperature(tmax));

                temperature_range_ = temp_range;
                return true;
                break;
            } catch (TemperatureRange::InvalidTemperatureRange &itr) {
                std::cout << "Error: " << itr.what() << "\n";
            } catch (Temperature::InvalidTemperature &it) {
                std::cout << it.what() << "\n";
            } catch (...) {
                std::cout << "Error: Invalid input\n";
            }
        }
        break;
    case 5:
        std::cout << "Error: Base price can't be changed.\n";
        return false;
        break;
    case 6:
        if (!utils::input("Temperature factor: ", temperature_factor_, is, os)) return false;
        else                                                                    return true;
        break;
    default:
        return false;
        break;
    }
}

CargoTransDangerous::CargoTransDangerous(Weight weight, const std::string &description, Currency expenses_per_km, DangerLevel danger_level):
    CargoTrans(weight, description, expenses_per_km), danger_level_(danger_level){}
std::istream& CargoTransDangerous::input(std::istream &is){
    CargoTrans::input(is);
    unsigned i; is >> i; danger_level_ = static_cast<Cargo::DangerLevel>(i);
    return is;
}
std::ostream& CargoTransDangerous::output(std::ostream &os) const{
    CargoTrans::output(os); os << "\n";
    os << (int)danger_level_;
    return os;
}

bool CargoTransDangerous::in(std::istream &is, std::ostream &os) {
    if(!CargoTrans::in(is, os)) return false;
    std::string input;
    std::string msg = "Danger Levels -> None(0) | Miscellaneous(1) | Gases(2)\n"
                      "                 Flammable Liquids(3) | Flammable Solids(4) | Oxydizing Agents(5)\n"
                      "                 Explosives(6) | Corrosive(7) | Toxic (8) | Radioactive(9)\nDanger Level: ";
    while (true) {
        if (!utils::input(msg, input, is, os)) return false;
        utils::to_lower(input);
        if (input == "none"                 ||  input == "0")   { danger_level_ = Cargo::DangerLevel::None;             break; }
        if (input == "miscellaneous"        ||  input == "1")   { danger_level_ = Cargo::DangerLevel::Miscellaneous;    break; }
        if (input == "gases"                ||  input == "2")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
        if (input == "flammable liquids"    ||  input == "3")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
        if (input == "flammable solids"     ||  input == "4")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
        if (input == "oxydizing agents"     ||  input == "5")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
        if (input == "explosives"           ||  input == "6")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
        if (input == "corrosive"            ||  input == "7")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
        if (input == "toxic"                ||  input == "8")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
        if (input == "radioactive"          ||  input == "9")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
        else { std::cout << "Error: Invalid danger level.\n"; }
    }
    return true;
}

bool CargoTransDangerous::edit(int property, std::istream &is, std::ostream &os) {
    if (property < 3)
        if (!CargoTrans::edit(property, is, os)) return false;

    switch (property) {
    case 4:
        {
            std::string input;
            std::string msg = "Danger Levels -> None(0) | Miscellaneous(1) | Gases(2)\n"
                              "                 Flammable Liquids(3) | Flammable Solids(4) | Oxydizing Agents(5)\n"
                              "                 Explosives(6) | Corrosive(7) | Toxic (8) | Radioactive(9)\nDanger Level: ";
            while (true) {
                if (!utils::input(msg, input, is, os)) return false;
                utils::to_lower(input);
                if (input == "none"                 ||  input == "0")   { danger_level_ = Cargo::DangerLevel::None;             break; }
                if (input == "miscellaneous"        ||  input == "1")   { danger_level_ = Cargo::DangerLevel::Miscellaneous;    break; }
                if (input == "gases"                ||  input == "2")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
                if (input == "flammable liquids"    ||  input == "3")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
                if (input == "flammable solids"     ||  input == "4")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
                if (input == "oxydizing agents"     ||  input == "5")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
                if (input == "explosives"           ||  input == "6")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
                if (input == "corrosive"            ||  input == "7")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
                if (input == "toxic"                ||  input == "8")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
                if (input == "radioactive"          ||  input == "9")   { danger_level_ = Cargo::DangerLevel::Gases;            break; }
                else { std::cout << "Error: Invalid danger level.\n"; }
            }
            return true;
        }
        break;
    default:
        return false;
        break;
    }
}
