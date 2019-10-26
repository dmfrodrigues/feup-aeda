#ifndef PHONENUMBER_H_INCLUDED
#define PHONENUMBER_H_INCLUDED

class PhoneNumber{
private:
    static const std::string regex_str_;
    static const std::regex  regex_;
    std::string number_;
public:
    PhoneNumber(const std::string &number);
    class InvalidPhoneNumber: public std::invalid_argument{
    private:
        std::string number_;
    public:
        InvalidPhoneNumber(const std::string &number);
        const std::string& get_number()const;
    };
    friend std::ostream& operator<<(std::ostream &os, const PhoneNumber &p);
    friend std::istream& operator>>(std::istream &is,       PhoneNumber &p);
};

#endif //PHONENUMBER_H_INCLUDED
