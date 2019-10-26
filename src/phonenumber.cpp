#include "phonenumber.h"

const std::regex  PhoneNumber::regex_(REGEX_STR);

PhoneNumber::PhoneNumber(const std::string &number){
    if(!std::regex_match(number, PhoneNumber::regex_))
        throw PhoneNumber::InvalidPhoneNumber(number);
    number_ = number;
}

PhoneNumber::InvalidPhoneNumber::InvalidPhoneNumber(const std::string &number):
    std::invalid_argument("Phone number had at least one invalid character (regex format is '"+PhoneNumber::REGEX_STR+"')"),
    number_(number){}

const std::string& PhoneNumber::InvalidPhoneNumber::get_number()const{
    return number_;
}

std::ostream& operator<<(std::ostream &os, const PhoneNumber &p){
    return (os << p.number_);
}

std::istream& operator>>(std::istream &is,       PhoneNumber &p){
    std::string s;
    std::getline(is, s);
    try{
        p = PhoneNumber(s);
    }catch(...){
        is.setstate(std::ios::failbit);
    }
    return is;
}
