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

CargoAnimal::CargoAnimal(Weight weight, const std::string &description):Cargo(weight, description){}
std::istream& CargoAnimal::input(std::istream &is){
    return Cargo::input(is);
}
std::ostream& CargoAnimal::output(std::ostream &os) const{
    return Cargo::output(os);
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

CargoTransAnimal::CargoTransAnimal(Weight weight, const std::string &description, Currency expenses_per_km):
    CargoTrans(weight, description, expenses_per_km){}
std::istream& CargoTransAnimal::input(std::istream &is){
    return CargoTrans::input(is);
}
std::ostream& CargoTransAnimal::output(std::ostream &os) const{
    return CargoTrans::output(os);
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
