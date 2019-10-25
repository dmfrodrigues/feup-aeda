#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

using namespace std;

class Time {
private:
    tm t_;
public:
    Time(string s);
    friend ostream& operator<<(ostream &os, const Time &t);
};

#endif //TIME_H_INCLUDED
