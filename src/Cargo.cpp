#include "Cargo.h"

#include <cmath>
#include <algorithm>
#include "utils.h"

void input_Cargo(std::istream &is,       Cargo *c){
    if(c != NULL) delete c;
    int t; is >> t;
    switch(t){
        case Cargo::Type::Normal      : c = new Cargo            (); break;
        case Cargo::Type::Animal      : c = new CargoAnimal      (); break;
        case Cargo::Type::Refrigerated: c = new CargoRefrigerated(); break;
        case Cargo::Type::Dangerous   : c = new CargoDangerous   (); break;
        default: throw 1;
    }
    c->input(is);
}

void output_Cargo(std::ostream &os, const Cargo *c){
    if(c == NULL) throw 1;
    os << c->get_type() << "\n";
    c->output(os);
}

Cargo::Cargo(): weight_(0){}
Cargo::Cargo(Weight weight, const std::string &description):weight_(weight), description_(description){}
void Cargo::input(std::istream &is){
    std::string s;
    is >> weight_;
    is >> s; description_ = utils::urldecode(s);
}
void Cargo::output(std::ostream &os) const{
    os << weight_                        << "\n"
       << utils::urlencode(description_);
}

CargoAnimal::CargoAnimal(Weight weight, const std::string &description):Cargo(weight, description){}



CargoRefrigerated::CargoRefrigerated(Weight weight, const std::string &description, TemperatureRange temperature_range):
    Cargo(weight, description), temperature_range_(temperature_range){}

CargoDangerous::CargoDangerous(Weight weight, const std::string &description, DangerLevel danger_level):
    Cargo(weight, description), danger_level_(danger_level){}

void input_CargoTrans(std::istream &is,       CargoTrans *c){
    if(c != NULL) delete c;
    int t; is >> t;
    switch(t){
        case Cargo::Type::Normal      : c = new CargoTrans            (); break;
        case Cargo::Type::Animal      : c = new CargoTransAnimal      (); break;
        case Cargo::Type::Refrigerated: c = new CargoTransRefrigerated(); break;
        case Cargo::Type::Dangerous   : c = new CargoTransDangerous   (); break;
        default: throw 1;
    }
    c->input(is);
}

void output_CargoTrans(std::ostream &os, const CargoTrans *c){
    if(c == NULL) throw 1;
    os << c->get_type() << "\n";
    c->output(os);
}

CargoTrans::CargoTrans(Weight weight, const std::string &description, Currency expenses_per_km):
    Cargo(weight, description), expenses_per_km_(expenses_per_km_){}

CargoTransAnimal::CargoTransAnimal(Weight weight, const std::string &description, Currency expenses_per_km):
    CargoTrans(weight, description, expenses_per_km){}

CargoTransRefrigerated::CargoTransRefrigerated(Weight weight, const std::string &description, Currency expenses_per_km, Currency expenses_per_deg):
    CargoTrans(weight, description, expenses_per_km), expenses_per_deg_(expenses_per_deg){}

CargoTransDangerous::CargoTransDangerous(float weight, const std::string &description, Currency expenses_per_km, DangerLevel danger_level):
    CargoTrans(weight, description, expenses_per_km), danger_level_(danger_level){}
