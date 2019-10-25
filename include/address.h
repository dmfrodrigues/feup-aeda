#ifndef ADDRESS_H_INCLUDED
#define ADDRESS_H_INCLUDED

using namespace std;

class Address{
private:
    std::string street_;
    std::string postal_code_;
    std::string city_;
    std::string district_;
    std::string country_;
    static const std::string DEFAULT_FORMAT;
public:
    Address(std::string street, std::string postal_code, std::string city, std::string district, std::string country);
    std::string format(const std::string &s = DEFAULT_FORMAT) const;
};

std::ostream& operator<<(std::ostream &os, const Address &a);

#endif //ADDRESS_H_INCLUDED
