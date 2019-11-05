#include "address.h"

#include "utils.h"

const std::string Address::DEFAULT_FORMAT = "%street\n%postal\n%city\n%district\n%country";

Address::Address(){}
Address::Address(const std::string &street, const std::string &postal_code, const std::string &city, const std::string &district, const std::string &country):
                 street_(street), postal_code_(postal_code), city_(city), district_(district), country_(country){}

std::string Address::format(const std::string &s) const{
    std::string ret = s;
    ret = utils::strrep(ret, "%street", street_);
    ret = utils::strrep(ret, "%postal", postal_code_);
    ret = utils::strrep(ret, "%city", city_);
    ret = utils::strrep(ret, "%district", district_);
    ret = utils::strrep(ret, "%country", country_);
    return ret;
}

std::ostream& operator<<(std::ostream &os, const Address &a){
    return os << utils::urlencode(a.street_     ) << "\n"
              << utils::urlencode(a.postal_code_) << "\n"
              << utils::urlencode(a.city_       ) << "\n"
              << utils::urlencode(a.district_   ) << "\n"
              << utils::urlencode(a.country_    );
}

std::istream& operator>>(std::istream &is, Address &a){
    std::string s;
    is >> s; a.street_      = utils::urldecode(s);
    is >> s; a.postal_code_ = utils::urldecode(s);
    is >> s; a.city_        = utils::urldecode(s);
    is >> s; a.district_    = utils::urldecode(s);
    is >> s; a.country_     = utils::urldecode(s);
    return is;
}
