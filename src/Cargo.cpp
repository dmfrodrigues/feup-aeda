#include "Cargo.h"

#include <cmath>
#include <algorithm>


Cargo::Cargo(): weight_(0){}
Cargo::Cargo(Weight weight, const std::string &description):weight_(weight), description_(description){}

CargoAnimal::CargoAnimal(Weight weight, const std::string &description):Cargo(weight, description){}

CargoRefrigerated::CargoRefrigerated(Weight weight, const std::string &description, TemperatureRange temperature_range):
    Cargo(weight, description), temperature_range_(temperature_range){}

CargoDangerous::CargoDangerous(Weight weight, const std::string &description, DangerLevel danger_level):
    Cargo(weight, description), danger_level_(danger_level){}

CargoTrans::CargoTrans(Weight weight, const std::string &description, Currency expenses_per_km):
    Cargo(weight, description), expenses_per_km_(expenses_per_km_){}

CargoTransAnimal::CargoTransAnimal(Weight weight, const std::string &description, Currency expenses_per_km):
    CargoTrans(weight, description, expenses_per_km){}

CargoTransRefrigerated::CargoTransRefrigerated(Weight weight, const std::string &description, Currency expenses_per_km, Currency expenses_per_deg):
    CargoTrans(weight, description, expenses_per_km), expenses_per_deg_(expenses_per_deg){}

CargoTransDangerous::CargoTransDangerous(float weight, const std::string &description, Currency expenses_per_km, DangerLevel danger_level):
    CargoTrans(weight, description, expenses_per_km), danger_level_(danger_level){}
