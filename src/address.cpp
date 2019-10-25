#include "address.h"

const string Address::DEFAULT_FORMAT = "%strt\n%pst %cty\n%district, %ctry";

Address::Address(string street, string postal_code, string city, string district, string country):
                 street_(street), postal_code_(postal_code), city_(city), district_(district), country_(country){}

string Address::format(string s) const{
    stringstream ss;
    ss << street_ << "\n"
       << postal_code_ << " " << city_ << "\n"
       << district_ << ", " << country_ << endl;
    return ss.str();
}

ostream& operator<<(ostream &os, const Address &a){
    return os << a.format();
}
