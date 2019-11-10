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
    float temp_;
public:
    Temperature();
    explicit Temperature(float temp);
    Temperature operator+(const Temperature &t) const;
    Temperature operator-(const Temperature &t) const;
    bool operator< (const Temperature &t)const;
    bool operator> (const Temperature &t)const;
    bool operator==(const Temperature &t)const;
    bool operator>=(const Temperature &t)const;
    bool operator<=(const Temperature &t)const;

    friend std::istream& operator>>(std::istream &is,       Temperature &t);
    friend std::ostream& operator<<(std::ostream &os, const Temperature &t);

    /**
     * @brief Exception for reporting invalid temperature.
     */
    class InvalidTemperature: public std::invalid_argument{
    private:
        float temp_;
    public:
        InvalidTemperature(const float &temp);
        const float& get_temperature()const;
    };
};

/**
 * @brief Store temperature range as a min/max pair, providing validation for min<max.
 */
class TemperatureRange{
private:
    std::pair<Temperature,Temperature> range_;
public:
    TemperatureRange(){}
    TemperatureRange(const Temperature &tmin, const Temperature &tmax);

    friend std::istream& operator>>(std::istream &is,       TemperatureRange &r);
    friend std::ostream& operator<<(std::ostream &os, const TemperatureRange &r);

    /**
     * @brief Exception for reporting invalid temperature range.
     */
    class InvalidTemperatureRange: public std::invalid_argument{
    private:
        std::pair<Temperature,Temperature> range_;
    public:
        InvalidTemperatureRange(const Temperature &tmin, const Temperature &tmax);
        const std::pair<Temperature,Temperature>& get_temperature_range() const;
    };
};

#endif //TEMPERATURE_H_INCLUDED
