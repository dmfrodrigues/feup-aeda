/**
 * @file address.h
 */

#ifndef ADDRESS_H_INCLUDED
#define ADDRESS_H_INCLUDED

#include "utils.h"

/**
 * @brief Class for real-world address.
 */
class Address{
public:
    /** @brief Postal code. */
    class PostalCode: public utils::string_regex{
    public:
        /// @brief Regex a postal code is supposed to match.
        static const std::string REGEX_STR;
        /// @brief Empty constructor.
        explicit PostalCode();
        /// @brief Constructor accepting postal code as \p std::string.
        explicit PostalCode(const std::string &postal_code);
        /// @brief Overload of \a operator= .
        PostalCode& operator=(const std::string &postal_code);
    };
private:
    std::string street_;
    PostalCode postal_code_;
    std::string city_;
    std::string district_;
    std::string country_;
public:
    /**
     * @brief Default address format.
     */
    static const std::string DEFAULT_FORMAT;
    /**
     * @brief Empty constructor.
     */
    Address();
    /**
     * @brief   Format address to a given format.
     * @param   fmt String that contains the text to be written to the output string.
     *              It can optionally contain format specifiers that are replaced
     *              by the values of the object. \n
     *              A <em> format specifier </em> follows this prototype: \n
     *              <em> \%specifier </em> \n
     *              where \a specifier is one of:
     *              <em> specifier </em> | Output
     *              -------------------- | ------------------------------
     *              <em> street    </em> | Street name and house number
     *              <em> postal    </em> | Postal code
     *              <em> city      </em> | City associated to postal code
     *              <em> district  </em> | District, province or state
     *              <em> country   </em> | Country
     */
    std::string format(const std::string &fmt = DEFAULT_FORMAT) const;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    bool in(std::istream &is, std::ostream &os);

    /** @brief   Overload of \a operator>>. Expects input in @ref Address::DEFAULT_FORMAT. */
    friend std::istream& operator>>(std::istream &is, Address &a);
    /** @brief   Overload of \a operator<<. Prints in @ref Address::DEFAULT_FORMAT.*/
    friend std::ostream& operator<<(std::ostream &os, const Address &a);
};

#endif //ADDRESS_H_INCLUDED
