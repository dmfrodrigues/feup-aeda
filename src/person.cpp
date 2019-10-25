#include "person.h"

Person::Person(string name, const PhoneNumber &phonenumber):
               name_(name), phonenumber_(phonenumber){}

User::User(string name, const PhoneNumber &phonenumber,
           string user, string pswd       ):
           Person(name, phonenumber),
           user_(user), pswd_(pswd){}

Client::Client(string name   , const PhoneNumber &phonenumber,
               string user   , string pswd       ,
               const Address     &address, const VAT         &vat        ):
               User(name, phonenumber, user, pswd),
               address_(address), vat_(vat){}

Employee::Employee(string name, const PhoneNumber &phonenumber,
                   string user, string pswd,
                   const Currency    &base_salary):
                   User(name, phonenumber, user, pswd),
                   base_salary_(base_salary){}

Manager::Manager(string name, const PhoneNumber &phonenumber,
                 string user, string pswd,
                 const Currency    &base_salary):
                 Employee(name, phonenumber, user, pswd, base_salary){}

Driver::Driver(string name, const PhoneNumber &phonenumber,
               string user, string pswd,
               const Currency    &base_salary):
               Employee(name, phonenumber, user, pswd, base_salary){}

Employee::Type Manager::get_type() const{ return Employee::Type::Manager; }

Employee::Type Driver::get_type() const{ return Employee::Type::Driver; }
