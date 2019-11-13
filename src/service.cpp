#include "service.h"

#include "utils.h"

int Service::next_id_ = 0;

Service::Service(const Client::Username &client_user):
    id_(utils::itos(next_id_++)), client_user_(client_user), cost_(0), revenue_(0){}

Service::~Service() { if(cargo_ != NULL) delete cargo_; }

bool Service::allocate(std::vector<const Truck*> tv, std::vector<const Driver*> dv){
    utils::mergesort(tv, [](const Truck *p1, const Truck *p2){
        return (p1->get_cargo()->get_W() > p2->get_cargo()->get_W());
    });
    size_t sz = std::min(tv.size(), dv.size());
    Weight done(0.0);
    size_t i = 0;
    while(i < sz && done < cargo_->get_W() && !utils::feq(double(done), double(cargo_->get_W()), 1.0)){
        trucks_.push_back(tv[i]->get_numberplate());
        drivers_.push_back(dv[i]->get_username());
        done += tv[i]->get_cargo()->get_W();
    }
    if(done < cargo_->get_W() && !utils::feq(double(done), double(cargo_->get_W()), 1.0)){
        trucks_.clear();
        drivers_.clear();
        return false;
    }else{
        cost_ = 0.0;
        Weight W(0.0);
        Weight dW;
        for(const Truck *t:tv){
            dW = std::min(t->get_cargo()->get_W(),
                          cargo_->get_W() - W);
            if(t->get_cargo()->get_type() == Cargo::Type::Refrigerated){
                const CargoTransRefrigerated *p = dynamic_cast<const CargoTransRefrigerated*>(t->get_cargo());
                const CargoRefrigerated      *q = dynamic_cast<const CargoRefrigerated     *>(cargo_);
                cost_    += p->get_E(distance_, dW, q->get_Tr());
                revenue_ += p->get_P(distance_, dW, q->get_Tr());
            }else{
                cost_    += t->get_cargo()->get_E(distance_, dW);
                revenue_ += t->get_cargo()->get_P(distance_, dW);
            }
            W += dW;
        }
        return true;
    }
}

std::istream& operator>>(std::istream &is,       Service &s){
    is >> s.id_
       >> s.client_user_
       >> s.contact1_
       >> s.contact2_
       >> s.t_begin_
       >> s.t_end_
       >> s.a_begin_
       >> s.a_end_
       >> s.distance_;
    input_Cargo(is, s.cargo_);
    size_t sz; is >> sz;
    s.trucks_ .resize(sz); s.drivers_.resize(sz);
    for(size_t i = 0; i < sz; ++i) is >> s.trucks_[i] >> s.drivers_[i];
    is >> s.cost_
       >> s.revenue_;
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
       << s.a_end_        << "\n"
       << s.distance_     << "\n";
    output_Cargo(os, s.cargo_); os << "\n";
    size_t sz = s.trucks_.size();
    os << sz << "\n";
    for(size_t i = 0; i < sz; ++i) os << s.trucks_[i] << " " << s.drivers_[i] << "\n";
    os << s.cost_ << "\n"
       << s.revenue_;
    return os;
}

bool Service::in(std::istream &is, std::ostream &os) {
    os << "Person to contact on pick-up of merchandise:\n";
    if (!contact1_.in(is, os)) return false;
    os << "Address to pick-up merchandise:\n";
    if (!a_begin_.in(is, os)) return false;

    os << "Person to contact on delivery of merchandise:\n";
    if (!contact2_.in(is, os)) return false;
    os << "Address to delivery merchandise:\n";
    if (!a_end_.in(is, os)) return false;

    while (true) {
        if (!utils::input("Time to start the service: ", t_begin_, is, os)||
            !utils::input("Time to end service: ", t_end_, is, os)) return false;

        if (t_begin_ <= t_end_) break;
        std::cout << "Error: Initial time must be before end time\n";
    }

    if (!utils::input("Distance: ", distance_, is, os)) return false;

    std::string type;
    while (true) {
        if (!utils::input("Types available: Normal, Animal, Refrigerated, Dangerous.\nCargo Type: ", type, is, os)) return false;

        utils::to_lower(type);
        if (type == "normal") {
            Cargo *cargo = new Cargo();
            if (!cargo->in(is, os)) { delete cargo; return false; }
            cargo_ = cargo;
            break;
        } else if (type == "animal") {
            CargoAnimal *cargo = new CargoAnimal();
            if (!cargo->in(is, os)) { delete cargo; return false; }
            cargo_ = cargo;
            break;
        } else if (type == "refrigerated") {
            CargoRefrigerated *cargo = new CargoRefrigerated();
            if (!cargo->in(is, os)) { delete cargo; return false; }
            cargo_ = cargo;
            break;
        } else if (type == "dangerous") {
            CargoDangerous *cargo = new CargoDangerous();
            if (!cargo->in(is, os)) { delete cargo; return false; }
            cargo_ = cargo;
            break;
        } else {
            std::cout << "Error: Invalid cargo type.\n";
            continue;
        }
    }
    return true;
}
