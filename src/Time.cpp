#include "Time.h"

Time::Time(const std::string &s){
    std::stringstream ss(s);
    ss >> std::get_time(&t_, "%Y%m%d_%H%M%S");
}

std::ostream& operator<<(std::ostream &os, const Time &t){
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(4) << t.t_.tm_year+1900 << std::setw(2) << t.t_.tm_mon+1 << std::setw(2) << t.t_.tm_mday << "_"
                            << std::setw(2) << t.t_.tm_hour      << std::setw(2) << t.t_.tm_min   << std::setw(2) << t.t_.tm_sec;
    std::string s; ss >> s;
    return (os << s);
}
