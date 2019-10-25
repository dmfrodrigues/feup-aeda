#include "currency.h"

Currency::Currency(double ammount):cents_(100.0L*ammount+(ammount > 0.0L ? 0.5L : -0.5L)){}

std::ostream& operator<<(std::ostream &os, const Currency &c){
    std::stringstream ss;
    ss << c.cents_/100 << "." << std::setw(2) << std::setfill('0') << c.cents_%100;
    return (os << ss.str());
}
