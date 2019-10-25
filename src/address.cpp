#include "address.h"

#include "utils.h"

const std::string Address::DEFAULT_FORMAT = "%street\n%postal %city\n%district, %country";

Address::Address(){}
Address::Address(std::string street, std::string postal_code, std::string city, std::string district, std::string country):
                 street_(street), postal_code_(postal_code), city_(city), district_(district), country_(country){}

std::string Address::format(const std::string &s) const{
    std::string ret = s;
    ret = strrep(ret, "%street", street_);
    ret = strrep(ret, "%postal", postal_code_);
    ret = strrep(ret, "%city", city_);
    ret = strrep(ret, "%district", district_);
    ret = strrep(ret, "%country", country_);
    return ret;
}

std::ostream& operator<<(std::ostream &os, const Address &a){
    return os << a.format("%street\n%postal\n%city\n%district\n%country");
}

std::istream& operator>>(std::istream &is, Address &a){
    std::getline(is, a.street_);
    std::getline(is, a.postal_code_);
    std::getline(is, a.city_);
    std::getline(is, a.district_);
    std::getline(is, a.country_);
    return is;
}
