#ifndef VAT_H_INCLUDED
#define VAT_H_INCLUDED

/**
 * @brief %VAT number.
 */
class VAT{
private:
    static const std::regex  regex_;
    std::string vat_;
public:
    /**
     * @brief   Regular expression string that describes a valid VAT.
     */
    static const std::string REGEX_STR;
    /**
     * @brief   Constructor accepting %VAT as string
     * @param   vat String containing %VAT
     * @exception   VAT::VATTooLong When VAT is longer than the maximum size
     */
    VAT(const std::string &vat);

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

    /**
     * @brief       Overload of <em> operator>> </em>. Reads an entire line and expects it to be a VAT.
     */
    friend std::istream& operator>>(std::istream &is,       VAT &v);
    /**
     * @brief       Overload of <em> operator<< </em>.
     */
    friend std::ostream& operator<<(std::ostream &os, const VAT &v);
};

const std::string VAT::REGEX_STR = "^[A-Z0-9]{2,15}$";

#endif //ADDRESS_H_INCLUDED
