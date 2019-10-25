#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

using namespace std;

#include "address.h"
#include "vat.h"
#include "phonenumber.h"
#include "currency.h"

class Person {
private:
    string name_;
    PhoneNumber phonenumber_;
public:
    Person(string name, const PhoneNumber &phonenumber);
};

class User : public Person{
private:
    string user_;
    string pswd_;
public:
    User(string name, const PhoneNumber &phonenumber,
         string user, string pswd       );
};

class Client: public User {
private:
    Address address_;
    VAT vat_;
public:
    Client(string name   , const PhoneNumber &phonenumber,
           string user   , string pswd       ,
           const Address     &address, const VAT         &vat        );
};

class Employee: public User {
private:
    Currency base_salary_;
public:
    Employee(string name, const PhoneNumber &phonenumber,
             string user, string pswd,
             const Currency    &base_salary);
    enum Type{
        Manager,
        Driver
    };
    virtual Employee::Type get_type() const = 0;
};

class Manager: public Employee {
public:
    Manager(string name, const PhoneNumber &phonenumber,
            string user, string pswd,
            const Currency    &base_salary_);
    Employee::Type get_type() const;
};

class Driver: public Employee {
public:
    Driver(string name, const PhoneNumber &phonenumber,
           string user, string pswd,
           const Currency    &base_salary_);
    Employee::Type get_type() const;
};

#endif //PERSON_H_INCLUDED
