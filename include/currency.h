/**
 * @file currency.h
 */

#ifndef CURRENCY_H_INCLUDED
#define CURRENCY_H_INCLUDED

#include <iostream>

/**
 * @brief Class for storing amounts of a given currency.
 *
 * Internally uses integers so the representation of the amount of currency is exact.
 */
class Currency{
private:
    long long int cents_;
public:
    /**
     * @brief           Construct from amount of currency as a \a double.
     * @param   amount  Amount of currency
     */
    explicit Currency(double amount = 0.0L);

    /**
     * @brief       Overload of <em> operator== </em>.
     * @param   c   Right-hand side of the comparison
     * @return      Truth value of the comparison
     */
    bool operator==(const Currency &c) const;
    bool operator< (const Currency &c) const;

    explicit operator double() const;
    Currency& operator=(const double &n);
    Currency& operator+=(const Currency &c);

    /**
     * @brief   Overload of <em> operator>> </em>.
     */
    friend std::istream& operator>>(std::istream &is,       Currency &c);

    /**
     * @brief   Overload of <em> operator<< </em>.
     */
    friend std::ostream& operator<<(std::ostream &os, const Currency &c);

    /**
     * @brief Gets the amount of money
     * @return The amount of cents
     */
    long long int getCents(void) const;

};

#endif //CURRENCY_H_INCLUDED
