#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include "address.h"
#include "vat.h"
#include "phonenumber.h"

class Person{
private:
    std::string name;
    Address address;
    VAT vat;
    PhoneNumber phone_num;
};

#endif //PERSON_H_INCLUDED
