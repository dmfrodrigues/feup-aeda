#ifndef WEIGHT_H_INCLUDED
#define WEIGHT_H_INCLUDED

#include <iostream>

class Weight{
private:
    float w_;
public:
    Weight():w_(0){}
    Weight(float w);

    friend std::istream& operator>>(std::istream &is,       Weight &w);
    friend std::ostream& operator<<(std::ostream &os, const Weight &w);

    class InvalidWeight: public std::invalid_argument{
    private:
        float w_;
    public:
        InvalidWeight(float w);
        float get_weight() const;
    };
};

#endif //WEIGHT_H_INCLUDED
