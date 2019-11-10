#include "truck.h"

#include "utils.h"

//Fuel processing
Truck::Fuel Truck::processFuel(const std::string &s) {
    if (s == "gasoline") return Truck::Fuel::Gasoline;
    if (s == "diesel") return Truck::Fuel::Diesel;
    if (s == "biodiesel") return Truck::Fuel::Diesel;
    if (s == "gas") return Truck::Fuel::Diesel;
    if (s == "hydrogen") return Truck::Fuel::Diesel;
    if (s == "electric") return Truck::Fuel::Diesel;
    if (s == "hybrid") return Truck::Fuel::Diesel;
    throw std::invalid_argument("Invalid fuel type.");
}

///NUMBERPLATE NUMBER
const std::string Truck::NumberPlate::Number::REGEX_STR = "^[A-Z0-9 |.]{4,12}*$";
Truck::NumberPlate::Number::Number():utils::string_regex(Truck::NumberPlate::Number::REGEX_STR){}
Truck::NumberPlate::Number::Number(const std::string &plate):Number(){
    *this = plate;
}
Truck::NumberPlate::Number& Truck::NumberPlate::Number::operator=(const std::string &s){
    string_regex::operator=(s);
    return *this;
}
///NUMBERPLATE
Truck::NumberPlate::NumberPlate(){}
Truck::NumberPlate::NumberPlate(const Number &number):number_(number){}
Truck::NumberPlate::operator std::string() const{ return (std::string)number_; }
bool Truck::NumberPlate::operator< (const NumberPlate &n) const{ return ((std::string)*this <  (std::string)n); }
bool Truck::NumberPlate::operator==(const NumberPlate &n) const{ return ((std::string)*this == (std::string)n); }
std::istream& operator>>(std::istream &is,       Truck::NumberPlate &n){
    is >> n.number_;
    return is;
}
std::ostream& operator<<(std::ostream &os, const Truck::NumberPlate &n){
    os << n.number_;
    return os;
}
///CATEGORY
const std::string Truck::Category::REGEX_STR = "^[+-A-Z]{1,4}$";
Truck::Category::Category():utils::string_regex(Truck::Category::REGEX_STR){}
Truck::Category::Category(const std::string &category):Category(){
    *this = category;
}
Truck::Category& Truck::Category::operator=(const std::string &category){
    string_regex::operator=(category);
    return *this;
}
///TRUCK
Truck::Truck(const Truck &t):
    number_plate_(t.number_plate_), plate_register_date_(t.plate_register_date_),
    fuel_        (t.fuel_        ), max_reach_          (t.max_reach_          ),
    category_    (t.category_    ), cargo_              (t.cargo_              ){}

Truck::Truck(const NumberPlate &number_plate, const Time     &plate_register_date,
             const Fuel        &fuel        , const Distance &max_reach          ,
             const Category    &category    , std::vector<CargoTrans*> cargo):
    number_plate_(number_plate), plate_register_date_(plate_register_date),
    fuel_        (fuel        ), max_reach_          (max_reach          ),
    category_    (category    ), cargo_              (cargo){}

Truck::Type Truck::get_type(void) const{ return Truck::Type::truck; }

std::istream& operator>>(std::istream &is,       Truck &t){
    std::string s;
    is >> t.number_plate_;
    is >> t.plate_register_date_;
    int i; is >> i; t.fuel_ = static_cast<Truck::Fuel>(i);
    is >> t.max_reach_;
    is >> t.category_;
    size_t N; is >> N;
    t.cargo_ = std::vector<CargoTrans*>(N, NULL);
    for(CargoTrans* &p:t.cargo_){
        input_CargoTrans(is, p);
    }
    return is;
}

std::ostream& operator<<(std::ostream &os, const Truck &t){
    os << t.number_plate_         << "\n"
       << t.plate_register_date_  << "\n"
       << (int)t.fuel_            << "\n"
       << t.max_reach_            << "\n"
       << t.category_             << "\n"
       << t.cargo_.size()         << "\n";
    for(size_t i = 0; i < t.cargo_.size(); ++i){
        output_CargoTrans(os, t.cargo_[i]); if(i+1 != t.cargo_.size()) os << "\n";
    }
    return os;
}

bool Truck::in(std::istream &is, std::ostream &os) {
    if (!utils::input("Number Plate: ", [](Truck::NumberPlate &np, const std::string &s) { np = Truck::NumberPlate(Truck::NumberPlate::Number(s)); }, number_plate_, is, os)|
        !utils::input("Plate Register Date: ", [](Time &tm, const std::string &s) { tm = Time(s); },  plate_register_date_, is, os)|
        !utils::input("Fuel: ", [](Truck::Fuel &fuel, const std::string &s) { fuel = Truck::processFuel(s); }, fuel_, is, os)|
        !utils::input("Maximum reach: ", max_reach_, is, os)|
        !utils::input("Category: ",[](Truck::Category &cat, const std::string &s) { cat = Truck::Category(s); }, category_, is, os)) return false;

    return true;
}
