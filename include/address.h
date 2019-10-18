#ifndef ADDRESS_H_INCLUDED
#define ADDRESS_H_INCLUDED

class Address{
private:
    std::string street;
    std::string postal_code;
    std::string city;
    std::string district;
    std::string country;
public:
    Address(std::string street, std::string postal_code, std::string city, std::string district, std::string country);
};

#endif //ADDRESS_H_INCLUDED
