#include "vat.h"

#include "utils.h"

VAT::VAT(const std::string &vat){
    if(vat.size() > 15) throw VAT::VATTooLong(vat);
    vat_ = vat;
}

VAT::VATTooLong::VATTooLong(const std::string &vat):
    invalid_argument("VAT too long ("+vat+" has size "+utils::itos(vat.size())+">15)"){}

std::string VAT::VATTooLong::get_vat() const{
    return vat_;
}
