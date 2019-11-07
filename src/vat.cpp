#include "vat.h"

const std::string VAT::REGEX_STR = "^[A-Z0-9]{2,15}$";

VAT::VAT():utils::string_regex(VAT::REGEX_STR){}

VAT::VAT(const std::string &vat):VAT(){
    *this = vat;
}
