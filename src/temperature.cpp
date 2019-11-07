#include "temperature.h"

Temperature::Temperature(float temp):temp_(temp){}
Temperature Temperature::operator+(const Temperature &t) const{ return Temperature(temp_+t.temp_); }
Temperature Temperature::operator-(const Temperature &t) const{ return Temperature(temp_-t.temp_); }
bool Temperature::operator< (const Temperature &t)const{ return (temp_ < t.temp_); }
bool Temperature::operator> (const Temperature &t)const{ return (t < *this); }
bool Temperature::operator==(const Temperature &t)const{ return !(*this < t || t < *this); }
bool Temperature::operator>=(const Temperature &t)const{ return !(*this < t); }
bool Temperature::operator<=(const Temperature &t)const{ return !(*this > t); }

std::istream& operator>>(std::istream &is,       Temperature &t){ return (is >> t.temp_); }
std::ostream& operator<<(std::ostream &os, const Temperature &t){ return (os << t.temp_); }

TemperatureRange::TemperatureRange(const Temperature &tmin, const Temperature &tmax){
    if(tmin > tmax)
        throw TemperatureRange::InvalidTemperatureRange(tmin, tmax);
    range_ = std::pair<Temperature,Temperature>(tmin, tmax);
}


std::istream& operator>>(std::istream &is,       TemperatureRange &r){ return (is >> r.range_.first        >> r.range_.second); }
std::ostream& operator<<(std::ostream &os, const TemperatureRange &r){ return (os << r.range_.first << " " << r.range_.second); }

TemperatureRange::InvalidTemperatureRange::InvalidTemperatureRange(const Temperature &tmin, const Temperature &tmax):
    std::invalid_argument("Invalid temperature range"),
    range_(tmin, tmax){}
const std::pair<Temperature,Temperature>& TemperatureRange::InvalidTemperatureRange::get_temperature_range() const{ return range_; }
