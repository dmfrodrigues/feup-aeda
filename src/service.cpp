#include "service.h"

Service::Service(const Client *client, const Person *person_to_contact,
                 string cargo_type, double cargo_ammount, int cargo_danger,
                 Time t_begin, Time t_end,
                 Address a_begin, Address a_end):
                 client_(client), person_to_contact_(person_to_contact),
                 cargo_type_(cargo_type), cargo_ammount_(cargo_ammount), cargo_danger_(cargo_danger),
                 t_begin_(t_begin), t_end_(t_end),
                 a_begin_(a_begin), a_end_(a_end){}
