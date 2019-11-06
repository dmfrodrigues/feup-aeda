#include "person.h"

#include "utils.h"

///PERSON
Person::Person(const std::string &name, const PhoneNumber &phonenumber):
               name_(name), phonenumber_(phonenumber){}

std::istream& Person::input(std::istream &is){
    std::string s; is >> s;
    try{
        name_ = utils::urldecode(s);
    }catch(...){
        is.setstate(std::ios::failbit);
    }
    is >> phonenumber_;
    return is;
}
std::istream& operator>>(std::istream &is,       Person &p){ return p.input(is); }
std::ostream& operator<<(std::ostream &os, const Person &p){
    os << utils::urlencode(p.name_) << "\n"
       << p.phonenumber_;
    return os;
}

///USER
User::User(const std::string &name    , const PhoneNumber &phonenumber,
           const std::string &username, const std::string &pswd       ,
           const Address     &address , const VAT         &vat        ):
           Person(name, phonenumber),
           username_(username), pswd_(pswd),
           address_ (address ), vat_ (vat ){}

std::istream& User::input(std::istream &is){
    Person::input(is);
    std::string s;
    try{
        is >> s; username_ = utils::urldecode(s);
        is >> s; pswd_     = utils::urldecode(s);
        is >> address_;
        is >> vat_;
    }catch(...){
        is.setstate(std::ios::failbit);
    }
    return is;
}
std::istream& operator>>(std::istream &is,       User &p){ return p.input(is); }
std::ostream& operator<<(std::ostream &os, const User &p){
    os << static_cast<const Person&>(p) << "\n"
       << utils::urlencode(p.username_) << "\n"
       << utils::urlencode(p.pswd_    ) << "\n"
       << p.address_                    << "\n"
       << p.vat_;
    return os;
}

///CLIENT
Client::Client(const std::string &name   , const PhoneNumber &phonenumber,
               const std::string &user   , const std::string &pswd       ,
               const Address     &address, const VAT         &vat        ):
               User(name, phonenumber, user, pswd, address, vat){}

std::istream& Client::input(std::istream &is){
    User::input(is);
    return is;
}

User::UserType Client::get_user_type() const { return User::UserType::client; }

std::istream& operator>>(std::istream &is,       Client &p){ return p.input(is); }
std::ostream& operator<<(std::ostream &os, const Client &p){
    os << static_cast<const User&>(p);
    return os;
}

///EMPLOYEE
Employee::Employee(const std::string &name       , const PhoneNumber &phonenumber,
                   const std::string &user       , const std::string &pswd       ,
                   const Address     &address    , const VAT      &vat           ,
                   const Currency    &base_salary):
                   User(name, phonenumber, user, pswd, address, vat),
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
Manager::Manager(const std::string &name       , const PhoneNumber &phonenumber,
                 const std::string &user       , const std::string &pswd       ,
                 const Address     &address    , const VAT         &vat        ,
                 const Currency    &base_salary):
                 Employee(name, phonenumber, user, pswd, address, vat, base_salary){}

User::UserType Manager::get_user_type() const { return User::UserType::manager; }

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
Driver::Driver(const std::string &name       , const PhoneNumber &phonenumber,
               const std::string &user       , const std::string &pswd       ,
               const Address     &address    , const VAT         &vat        ,
               const Currency    &base_salary):
               Employee(name, phonenumber, user, pswd, address, vat, base_salary){}

std::istream& Driver ::input(std::istream &is){
   Employee::input(is);
   return is;
}

User::UserType Driver::get_user_type() const { return User::UserType::driver; }

std::istream& operator>>(std::istream &is,       Driver &p){ return p.input(is); }
std::ostream& operator<<(std::ostream &os, const Driver &p){
    os << static_cast<const Employee&>(p);
    return os;
}
