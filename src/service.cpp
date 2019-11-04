#include "../include/service.h"

Service::Service(const Client::UserName &client_user, const Person &contact1, const Person &contact2,
                 const std::string &cargo_type, double cargo_amount, int cargo_danger,
                 Time t_begin, Time t_end,
                 Address a_begin, Address a_end,
                 Cargo *cargo):
                 client_user_(client_user), contact1_(contact1), contact2_(contact2),
                 cargo_type_(cargo_type), cargo_amount_(cargo_amount), cargo_danger_(cargo_danger),
                 t_begin_(t_begin), t_end_(t_end),
                 a_begin_(a_begin), a_end_(a_end),
                 cargo_(cargo){}

std::istream& operator>>(std::istream &is,       Service &s){
    is >> s.client_user_
       >> s.contact1_
       >> s.contact2_
       >> s.cargo_type_
       >> s.cargo_amount_
       >> s.cargo_danger_
       >> s.t_begin_
       >> s.t_end_
       >> s.a_begin_
       >> s.a_end_;
    return is;
}
std::ostream& operator<<(std::ostream &os, const Service &s){
    os << s.client_user_ << "\n"
       << s.contact1_ << "\n"
       << s.contact2_ << "\n"
       << s.cargo_type_ << "\n"
       << s.cargo_amount_ << "\n"
       << s.cargo_danger_ << "\n"
       << s.t_begin_      << "\n"
       << s.t_end_        << "\n"
       << s.a_begin_      << "\n"
       << s.a_end_;
    return os;
}
