#include "service.h"

#include "utils.h"

int Service::next_id_ = 0;

Service::Service(const Client::Username &client_user, const Person &contact1, const Person &contact2,
                 Time t_begin, Time t_end,
                 Address a_begin, Address a_end,
                 Cargo *cargo):
                 id_(utils::itos(next_id_++)),
                 client_user_(client_user), contact1_(contact1), contact2_(contact2),
                 t_begin_(t_begin), t_end_(t_end),
                 a_begin_(a_begin), a_end_(a_end),
                 cargo_(cargo){}

const Currency& Service::get_expenses() const{
    return Currency(0);
}
const Currency& Service::get_price   () const{
    return Currency(0);
}

std::istream& operator>>(std::istream &is,       Service &s){
    is >> s.id_
       >> s.client_user_
       >> s.contact1_
       >> s.contact2_
       >> s.t_begin_
       >> s.t_end_
       >> s.a_begin_
       >> s.a_end_; std::cout << "service.cpp,L25\n";
    input_Cargo(is, s.cargo_); std::cout << "service.cpp,L26\n";
    size_t sz; is >> sz;
    s.trucks_ .resize(sz); for(Truck::NumberPlate &n:s.trucks_ ) is >> n;
    s.drivers_.resize(sz); for(User ::Username    &u:s.drivers_) is >> u;
    return is;
}
std::ostream& operator<<(std::ostream &os, const Service &s){
    os << s.id_           << "\n"
       << s.client_user_  << "\n"
       << s.contact1_     << "\n"
       << s.contact2_     << "\n"
       << s.t_begin_      << "\n"
       << s.t_end_        << "\n"
       << s.a_begin_      << "\n"
       << s.a_end_;
    return os;
}
