#include "person.h"

Person::Person(const std::string &name, const Address &address, const VAT &vat, const PhoneNumber &phonenumber):
               name_(name), address_(address), vat_(vat), phonenumber_(phonenumber){}

Employee::Employee(const std::string &name, const Address &address, const VAT &vat, const PhoneNumber &phonenumber, const Currency &base_salary):
                   Person(name, address, vat, phonenumber), base_salary_(base_salary){}

Manager::Manager(const std::string &name, const Address &address, const VAT &vat, const PhoneNumber &phonenumber, const Currency &base_salary):
                 Employee(name, address, vat, phonenumber, base_salary){}

Driver::Driver(const std::string &name, const Address &address, const VAT &vat, const PhoneNumber &phonenumber, const Currency &base_salary):
               Employee(name, address, vat, phonenumber, base_salary){}

Employee::Type Manager::get_type() const{ return Employee::Type::Manager; }

Employee::Type Driver::get_type() const{ return Employee::Type::Driver; }
