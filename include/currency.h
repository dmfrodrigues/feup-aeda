#ifndef CURRENCY_H_INCLUDED
#define CURRENCY_H_INCLUDED

class Currency{
private:
    long long int cents_;
public:
    Currency();
    explicit Currency(double ammount);

    bool operator==(const Currency &c) const;

    friend std::ostream& operator<<(std::ostream &os, const Currency &c);
    friend std::istream& operator>>(std::istream &is,       Currency &c);
};

#endif //CURRENCY_H_INCLUDED
