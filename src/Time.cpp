#include "Time.h"

Time::Time(string s){
    stringstream ss(s);
    ss >> get_time(&t_, "%Y%m%d_%H%M%S");
}

ostream& operator<<(ostream &os, const Time &t){
    stringstream ss;
    ss << setfill('0') << setw(4) << t.t_.tm_year+1900 << setw(2) << t.t_.tm_mon+1 << setw(2) << t.t_.tm_mday << "_"
                            << setw(2) << t.t_.tm_hour      << setw(2) << t.t_.tm_min   << setw(2) << t.t_.tm_sec;
    string s; ss >> s;
    return (os << s);
}
