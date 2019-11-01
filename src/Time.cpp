#include "Time.h"

Time::Time(const std::string &s){
    std::stringstream ss(s);
    ss >> std::get_time(&t_, Time::DEFAULT_FORMAT.c_str());
}

std::string Time::format(const std::string &fmt) const{
    char buff[100];
    if(std::strftime(buff, sizeof(buff), fmt.c_str(), &t_)==0)
        throw InvalidTimeFormat(fmt);
    return std::string(buff);
}

std::istream& operator>>(std::istream &is,       Time &t){
    std::string s;
    std::getline(is, s);
    try{
        t = Time(s);
    }catch(...){
        is.setstate(std::ios::failbit);
    }
    return is;
}

std::ostream& operator<<(std::ostream &os, const Time &t){
    return (os << t.format());
}

Time::InvalidTimeFormat::InvalidTimeFormat(const std::string &fmt):
    std::invalid_argument("Invalid time format ("+fmt+")"),
    fmt_(fmt){}
const std::string& Time::InvalidTimeFormat::get_format() const{ return fmt_; }
