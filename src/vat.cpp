#include "vat.h"

#include "utils.h"

const std::regex  VAT::regex_(VAT::REGEX_STR);

VAT::VAT(const std::string &vat){
    if(!std::regex_match(vat, VAT::regex_))
        throw VAT::InvalidVAT(vat);
    vat_ = vat;
}

VAT::InvalidVAT::InvalidVAT(const std::string &vat):
    std::invalid_argument("VAT has at least one invalid character (regex format is '"+VAT::REGEX_STR+"')"),
    vat_(vat){}

std::string VAT::InvalidVAT::get_vat() const{
    return vat_;
}
