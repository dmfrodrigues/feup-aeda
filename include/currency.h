#ifndef CURRENCY_H_INCLUDED
#define CURRENCY_H_INCLUDED

class Currency{
private:
    long long int cents_;
public:
    explicit Currency(double ammount);
    friend std::ostream& operator<<(std::ostream &os, const Currency &c);
};

#endif //CURRENCY_H_INCLUDED
