#include "phonenumber.h"

const std::string PhoneNumber::regex_str_("^[+-a-zA-Z0-9 *#()/,.;]*$");
const std::regex  PhoneNumber::regex_(regex_str_);

PhoneNumber::PhoneNumber(const std::string &number){
    if(!std::regex_match(number, PhoneNumber::regex_))
        throw PhoneNumber::InvalidPhoneNumber(number);
    number_ = number;
}

PhoneNumber::InvalidPhoneNumber::InvalidPhoneNumber(const std::string &number):
    std::invalid_argument("Phone number had at least one invalid character (regex format is '"+PhoneNumber::regex_str_+"')"),
    number_(number){}

const std::string& PhoneNumber::InvalidPhoneNumber::get_number()const{
    return number_;
}
