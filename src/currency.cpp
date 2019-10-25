#include "currency.h"

Currency::Currency(double ammount):cents_(100.0L*ammount+(ammount > 0.0L ? 0.5L : -0.5L)){}

ostream& operator<<(ostream &os, const Currency &c){
    string s;
    stringstream ss;
    ss << c.cents_/100 << "." << setw(2) << setfill('0') << c.cents_%100;
    ss >> s;
    return (os << s);
}
