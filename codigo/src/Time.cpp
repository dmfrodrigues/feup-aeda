#include "../include/Time.h"

#include <sstream>
#include <iomanip>
#include <regex>
#include <chrono>
#include "../include/utils.h"

const std::string Time::DEFAULT_FORMAT = "%Y%m%d_%H%M%S";
const std::string Time::DEFAULT_TIME_REGEX = "^(\\d{4})/(\\d{2})/(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2})$";
const std::string Time::DEFAULT_DATE_REGEX = "^(\\d{4})/(\\d{2})/(\\d{2})$";
const std::string Time::DEFAULT_TIME   = "00010101_000000";

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

Time Time::get_current_date(void) {
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();


    std::time_t time_now = std::chrono::system_clock::to_time_t(now);

    std::tm *tm_p = std::localtime(&time_now);

    if (tm_p == NULL) throw std::runtime_error("Failed to get current time.");

    std::string tm_formatted = utils::itos(tm_p->tm_year + 1900) + utils::itos(tm_p->tm_mon + 1) + utils::itos(tm_p->tm_mday) + "_000000";

    return Time(tm_formatted);
}

int Time::get_year(void) const { return t_.tm_year + 1900; }

void Time::set_year(int year) {
    t_.tm_year = year - 1900;
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
void Time::input_date(const std::string &date) {
    static std::regex hour_regex(DEFAULT_DATE_REGEX);
    std::smatch matches;

    if (std::regex_match(date, matches, hour_regex)) {

        std::string tm_formatted = matches[1].str() + matches[2].str() + matches[3].str() + "_000000";

        Time new_time = Time(tm_formatted);
        this->t_ = new_time.t_;
    } else {
        throw Time::InvalidTimeFormat(date);
    }
}

int num_month[] = {0,3,2,5,0,3,5,1,4,6,2,4};
Time::DayOfWeek Time::get_dayofweek() const{
    int y = 1900+t_.tm_year;
    int m = t_.tm_mon + 1;
    int d = t_.tm_mday;
    y -= (m < 3);
    int ret = (y+y/4-y/100+y/400+num_month[m-1]+d+6)%7;
    return static_cast<Time::DayOfWeek>(ret);
}

bool Time::operator==(const Time &t) const{ return (format() == t.format()); }
bool Time::operator!=(const Time &t) const{ return !(*this == t); }
bool Time::operator< (const Time &t) const{ return (format() < t.format()); }
bool Time::operator> (const Time &t) const{ return (t < *this); }
bool Time::operator<=(const Time &t) const{ return !(*this > t); }
bool Time::operator>=(const Time &t) const{ return !(*this < t); }

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
