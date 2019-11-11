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

bool Person::in(std::istream &is, std::ostream &os) {
    if (!utils::input("Name: ",         name_,        is, os)|
        !utils::input("Phone Number: ", phonenumber_, is, os)) return false;
    return true;
}

bool Person::edit(int property, std::istream&is, std::ostream &os) {
    switch(property) {
    case 0:
        if (!utils::input("Name: ", name_, is, os))                 return false;
        else                                                        return true;
        break;
    case 1:
        if (!utils::input("Phone Number: ", phonenumber_, is, os))  return false;
        else                                                        return true;
        break;
    default:
        return false;
    }
}

std::istream& operator>>(std::istream &is,       Person &p){ return p.input(is); }
std::ostream& operator<<(std::ostream &os, const Person &p){
    os << utils::urlencode(p.name_) << "\n"
       << p.phonenumber_;
    return os;
}

///USER
//Username
const std::string User::Username::REGEX_STR = "^[0-9a-zA-Z_]*$";
User::Username::Username():string_regex(User::Username::REGEX_STR){}
User::Username::Username(const std::string &username):Username(){
    *this = username;
}
User::Username& User::Username::operator=(const std::string &s){
    string_regex::operator=(s);
    return *this;
}
//Password
const std::string User::Password::REGEX_STR = "^[0-9a-zA-Z_]*$";
User::Password::Password():string_regex(User::Password::REGEX_STR){}
User::Password::Password(const std::string &password):Password(){
    *this = password;
}
User::Password& User::Password::operator=(const std::string &s){
    string_regex::operator=(s);
    return *this;
}
//User
User::User(const std::string &name    , const PhoneNumber &phonenumber,
           const Username    &username, const Password    &password   ,
           const Address     &address , const VAT         &vat        ):
           Person(name, phonenumber),
           username_(username), password_(password),
           address_ (address ), vat_ (vat ){}

std::istream& User::input(std::istream &is){
    Person::input(is);
    std::string s;
    try{
        is >> username_;
        is >> password_;
        is >> address_;
        is >> vat_;
    }catch(...){
        is.setstate(std::ios::failbit);
    }
    return is;
}

bool User::in(std::istream &is, std::ostream &os) {
    if (!Person::in(is, os)) return false;
    if (!utils::input("Username: ", username_, is, os)|
        !utils::input("Password: ", password_, is, os)) return false;

    if (!address_.in(is, os)) return false;

    if (!utils::input("VAT: ", vat_, is, os)) return false;

    return true;
}

bool User::edit(int property, std::istream&is, std::ostream &os) {
    switch(property) {
    case 0:
        if (!utils::input("Username: ", username_, is, os))         return false;
        else                                                        return true;
        break;
    case 1:
        return Person::edit(0, is, os);
        break;
    case 2:
        if (!address_.in(is, os))                                   return false;
        else                                                        return true;
        break;
    case 3:
        return Person::edit(1, is, os);
        break;
    case 4:
        if (!utils::input("VAT: ", vat_, is, os))                   return false;
        else                                                        return true;
        break;
    case 5:
        if (!utils::input("Password: ", password_, is, os))         return false;
        else                                                        return true;
        break;
    default:
        return false;
    }
}

bool User::verifyCredentials(const std::string &password) const{
    return this->password_ == Password(password);
}

std::istream& operator>>(std::istream &is,       User &p){ return p.input(is); }
std::ostream& operator<<(std::ostream &os, const User &p){
    os << static_cast<const Person&>(p) << "\n"
       << p.username_                   << "\n"
       << p.password_                   << "\n"
       << p.address_                    << "\n"
       << p.vat_;
    return os;
}

///CLIENT
Client::Client(const std::string &name   , const PhoneNumber &phonenumber,
               const Username    &user   , const Password    &password   ,
               const Address     &address, const VAT         &vat        ):
               User(name, phonenumber, user, password, address, vat){}

std::istream& Client::input(std::istream &is){
    User::input(is);
    return is;
}

User::Type Client::get_type() const { return User::Type::client; }

bool Client::in(std::istream &is, std::ostream &os) {
    return User::in(is, os);
}

bool Client::edit(int property, std::istream&is, std::ostream &os) {
    return User::edit(property, is, os);
}

std::istream& operator>>(std::istream &is,       Client &p){ return p.input(is); }
std::ostream& operator<<(std::ostream &os, const Client &p){
    os << static_cast<const User&>(p);
    return os;
}

///EMPLOYEE
Employee::Employee(const std::string &name       , const PhoneNumber &phonenumber,
                   const Username    &user       , const Password    &password   ,
                   const Address     &address    , const VAT      &vat           ,
                   const Currency    &base_salary):
                   User(name, phonenumber, user, password, address, vat),
                   base_salary_(base_salary){}

std::istream& Employee::input(std::istream &is){
    User::input(is);
    is >> base_salary_;
    return is;
}

bool Employee::in(std::istream &is, std::ostream &os) {
    if (!User::in(is, os)) return false;

    if (!utils::input("Salary: ", base_salary_, is, os)) return false;

    return true;
}

bool Employee::edit(int property, std::istream&is, std::ostream &os) {
    if (property < 5)
        return User::edit(property, is, os);
    switch(property) {
    case 5:
        if (!utils::input("Salary: ", base_salary_, is, os))        return false;
        else                                                        return true;
        break;
    case 6:
        return User::edit(5, is, os);
        break;
    default:
        return false;
    }
}

std::istream& operator>>(std::istream &is,       Employee &p){ return p.input(is); }
std::ostream& operator<<(std::ostream &os, const Employee &p){
    os << static_cast<const User&>(p) << "\n"
       << p.base_salary_;
    return os;
}

///MANAGER
Manager::Manager(const std::string &name       , const PhoneNumber &phonenumber,
                 const Username    &user       , const Password    &password   ,
                 const Address     &address    , const VAT         &vat        ,
                 const Currency    &base_salary):
                 Employee(name, phonenumber, user, password, address, vat, base_salary){}

User::Type Manager::get_type() const { return User::Type::manager; }

std::istream& Manager::input(std::istream &is){
    Employee::input(is);
    return is;
}

bool Manager::in(std::istream &is, std::ostream &os) {
    return Employee::in(is, os);
}

bool Manager::edit(int property, std::istream&is, std::ostream &os) {
    return Employee::edit(property, is, os);
}

std::istream& operator>>(std::istream &is,       Manager &p){ return p.input(is); }
std::ostream& operator<<(std::ostream &os, const Manager &p){
    os << static_cast<const Employee&>(p);
    return os;
}

///DRIVER
Driver::Driver(const std::string &name       , const PhoneNumber &phonenumber,
               const Username    &user       , const Password    &password   ,
               const Address     &address    , const VAT         &vat        ,
               const Currency    &base_salary):
               Employee(name, phonenumber, user, password, address, vat, base_salary){}

std::istream& Driver ::input(std::istream &is){
   Employee::input(is);
   return is;
}

User::Type Driver::get_type() const { return User::Type::driver; }

bool Driver::in(std::istream &is, std::ostream &os) {
    return Employee::in(is, os);
}

bool Driver::edit(int property, std::istream&is, std::ostream &os) {
    return Employee::edit(property, is, os);
}

std::istream& operator>>(std::istream &is,       Driver &p){ return p.input(is); }
std::ostream& operator<<(std::ostream &os, const Driver &p){
    os << static_cast<const Employee&>(p);
    return os;
}
