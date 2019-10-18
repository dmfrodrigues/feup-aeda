#ifndef SERVICE_H_INCLUDED
#define SERVICE_H_INCLUDED

#include "address.h"
#include "vat.h"
#include "phonenumber.h"

class Service{
private:
    class Event;
    std::vector<Event*> events_;
public:
    Service();
};

class Service::Event{
private:
    std::chrono::time_point t_begin_est_;
    std::chrono::time_point t_end_est_;
    std::chrono::time_point t_begin_real_;
    std::chrono::time_point t_end_real_;
    Address a_begin_;
    Address a_end_;
    bool done_ = false;
    enum Type{
        Load,
        Unload,
        Wait
    }
    Type type_;
public:
    Service::Event::Type get_type() const;
};

#endif //SERVICE_H_INCLUDED
