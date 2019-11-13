#include "Time.h"

#include <sstream>
#include <iomanip>
#include <regex>
#include <chrono>
#include "utils.h"

Time::Time(const std::string &s){
    std::stringstream ss(s);
    ss >> std::get_time(&t_, Time::DEFAULT_FORMAT.c_str());

    if (t_.tm_sec   >= 60 ||
        t_.tm_min   >= 60 ||
        t_.tm_hour  >= 24 ||
        t_.tm_mday  <= 0  ||
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

void Time::input_time(const std::string &time) {
    static std::regex time_regex(DEFAULT_TIME_REGEX);
    std::smatch matches;

    if (std::regex_match(time, matches, time_regex)) {
        std::string tm_formatted = matches[1].str() + matches[2].str() + matches[3].str() +
                                    "_" + matches[4].str() + matches[5].str() + matches[6].str();

        Time new_time = Time(tm_formatted);
        this->t_ = new_time.t_;
    } else {
        throw Time::InvalidTimeFormat(time);
    }
}

void Time::input_hour(const std::string &hour) {
    static std::regex hour_regex(DEFAULT_HOUR_REGEX);
    std::smatch matches;

    if (std::regex_match(hour, matches, hour_regex)) {
        std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

        std::time_t time_now = std::chrono::system_clock::to_time_t(now);

        std::tm *tm_p = std::localtime(&time_now);

        if (tm_p == NULL) throw std::runtime_error("Failed to get current time.");

        std::string tm_formatted = utils::itos(tm_p->tm_year + 1900) + utils::itos(tm_p->tm_mon + 1) + utils::itos(tm_p->tm_mday) +
                                    "_" + matches[1].str() + matches[2].str() + matches[3].str();

        Time new_time = Time(tm_formatted);
        this->t_ = new_time.t_;
    } else {
        throw Time::InvalidTimeFormat(hour);
    }
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
const std::string Time::DEFAULT_TIME_REGEX = "^(\\d{4})/(\\d{2})/(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2})$";
const std::string Time::DEFAULT_HOUR_REGEX = "^(\\d{2}):(\\d{2}):(\\d{2})$";
const std::string Time::DEFAULT_TIME   = "00010101_000000";
