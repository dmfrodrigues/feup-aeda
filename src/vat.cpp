#include "vat.h"

#include "utils.h"

VAT::VAT(string vat){
    if(vat.size() > 15) throw VAT::VATTooLong(vat);
    vat_ = vat;
}

VAT::VATTooLong::VATTooLong(string vat):
    invalid_argument("VAT too long ("+vat+" has size "+itos(vat.size())+">15)"){}

string VAT::VATTooLong::get_vat() const{
    return vat_;
}
