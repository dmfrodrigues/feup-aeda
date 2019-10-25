#include "person.h"

Person::Person(const std::string &name, const PhoneNumber &phonenumber):
               name_(name), phonenumber_(phonenumber){}

User::User(const std::string &name, const PhoneNumber &phonenumber,
           const std::string &user, const std::string &pswd       ):
           Person(name, phonenumber),
           user_(user), pswd_(pswd){}

Client::Client(const std::string &name   , const PhoneNumber &phonenumber,
               const std::string &user   , const std::string &pswd       ,
               const Address     &address, const VAT         &vat        ):
               User(name, phonenumber, user, pswd),
               address_(address), vat_(vat){}

Employee::Employee(const std::string &name, const PhoneNumber &phonenumber,
                   const std::string &user, const std::string &pswd,
                   const Currency    &base_salary):
                   User(name, phonenumber, user, pswd),
                   base_salary_(base_salary){}

Manager::Manager(const std::string &name, const PhoneNumber &phonenumber,
                 const std::string &user, const std::string &pswd,
                 const Currency    &base_salary):
                 Employee(name, phonenumber, user, pswd, base_salary){}

Driver::Driver(const std::string &name, const PhoneNumber &phonenumber,
               const std::string &user, const std::string &pswd,
               const Currency    &base_salary):
               Employee(name, phonenumber, user, pswd, base_salary){}

Employee::Type Manager::get_type() const{ return Employee::Type::Manager; }

Employee::Type Driver::get_type() const{ return Employee::Type::Driver; }
