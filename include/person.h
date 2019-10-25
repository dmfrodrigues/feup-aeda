#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include "address.h"
#include "vat.h"
#include "phonenumber.h"
#include "currency.h"

class Person {
private:
    std::string name_;
    PhoneNumber phonenumber_;
public:
    Person(const std::string &name, const PhoneNumber &phonenumber);
};

class User : public Person{
private:
    std::string user_;
    std::string pswd_;
public:
    User(const std::string &name, const PhoneNumber &phonenumber,
         const std::string &user, const std::string &pswd       );
};

class Client: public User {
private:
    Address address_;
    VAT vat_;
public:
    Client(const std::string &name   , const PhoneNumber &phonenumber,
           const std::string &user   , const std::string &pswd       ,
           const Address     &address, const VAT         &vat        );
};

class Employee: public User {
private:
    Currency base_salary_;
public:
    Employee(const std::string &name, const PhoneNumber &phonenumber,
             const std::string &user, const std::string &pswd,
             const Currency    &base_salary);
    enum Type{
        Manager,
        Driver
    };
    virtual Employee::Type get_type() const = 0;
};

class Manager: public Employee {
public:
    Manager(const std::string &name, const PhoneNumber &phonenumber,
            const std::string &user, const std::string &pswd,
            const Currency    &base_salary_);
    Employee::Type get_type() const;
};

class Driver: public Employee {
public:
    Driver(const std::string &name, const PhoneNumber &phonenumber,
           const std::string &user, const std::string &pswd,
           const Currency    &base_salary_);
    Employee::Type get_type() const;
};

#endif //PERSON_H_INCLUDED
