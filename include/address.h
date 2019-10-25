#ifndef ADDRESS_H_INCLUDED
#define ADDRESS_H_INCLUDED

using namespace std;

class Address{
private:
    string street_;
    string postal_code_;
    string city_;
    string district_;
    string country_;
    static const string DEFAULT_FORMAT;
public:
    Address(string street, string postal_code, string city, string district, string country);
    string format(string s  = Address::DEFAULT_FORMAT) const;
    friend ostream& operator<<(ostream &os, const Address &a);
};

#endif //ADDRESS_H_INCLUDED
