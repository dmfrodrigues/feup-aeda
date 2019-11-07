#include "weight.h"

Weight::Weight(float w){
    if(w < 0.0)
        throw Weight::InvalidWeight(w);
    w_ = w;
}

std::istream& operator>>(std::istream &is,       Weight &w){ return (is >> w.w_); }
std::ostream& operator<<(std::ostream &os, const Weight &w){ return (os << w.w_); }

Weight::InvalidWeight::InvalidWeight(float w):
    std::invalid_argument("Invalid weight"),
    w_(w){}
float Weight::InvalidWeight::get_weight()const{ return w_; }
