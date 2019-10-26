#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

class Time {
private:
    std::tm t_;
public:
    Time(const std::string &s);
    friend std::ostream& operator<<(std::ostream &os, const Time &t);
    friend std::istream& operator>>(std::istream &is,       Time &t);
};

#endif //TIME_H_INCLUDED
