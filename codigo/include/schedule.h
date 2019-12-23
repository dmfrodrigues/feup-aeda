#ifndef SCHEDULE_H_INCLUDED
#define SCHEDULE_H_INCLUDED

#include "service.h"
#include <set>

class Schedule{
private:
    static bool cmp(const Service *s1, const Service *s2);
    std::set<const Service *, bool(*)(const Service*, const Service*)> st;
    bool valid;
public:
    Schedule();
    bool is_available(const Service *s) const;
    void add_service (const Service *s);
    operator bool() const;
    std::ostream& print_week(std::ostream &os, const Time &t) const;
};

#endif //SCHEDULE_H_INCLUDED
