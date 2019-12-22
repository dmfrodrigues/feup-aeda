#ifndef SCHEDULE_H_INCLUDED
#define SCHEDULE_H_INCLUDED

#include "service.h"
#include <set>

class Schedule{
private:
    static bool cmp(const Service *s1, const Service *s2);
    std::set<const Service *, bool(*)(const Service*, const Service*)> st;
public:
    Schedule();
    bool is_available(const Service *s) const;
    bool add_service (const Service *s);
};

#endif //SCHEDULE_H_INCLUDED
