#ifndef ADDRESS_H_INCLUDED
#define ADDRESS_H_INCLUDED

/**
 * @brief Class for real-world address.
 */
class Address{
private:
    std::string street_;
    std::string postal_code_;
    std::string city_;
    std::string district_;
    std::string country_;
public:
    /**
     * @brief Default address format.
     */
    static const std::string DEFAULT_FORMAT;
    /**
     * @brief Constructor with no arguments
     */
    Address();
    /**
     * @brief Constructor with arguments.
     * @param   street      Street name and house number, usually separated by comma.
     * @param   postal_code Postal code.
     * @param   city        City, usually in capital letters and associated to postal code.
     * @param   district    District, province or state.
     * @param   country     Country
     */
    Address(const std::string &street, const std::string &postal_code, const std::string &city, const std::string &district, const std::string &country);
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
     * @brief   Overload of <em> operator>> </em>. Expects input in @ref Address::DEFAULT_FORMAT.
     */
    friend std::istream& operator>>(std::istream &is, Address &a);

    /**
     * @brief   Overload of <em> operator<< </em>. Prints in @ref Address::DEFAULT_FORMAT.
     */
    friend std::ostream& operator<<(std::ostream &os, const Address &a);
};

const std::string Address::DEFAULT_FORMAT = "%street\n%postal\n%city\n%district\n%country";

#endif //ADDRESS_H_INCLUDED
