#ifndef VAT_H_INCLUDED
#define VAT_H_INCLUDED

class VAT{
private:
    std::string vat_;
public:
    VAT(const std::string &vat);
    class VATTooLong: public std::invalid_argument{
    private:
        std::string vat_;
    public:
        VATTooLong(const std::string &vat);
        std::string get_vat() const;
    };
};

#endif //ADDRESS_H_INCLUDED
