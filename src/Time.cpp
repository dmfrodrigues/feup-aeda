#include "Time.h"

#include <sstream>
#include <iomanip>
#include "utils.h"

Time::Time(const std::string &s){
    std::stringstream ss(s);
    ss >> std::get_time(&t_, Time::DEFAULT_FORMAT.c_str());

    if (t_.tm_sec   >= 60 ||
        t_.tm_min   <= 0  ||
        t_.tm_min   >= 60 ||
        t_.tm_hour  >= 24 ||
        t_.tm_mday  >  31 ||
        t_.tm_mon   >= 12)
        throw InvalidTime(s);
}

std::string Time::format(const std::string &fmt) const{
    char buff[100];
    if(std::strftime(buff, sizeof(buff), fmt.c_str(), &t_)==0)
        throw InvalidTimeFormat(fmt);
    return std::string(buff);
}

bool Time::operator< (const Time &t) const{ return (format() < t.format()); }

std::istream& operator>>(std::istream &is,       Time &t){
    std::string s;
    try{
        is >> s; t = Time(utils::urldecode(s));
    }catch(...){
        is.setstate(std::ios::failbit);
    }
    return is;
}

std::ostream& operator<<(std::ostream &os, const Time &t){
    return (os << utils::urlencode(t.format()));
}

Time::InvalidTime::InvalidTime(const std::string &date):
    std::invalid_argument("Invalid date: "+date),
    date_(date){}

const std::string& Time::InvalidTime::get_date() const { return date_; }

Time::InvalidTimeFormat::InvalidTimeFormat(const std::string &fmt):
    std::invalid_argument("Invalid time format ("+fmt+")"),
    fmt_(fmt){}
const std::string& Time::InvalidTimeFormat::get_format() const{ return fmt_; }

const std::string Time::DEFAULT_FORMAT = "%Y%m%d_%H%M%S";
const std::string Time::DEFAULT_TIME   = "00000000_000000";
