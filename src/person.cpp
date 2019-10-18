#include "person.h"

Person::Person(const std::string &name, const Address &address, const VAT &vat, const PhoneNumber &phonenumber):
               name_(name), address_(address), vat_(vat), phonenumber_(phonenumber){}
