#ifndef VAT_H_INCLUDED
#define VAT_H_INCLUDED

#include <string>
#include <stdexcept>
#include <regex>

/**
 * @brief %VAT number.
 */
class VAT{
private:
    static const std::regex REGEX;
    std::string vat_;
public:
    /**
     * @brief   Regular expression string that describes a valid VAT.
     */
    static const std::string REGEX_STR;
    /**
     * @brief   Empty constructor
     */
    VAT();
    /**
     * @brief   Constructor accepting %VAT as string
     * @param   vat String containing %VAT
     * @exception   VAT::VATTooLong When VAT is longer than the maximum size
     */
    VAT(const std::string &vat);

    /**
     * @brief       Overload of <em> operator>> </em>. Reads an entire line and expects it to be a VAT.
     */
    friend std::istream& operator>>(std::istream &is,       VAT &v);
    /**
     * @brief       Overload of <em> operator<< </em>.
     */
    friend std::ostream& operator<<(std::ostream &os, const VAT &v);

    /**
     * @brief   Exception class for when the provided %VAT string is too long.
     */
    class InvalidVAT: public std::invalid_argument{
    private:
        std::string vat_;
    public:
        /**
         * @brief Constructor accepting %VAT string that caused the exception.
         *
         * Also sets the string returned by <em> std::exception::what() </em>.
         * @param   vat String containing %VAT
         */
        InvalidVAT(const std::string &vat);

        /**
         * @brief Get %VAT from which the exception was constructed.
         * @return %VAT as string
         */
        std::string get_vat() const;
    };
};

#endif //ADDRESS_H_INCLUDED
