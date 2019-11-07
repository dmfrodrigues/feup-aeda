#include "phonenumber.h"

const std::string PhoneNumber::REGEX_STR = "^[+-a-zA-Z0-9 *#()/,.;]*$";

PhoneNumber::PhoneNumber():utils::string_regex(PhoneNumber::REGEX_STR){}

PhoneNumber::PhoneNumber(const std::string &number):PhoneNumber(){
    *this = number;
}
