#ifndef VAT_H_INCLUDED
#define VAT_H_INCLUDED

using namespace std;

class VAT{
private:
    string vat_;
public:
    VAT(string vat);
    class VATTooLong: public invalid_argument{
    private:
        string vat_;
    public:
        VATTooLong(string vat);
        string get_vat() const;
    };
};

#endif //ADDRESS_H_INCLUDED
