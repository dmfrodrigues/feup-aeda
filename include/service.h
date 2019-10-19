#ifndef SERVICE_H_INCLUDED
#define SERVICE_H_INCLUDED

#include "person.h"
#include "Time.h"

class Service{
private:
    const Client *client_;
    const Person *person_to_contact_;
    std::string cargo_type_;
    double cargo_ammount_;
    int cargo_danger_;
    Time t_begin_;
    Time t_end_;
    Address a_begin_;
    Address a_end_;
    //std::vector<Truck*> trucks_;
public:
    Service(const Client *client, const Person *person_to_contact,
            const std::string &cargo_type, double cargo_ammount, int cargo_danger,
            const Time &t_begin, const Time &t_end,
            const Address &a_begin, const Address &a_end);
};

#endif //SERVICE_H_INCLUDED
