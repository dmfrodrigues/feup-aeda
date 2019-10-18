#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include "address.h"
#include "vat.h"
#include "phonenumber.h"
#include "currency.h"

class Person {
private:
    std::string name_;
    Address address_;
    VAT vat_;
    PhoneNumber phonenumber_;
public:
    Person(const std::string &name, const Address &address, const VAT &vat, const PhoneNumber &phonenumber);
};

typedef Person Client;

class Employee: public Person {
private:
    Currency base_salary_;
public:
    Employee(const std::string &name, const Address &address, const VAT &vat, const PhoneNumber &phonenumber, const Currency &base_salary_);
    enum Type{
        Manager,
        Driver
    };
    virtual Employee::Type get_type() const = 0;
};

class Manager: public Employee {
public:
    Manager(const std::string &name, const Address &address, const VAT &vat, const PhoneNumber &phonenumber, const Currency &base_salary_);
    Employee::Type get_type() const;
};

class Driver: public Employee {
public:
    Driver(const std::string &name, const Address &address, const VAT &vat, const PhoneNumber &phonenumber, const Currency &base_salary_);
    Employee::Type get_type() const;
};

#endif //PERSON_H_INCLUDED
