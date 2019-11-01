#include "person.h"

///PERSON
Person::Person(const std::string &name, const PhoneNumber &phonenumber):
               name_(name), phonenumber_(phonenumber){}

std::istream& Person::input(std::istream &is){
    std::getline(is, name_);
    is >> phonenumber_;
    return is;
}
std::istream& operator>>(std::istream &is,       Person &p){ return p.input(is); }
std::ostream& operator<<(std::ostream &os, const Person &p){
    os << p.name_        << "\n"
       << p.phonenumber_ << "\n";
    return os;
}

///USER
User::User(const std::string &name    , const PhoneNumber &phonenumber,
           const std::string &username, const std::string &pswd       ):
           Person(name, phonenumber),
           username_(username), pswd_(pswd){}

std::istream& User::input(std::istream &is){
   Person::input(is);
   std::getline(is, username_);
   std::getline(is, pswd_);
   return is;
}
std::istream& operator>>(std::istream &is,       User &p){ return p.input(is); }
std::ostream& operator<<(std::ostream &os, const User &p){
    os << static_cast<const Person&>(p) << "\n"
       << p.username_                   << "\n"
       << p.pswd_;
    return os;
}

///CLIENT
Client::Client(const std::string &name   , const PhoneNumber &phonenumber,
               const std::string &user   , const std::string &pswd       ,
               const Address     &address, const VAT         &vat        ):
               User(name, phonenumber, user, pswd),
               address_(address), vat_(vat){}

std::istream& Client::input(std::istream &is){
    User::input(is);
    is >> address_ >> vat_;
    return is;
}
std::istream& operator>>(std::istream &is,       Client &p){ return p.input(is); }
std::ostream& operator<<(std::ostream &os, const Client &p){
    os << static_cast<const User&>(p) << "\n"
       << p.address_                  << "\n"
       << p.vat_;
    return os;
}

///EMPLOYEE
Employee::Employee(const std::string &name, const PhoneNumber &phonenumber,
                   const std::string &user, const std::string &pswd,
                   const Currency    &base_salary):
                   User(name, phonenumber, user, pswd),
                   base_salary_(base_salary){}

std::istream& Employee::input(std::istream &is){
    User::input(is);
    is >> base_salary_;
    return is;
}
std::istream& operator>>(std::istream &is,       Employee &p){ return p.input(is); }
std::ostream& operator<<(std::ostream &os, const Employee &p){
    os << static_cast<const User&>(p) << "\n"
       << p.base_salary_;
    return os;
}

///MANAGER
Manager::Manager(const std::string &name, const PhoneNumber &phonenumber,
                 const std::string &user, const std::string &pswd,
                 const Currency    &base_salary):
                 Employee(name, phonenumber, user, pswd, base_salary){}

Employee::Type Manager::get_type() const{ return Employee::Type::Manager; }

std::istream& Manager::input(std::istream &is){
    Employee::input(is);
    return is;
}
std::istream& operator>>(std::istream &is,       Manager &p){ return p.input(is); }
std::ostream& operator<<(std::ostream &os, const Manager &p){
    os << static_cast<const Employee&>(p);
    return os;
}

///DRIVER
Driver::Driver(const std::string &name, const PhoneNumber &phonenumber,
               const std::string &user, const std::string &pswd,
               const Currency    &base_salary):
               Employee(name, phonenumber, user, pswd, base_salary){}

std::istream& Driver ::input(std::istream &is){
   Employee::input(is);
   return is;
}

Employee::Type Driver ::get_type() const{ return Employee::Type::Driver; }

std::istream& operator>>(std::istream &is,       Driver &p){ return p.input(is); }
std::ostream& operator<<(std::ostream &os, const Driver &p){
    os << static_cast<const Employee&>(p);
    return os;
}
