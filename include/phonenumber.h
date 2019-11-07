#ifndef PHONENUMBER_H_INCLUDED
#define PHONENUMBER_H_INCLUDED

#include "utils.h"

/**
 * @brief Class to store phone number.
 */
class PhoneNumber: public utils::string_regex{
public:
    /**
     * @brief   Regular expression string that describes a valid phone number.
     */
    static const std::string REGEX_STR;
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
};

#endif //PHONENUMBER_H_INCLUDED
