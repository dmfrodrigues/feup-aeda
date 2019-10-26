#ifndef VAT_H_INCLUDED
#define VAT_H_INCLUDED

/**
 * @brief %VAT number.
 */
class VAT{
private:
    std::string vat_;
public:
    /**
     * @brief   Constructor accepting %VAT as string
     * @param   vat String containing %VAT
     * @exception   VAT::VATTooLong When VAT is longer than the maximum size
     */
    VAT(const std::string &vat);

    /**
     * @brief   Exception class for when the provided %VAT string is too long.
     */
    class VATTooLong: public std::invalid_argument{
    private:
        std::string vat_;
    public:
        /**
         * @brief Constructor accepting %VAT string that caused the exception.
         *
         * Also sets the string returned by <em> std::exception::what() </em>.
         * @param   vat String containing %VAT
         */
        VATTooLong(const std::string &vat);

        /**
         * @brief Get %VAT from which the exception was constructed.
         * @return %VAT as string
         */
        std::string get_vat() const;
    };
};

#endif //ADDRESS_H_INCLUDED
