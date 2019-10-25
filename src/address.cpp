#include "address.h"

#include "utils.h"

const std::string Address::DEFAULT_FORMAT = "%street\n%postal %city\n%district, %country";

Address::Address(std::string street, std::string postal_code, std::string city, std::string district, std::string country):
                 street_(street), postal_code_(postal_code), city_(city), district_(district), country_(country){}

std::string Address::format(const std::string &s) const{
    std::string ret = s;
    strrep(ret, "%street", street_);
    strrep(ret, "%postal", postal_code_);
    strrep(ret, "%city", city_);
    strrep(ret, "%district", district_);
    strrep(ret, "%country", country_);
    return ret;
}

std::ostream& operator<<(std::ostream &os, const Address &a){
    return os << a.format();
}
