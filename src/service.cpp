#include "service.h"

#include "utils.h"

int Service::next_id_ = 0;

Service::Service(const Client::Username &client_user, const Person &contact1, const Person &contact2,
                 Time t_begin, Time t_end,
                 Address a_begin, Address a_end,
                 Cargo *cargo,
                 Currency expenses, Currency price):
                 id_(utils::itos(next_id_++)),
                 client_user_(client_user), contact1_(contact1), contact2_(contact2),
                 t_begin_(t_begin), t_end_(t_end),
                 a_begin_(a_begin), a_end_(a_end),
                 cargo_(cargo),
                 expenses_(expenses), price_(price){}

Currency Service::get_expenses() const{
    return expenses_;
}
Currency Service::get_price   () const{
    return price_;
}

bool Service::allocate(std::vector<const Truck*> tv, std::vector<const Driver*> dv){
    utils::mergesort(tv, [](const Truck *p1, const Truck *p2){
        return (p1->get_cargo()->get_weight() > p2->get_cargo()->get_weight());
    });
    size_t sz = std::min(tv.size(), dv.size());

    return false;
}

std::istream& operator>>(std::istream &is,       Service &s){
    is >> s.id_
       >> s.client_user_
       >> s.contact1_
       >> s.contact2_
       >> s.t_begin_
       >> s.t_end_
       >> s.a_begin_
       >> s.a_end_;
    input_Cargo(is, s.cargo_);
    size_t sz; is >> sz;
    s.trucks_ .resize(sz); s.drivers_.resize(sz);
    for(size_t i = 0; i < sz; ++i) is >> s.trucks_[i] >> s.drivers_[i];
    is >> s.expenses_
       >> s.price_;
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
       << s.a_end_        << "\n";
    output_Cargo(os, s.cargo_); os << "\n";
    size_t sz = s.trucks_.size();
    os << sz << "\n";
    for(size_t i = 0; i < sz; ++i) os << s.trucks_[i] << " " << s.drivers_[i] << "\n";
    os << s.expenses_ << "\n"
       << s.price_;
    return os;
}
