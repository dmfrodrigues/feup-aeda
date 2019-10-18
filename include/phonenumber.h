#ifndef PHONENUMBER_H_INCLUDED
#define PHONENUMBER_H_INCLUDED

class PhoneNumber{
private:
    static const std::string regex_str;
    static const std::regex  regex;
    std::string number_;
public:
    PhoneNumber(const std::string &number);
    class InvalidPhoneNumber: public std::invalid_argument{
    private:
        std::string number_;
    public:
        InvalidPhoneNumber(const std::string &number);
        std::string get_number()const;
    };
};

#endif //PHONENUMBER_H_INCLUDED
