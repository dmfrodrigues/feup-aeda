#include "address.h"

const std::string Address::DEFAULT_FORMAT = "%strt\n%pst %cty\n%district, %ctry";

Address::Address(std::string street, std::string postal_code, std::string city, std::string district, std::string country):
                 street_(street), postal_code_(postal_code), city_(city), district_(district), country_(country){}

std::string Address::format(const std::string &s) const{
    std::stringstream ss;
    ss << street_ << "\n"
       << postal_code_ << " " << city_ << "\n"
       << district_ << ", " << country_;
    return ss.str();
}

std::ostream& operator<<(std::ostream &os, const Address &a){
    return os << a.format();
}
