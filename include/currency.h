#ifndef CURRENCY_H_INCLUDED
#define CURRENCY_H_INCLUDED

using namespace std;

class Currency{
private:
    long long int cents_;
public:
    explicit Currency(double ammount);
    friend ostream& operator<<(ostream &os, const Currency &c);
};

#endif //CURRENCY_H_INCLUDED
