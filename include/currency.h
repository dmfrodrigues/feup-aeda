#ifndef CURRENCY_H_INCLUDED
#define CURRENCY_H_INCLUDED

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

    /**
     * @brief       Overload of <em> operator>> </em>.
     * @param   is  Input stream to read from.
     * @param   c   Currency to write read information to.
     * @return      The same as \a is.
     */
    friend std::istream& operator>>(std::istream &is,       Currency &c);

    /**
     * @brief       Overload of <em> operator<< </em>.
     * @param   os  Output stream to write to.
     * @param   c   Currency to read information from.
     * @return      The same as \a os.
     */
    friend std::ostream& operator<<(std::ostream &os, const Currency &c);

};

#endif //CURRENCY_H_INCLUDED
