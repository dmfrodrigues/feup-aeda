#include "service.h"

Service::Service(const Client *client, const Person &contact1, const Person &contact2,
                 const std::string &cargo_type, double cargo_amount, int cargo_danger,
                 Time t_begin, Time t_end,
                 Address a_begin, Address a_end):
                 client_(client), contact1_(contact1), contact2_(contact2),
                 cargo_type_(cargo_type), cargo_amount_(cargo_amount), cargo_danger_(cargo_danger),
                 t_begin_(t_begin), t_end_(t_end),
                 a_begin_(a_begin), a_end_(a_end){}
