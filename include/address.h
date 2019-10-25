#ifndef ADDRESS_H_INCLUDED
#define ADDRESS_H_INCLUDED

class Address{
private:
    std::string street_;
    std::string postal_code_;
    std::string city_;
    std::string district_;
    std::string country_;
    static const std::string DEFAULT_FORMAT;
public:
    Address();
    Address(std::string street, std::string postal_code, std::string city, std::string district, std::string country);
    std::string format(const std::string &s = DEFAULT_FORMAT) const;

    friend std::istream& operator>>(std::istream &is, Address &a);
};

std::ostream& operator<<(std::ostream &os, const Address &a);

#endif //ADDRESS_H_INCLUDED
