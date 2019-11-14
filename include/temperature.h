/**
 * @file temperature.h
 */

#ifndef TEMPERATURE_H_INCLUDED
#define TEMPERATURE_H_INCLUDED

#include <iostream>

/** Store temperature in degrees Celsius, providing validation for
 *  absolute zero (-273.15) and boiling temperature (+100).
 */
class Temperature{
private:
    double temp_;
public:
    Temperature();
    explicit Temperature(double temp);

    double      operator+(const Temperature &t) const;
    double      operator-(const Temperature &t) const;

    bool operator==(const Temperature &t)const;
    bool operator< (const Temperature &t)const;
    bool operator> (const Temperature &t)const;
    bool operator>=(const Temperature &t)const;
    bool operator<=(const Temperature &t)const;

    explicit operator double() const{ return temp_; }

    friend std::istream& operator>>(std::istream &is,       Temperature &t);
    friend std::ostream& operator<<(std::ostream &os, const Temperature &t);

    /**
     * @brief Exception for reporting invalid temperature.
     */
    class InvalidTemperature: public std::invalid_argument{
    private:
        double temp_;
    public:
        InvalidTemperature(const double &temp);
        const double& get_temperature()const;
    };
};

/**
 * @brief Store temperature range as a min/max pair, providing validation for min<max.
 */
class TemperatureRange{
public:
    Temperature min, max;

    TemperatureRange();
    TemperatureRange(const Temperature &tmin, const Temperature &tmax);

    friend std::istream& operator>>(std::istream &is,       TemperatureRange &r);
    friend std::ostream& operator<<(std::ostream &os, const TemperatureRange &r);

    /**
     * @brief Exception for reporting invalid temperature range.
     */
    class InvalidTemperatureRange: public std::invalid_argument{
    private:
        Temperature min, max;
    public:
        InvalidTemperatureRange(const Temperature &tmin, const Temperature &tmax);
        std::pair<Temperature,Temperature> get_temperature_range() const;
    };
};

#endif //TEMPERATURE_H_INCLUDED
