#ifndef PHONENUMBER_H_INCLUDED
#define PHONENUMBER_H_INCLUDED

#include <regex>
#include <string>

const char REGEX_STR[] = "^[+-a-zA-Z0-9 *#()/,.;]*$";

/**
 * @brief Class to store phone number.
 */
class PhoneNumber{
private:
    static const std::regex  REGEX;
    std::string number_;
public:
    /**
     * @brief   Regular expression string that describes a valid phone number.
     */
    /**
     * @brief   Empty constructor.
     */
    PhoneNumber();
    /**
     * @brief   Constructs from string containing phone number.
     *
     * @param   number  String with phone number
     * @exception InvalidPhoneNumber    When phone number does not match regular expression
     */
    PhoneNumber(const std::string &number);

    /**
     * @brief   Class for denoting an invalid phone number
     */
    class InvalidPhoneNumber: public std::invalid_argument{
    private:
        std::string number_;
    public:
        /**
         * @brief   Constructor accepting the phone number that caused the exception.
         *
         * Also sets the string returned by <em> std::exception::what() </em>.
         * @param   number  Phone number
         */
        InvalidPhoneNumber(const std::string &number);
        /**
         * @brief   Get phone number from which the exception was built.
         * @return  Phone number
         */
        const std::string& get_number()const;
    };

    /**
     * @brief       Overload of <em> operator== </em>.
     */
    bool operator==(const PhoneNumber &p) const;
    /**
     * @brief       Overload of <em> operator>> </em>. Reads an entire line and expects it to be a phone number.
     */
    friend std::istream& operator>>(std::istream &is,       PhoneNumber &p);
    /**
     * @brief       Overload of <em> operator<< </em>.
     */
    friend std::ostream& operator<<(std::ostream &os, const PhoneNumber &p);
};

#endif //PHONENUMBER_H_INCLUDED
