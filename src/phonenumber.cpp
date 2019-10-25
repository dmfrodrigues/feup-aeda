#include "phonenumber.h"

const string PhoneNumber::regex_str_("^[+-a-zA-Z0-9 *#()/,.;]*$");
const regex  PhoneNumber::regex_(regex_str_);

PhoneNumber::PhoneNumber(string number){
    if(!regex_match(number, PhoneNumber::regex_))
        throw PhoneNumber::InvalidPhoneNumber(number);
    number_ = number;
}

PhoneNumber::InvalidPhoneNumber::InvalidPhoneNumber(string number):
    invalid_argument("Phone number had at least one invalid character (regex format is '"+PhoneNumber::regex_str_+"')"),
    number_(number){}

string PhoneNumber::InvalidPhoneNumber::get_number()const{
    return number_;
}
