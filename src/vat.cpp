#include "../include/vat.h"

#include "../include/utils.h"

const std::string VAT::REGEX_STR = "^[A-Z0-9]{2,15}$";

const std::regex  VAT::regex_(VAT::REGEX_STR);

VAT::VAT(){}

VAT::VAT(const std::string &vat){
    if(!std::regex_match(vat, VAT::regex_))
        throw VAT::InvalidVAT(vat);
    vat_ = vat;
}

std::istream& operator>>(std::istream &is,       VAT &v){
    std::string s;
    try{
        std::getline(is, s);
        v = VAT(s);
    }catch(...){
        is.setstate(std::ios::failbit);
    }
    return is;
}

std::ostream& operator<<(std::ostream &os, const VAT &v){
    if(!std::regex_match(v.vat_, VAT::regex_)){
        os.setstate(std::ios::failbit);
    }else{
        os << v.vat_;
    }
    return os;
}

VAT::InvalidVAT::InvalidVAT(const std::string &vat):
    std::invalid_argument("VAT has at least one invalid character (regex format is '"+VAT::REGEX_STR+"')"),
    vat_(vat){}

std::string VAT::InvalidVAT::get_vat() const{
    return vat_;
}
