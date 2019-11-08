#include "truck.h"

#include "utils.h"

const std::string Truck::NumberPlate::REGEX_STR = "^[A-Z0-9 |.]{4,12}*$";
Truck::NumberPlate::NumberPlate():utils::string_regex(Truck::NumberPlate::REGEX_STR){}
Truck::NumberPlate::NumberPlate(const std::string &plate):NumberPlate(){
    *this = plate;
}
Truck::NumberPlate& Truck::NumberPlate::operator=(const std::string &s){
    string_regex::operator=(s);
    return *this;
}

Truck::Truck(const Truck &truck):
    number_plate_(truck.number_plate_), plate_register_date_(truck.plate_register_date_),
    fuel_        (truck.fuel_        ), max_reach_          (truck.max_reach_          ),
    category_    (truck.category_    ), cargo_              (truck.cargo_              ){}

Truck::Truck(const NumberPlate &number_plate, const Time     &plate_register_date,
             const Fuel        &fuel        , const Distance &max_reach          ,
             const Category    &category    , std::vector<CargoTrans*> cargo):
    number_plate_(number_plate), plate_register_date_(plate_register_date),
    fuel_        (fuel        ), max_reach_          (max_reach          ),
    category_    (category    ), cargo_              (cargo){}


std::istream& operator>>(std::istream &is,       Truck &t){
    std::string s;
    is >> s; t.number_plate_ = utils::urldecode(s);
    is >> t.plate_register_date_;
    is >> s; t.fuel_ = utils::urldecode(s);
    is >> t.max_reach_;
    is >> s; t.category_ = utils::urldecode(s);
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
       << utils::urlencode(t.fuel_               ) << "\n"
       <<                  t.max_reach_            << "\n"
       << utils::urlencode(t.category_           ) << "\n"
       <<                  t.cargo_.size()         << "\n";
    for(size_t i = 0; i < t.cargo_.size(); ++i){
        output_CargoTrans(os, t.cargo_[i]); if(i+1 != t.cargo_.size()) os << "\n";
    }
    return os;
}
