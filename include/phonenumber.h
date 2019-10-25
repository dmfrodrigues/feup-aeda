#ifndef PHONENUMBER_H_INCLUDED
#define PHONENUMBER_H_INCLUDED

using namespace std;

class PhoneNumber{
private:
    static const std::string regex_str_;
    static const std::regex  regex_;
    std::string number_;
public:
    PhoneNumber(string number);
    class InvalidPhoneNumber: public invalid_argument{
    private:
        string number_;
    public:
        InvalidPhoneNumber(string number);
        string get_number()const;
    };
};

#endif //PHONENUMBER_H_INCLUDED
