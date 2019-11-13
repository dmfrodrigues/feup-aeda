#include "cargo.h"

#include <cmath>
#include <algorithm>

#include "app.h"

const Currency    CargoTrans            ::P_B_(100.0);
const Currency    CargoTransAnimal      ::P_B_(150.0);
const Currency    CargoTransRefrigerated::P_B_(200.0);
const Temperature CargoTransRefrigerated::T0_(20.0);
const Currency    CargoTransDangerous   ::P_B_(300.0);

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

std::istream& input_Cargo     (std::istream &is,       Cargo      *&c){
    if(c != NULL) delete c;
    int t; is >> t;
    switch(t){
        case Cargo::Type::Normal      : c = new Cargo            (); break;
        case Cargo::Type::Animal      : c = new CargoAnimal      (); break;
        case Cargo::Type::Refrigerated: c = new CargoRefrigerated(); break;
        case Cargo::Type::Dangerous   : c = new CargoDangerous   (); break;
        default: is.setstate(std::ios::failbit); break;
    }
    return c->input(is);
}
std::istream& input_CargoTrans(std::istream &is,       CargoTrans *&c){
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

std::ostream& output_Cargo     (std::ostream &os, const Cargo      *c){
    if(c == NULL) throw std::invalid_argument("*c is a null pointer");
    os << (int)c->get_type() << "\n";
    return c->output(os);
}
std::ostream& output_CargoTrans(std::ostream &os, const CargoTrans *c){
    if(c == NULL) throw std::invalid_argument("*c is a null pointer");
    os << (int)c->get_type() << "\n";
    return c->output(os);
}

Cargo     ::Cargo     (): W_(0){}
Cargo     ::Cargo     (Weight W, const std::string &description):W_(W), description_(description){}
CargoTrans::CargoTrans(Weight W, const std::string &description, Currency E_D): Cargo(W, description), E_D_(E_D){}

std::istream& Cargo     ::input(std::istream &is){
    std::string s;
    is >> W_ >> s;
    try{
        description_ = utils::urldecode(s);
    }catch(...){
        is.setstate(std::ios::failbit);
    }
    return is;
}
std::istream& CargoTrans::input(std::istream &is){
    Cargo::input(is);
    is >> E_D_
       >> E_W_;
    return is;
}

std::ostream& Cargo     ::output(std::ostream &os) const{
    os << W_                        << "\n"
       << utils::urlencode(description_);
    return os;
}
std::ostream& CargoTrans::output(std::ostream &os) const{
    Cargo::output(os); os << "\n";
    os << E_D_ << "\n"
       << E_W_;
    return os;
}

bool Cargo     ::in(std::istream &is, std::ostream &os) {
    if (!utils::input("Weight: ", W_, is, os)||
        !utils::input("Description: ", description_, is, os)) return false;
    return true;
}
bool CargoTrans::in(std::istream &is, std::ostream &os) {
    if(!Cargo::in(is, os)) return false;
    if(!utils::input("Expenses per kilometer: ", E_D_, is, os)) return false;
    else                                                                    return true;
}

bool Cargo     ::edit(int property, std::istream &is, std::ostream &os) {
    switch(property) {
        case 0: return utils::input("Weight: "     , W_          , is, os);
        case 1: return utils::input("Description: ", description_, is, os);
        default: return false;
    }
}
bool CargoTrans::edit(int property, std::istream &is, std::ostream &os) {
    if (property < 2 && !Cargo::edit(property, is, os)) return false;
    switch (property) {
        case 2: std::cout << "Error: Base price can't be changed.\n"; return false;
        case 3: return utils::input("Expenses per kilometer: ", E_D_, is, os);
        default: return false;
    }
}

std::istream& CargoAnimal     ::input(std::istream &is){ return Cargo     ::input(is); }
std::istream& CargoTransAnimal::input(std::istream &is){ return CargoTrans::input(is); }

std::ostream& CargoAnimal     ::output(std::ostream &os) const{ return Cargo     ::output(os); }
std::ostream& CargoTransAnimal::output(std::ostream &os) const{ return CargoTrans::output(os); }

bool CargoAnimal     ::in(std::istream &is, std::ostream &os) { return Cargo     ::in(is, os); }
bool CargoTransAnimal::in(std::istream &is, std::ostream &os) { return CargoTrans::in(is, os); }

bool CargoAnimal     ::edit(int property, std::istream &is, std::ostream &os) { return Cargo     ::edit(property, is, os); }
bool CargoTransAnimal::edit(int property, std::istream &is, std::ostream &os) { return CargoTrans::edit(property, is, os); }

std::istream& CargoRefrigerated     ::input(std::istream &is){ Cargo::input(is); is >> Tr_; return is; }
std::istream& CargoTransRefrigerated::input(std::istream &is){ CargoTrans::input(is); return is >> E_T_ >> Tr_; }

std::ostream& CargoRefrigerated     ::output(std::ostream &os) const{
    Cargo::output(os); os << "\n";
    os << Tr_;
    return os;
}
std::ostream& CargoTransRefrigerated::output(std::ostream &os) const{ CargoTrans::output(os); return os << "\n" << E_T_ << "\n" << Tr_; }

bool CargoRefrigerated     ::in(std::istream &is, std::ostream &os) {
    if(!Cargo::in(is, os)) return false;

    while (true) {
        try {
            float tmin, tmax;
            if (!utils::input("Minimum temperature: ", tmin, is, os)||
                !utils::input("Maximum temperature: ", tmax, is, os)) return false;

            TemperatureRange temp_range = TemperatureRange(Temperature(tmin), Temperature(tmax));

            Tr_ = temp_range;
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
bool CargoTransRefrigerated::in(std::istream &is, std::ostream &os) {
    if(!CargoTrans::in(is, os)) return false;

    while (true) {
        try {
            float tmin, tmax;
            if (!utils::input("Minimum temperature: ", tmin, is, os)||
                !utils::input("Maximum temperature: ", tmax, is, os)) return false;

            TemperatureRange temp_range = TemperatureRange(Temperature(tmin), Temperature(tmax));

            Tr_ = temp_range;
            break;
        } catch (TemperatureRange::InvalidTemperatureRange &itr) {
            std::cout << "Error: " << itr.what() << "\n";
        } catch (Temperature::InvalidTemperature &it) {
            std::cout << it.what() << "\n";
        } catch (...) {
            std::cout << "Error: Invalid input\n";
        }
    }

    if (!utils::input("Temperature factor: ", E_T_, is, os)) return false;
    else                                                                    return true;
}

bool CargoRefrigerated     ::edit(int property, std::istream &is, std::ostream &os) {
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

                Tr_ = temp_range;
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

                Tr_ = temp_range;
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
        if (!utils::input("Temperature factor: ", E_T_, is, os)) return false;
        else                                                                    return true;
        break;
    default:
        return false;
        break;
    }
}

std::istream& CargoDangerous     ::input(std::istream &is){
    Cargo::input(is);
    unsigned i; is >> i; danger_level_ = static_cast<Cargo::DangerLevel>(i);
    return is;
}
std::istream& CargoTransDangerous::input(std::istream &is){
    CargoTrans::input(is);
    unsigned i; is >> i; danger_level_ = static_cast<Cargo::DangerLevel>(i);
    return is;
}

std::ostream& CargoDangerous     ::output(std::ostream &os) const{
    Cargo::output(os); os << "\n";
    os << (int)danger_level_;
    return os;
}
std::ostream& CargoTransDangerous::output(std::ostream &os) const{
    CargoTrans::output(os); os << "\n";
    os << (int)danger_level_;
    return os;
}

bool CargoDangerous     ::in(std::istream &is, std::ostream &os) {
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

bool CargoDangerous     ::edit(int property, std::istream &is, std::ostream &os) {
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

bool CargoTrans            ::can_carry(const Cargo *p) const{ return (get_type() == p->get_type()); }
bool CargoTransAnimal      ::can_carry(const Cargo *p) const{ return (get_type() == p->get_type()); }
bool CargoTransRefrigerated::can_carry(const Cargo *p) const{
    if(get_type() == p->get_type()){
        const CargoRefrigerated *q = dynamic_cast<const CargoRefrigerated*>(p);
        return (utils::feq(double(get_Tr().max), double(q->get_Tr().min), 0.01) ||
                std::max(get_Tr().min, q->get_Tr().min) <
                std::min(get_Tr().max, q->get_Tr().max));
    }else return false;
}
bool CargoTransDangerous   ::can_carry(const Cargo *p) const{
    if(get_type() == p->get_type()){
        const CargoDangerous *q = dynamic_cast<const CargoDangerous*>(p);
        return (get_dangerlevel() == q->get_dangerlevel());
    }else return false;
}

Currency CargoTrans            ::get_E(Distance D, Weight W) const{ return Currency(double(D)*(get_E_D()+double(W)*get_E_W())); }
Currency CargoTransAnimal      ::get_E(Distance D, Weight W) const{ return Currency(double(D)*(get_E_D()+double(W)*get_E_W())); }
Currency CargoTransRefrigerated::get_E(Distance D, Weight W, TemperatureRange Tr) const{
    double DT = std::fabs(std::min(Tr_.max, Tr.max)-get_T0());
    return Currency(double(D)*(get_E_D()+double(W)*get_E_W())*(DT*get_E_T()));
}
Currency CargoTransDangerous   ::get_E(Distance D, Weight W) const{ return Currency(double(D)*(get_E_D()+double(W)*get_E_W()));}

Currency CargoTrans            ::get_P(Distance D, Weight W) const{ return Currency(double(get_E(D,W))*(1.0L+App::rate))+get_P_B(); }
Currency CargoTransAnimal      ::get_P(Distance D, Weight W) const{ return Currency(double(get_E(D,W))*(1.0L+App::rate))+get_P_B(); }
Currency CargoTransRefrigerated::get_P(Distance D, Weight W, TemperatureRange Tr) const{ return Currency(double(get_E(D,W,Tr))*(1.0L+App::rate))+get_P_B(); }
Currency CargoTransDangerous   ::get_P(Distance D, Weight W) const{ return Currency(double(get_E(D,W))*(1.0L+App::rate))+get_P_B(); }


/*
double CargoTransRefrigerated::get_expenses(Distance D, Weight W) const{
    const CargoRefrigerated *q = dynamic_cast<const CargoRefrigerated*>(p);
    double dT = std::fabs(double(std::min(q->get_Tr().max, get_Tr().max)-T0_));
    return get_expensesperkm()*(1.0L+E_T_*dT);
}
*/
