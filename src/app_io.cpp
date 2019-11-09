#include "app.h"

template<class Base, class Deriv, class ID>
size_t App::load_ptr(std::ifstream &is, std::vector<Base*> &m_in){
    is.exceptions(std::ifstream::eofbit | std::ifstream::badbit | std::ifstream::failbit);
    size_t N; is >> N;
    for(size_t i = 0; i < N; ++i){
        Base *m = new Deriv(); is >> *dynamic_cast<Deriv*>(m);
        if(utils::linearfind(m_in.begin(), m_in.end(), m->get_id(),
          [](const Base* p, const ID &s){ return (p->get_id() == s); }) != m_in.end()){
            auto id = m->get_id();
            delete m;
            throw App::RepeatedId((std::string)id);
        }
        m_in.push_back(m);
    }
    return N;
}

template<class Base, class Deriv>
size_t App::save_ptr(std::ofstream &os, const std::vector<Base*> &m_out){
    os.exceptions(std::ifstream::eofbit | std::ifstream::badbit | std::ifstream::failbit);
    os << m_out.size() << "\n";
    for(const Base* p:m_out){
        os << *dynamic_cast<const Deriv*>(p) << "\n";
    }
    os << std::flush;
    return m_out.size();
}

void App::load_all(){
    for(const User *p:users_) delete p;
    users_ = std::vector<User*>();
    {
        std::cout << "Loading managers..." << std::flush;
        std::ifstream is(managers_path_);
        size_t sz = load_ptr<User,Manager,User::Username>(is, users_ );
        std::cout << " loaded " << sz << std::endl;
    }
    {
        std::cout << "Loading drivers ..." << std::flush;
        std::ifstream is(drivers_path_ );
        size_t sz = load_ptr<User,Driver ,User::Username>(is, users_ );
        std::cout << " loaded " << sz << std::endl;
    }
    {
        std::cout << "Loading clients ..." << std::flush;
        std::ifstream is(clients_path_ );
        size_t sz = load_ptr<User,Client ,User::Username>(is, users_ );
        std::cout << " loaded " << sz << std::endl;
    }
    {
        std::cout << "Loading trucks  ..." << std::flush;
        std::ifstream is(trucks_path_  );
        size_t sz = load_ptr<Truck,Truck ,Truck::NumberPlate>(is, trucks_);
        std::cout << " loaded " << sz << std::endl;
    }
    {
        std::cout << "Loading services..." << std::flush;
        std::ifstream is(services_path_);
        is >> Service::next_id_;
        size_t sz = load_ptr<Service,Service,std::string>(is, services_);
        std::cout << " loaded " << sz << std::endl;
    }
}

void App::save_all(){
    {
        std::cout << "Saving managers...";
        std::ofstream os(managers_path_);
        size_t sz = save_ptr<User,Manager>(os, filter_user_by_type(users_, User::Type::manager));
        std::cout << " saved " << sz << std::endl;
    }
    {
        std::cout << "Saving drivers ...";
        std::ofstream os(drivers_path_ );
        size_t sz = save_ptr<User,Driver >(os, filter_user_by_type(users_, User::Type::driver ));
        std::cout << " saved " << sz << std::endl;
    }
    {
        std::cout << "Saving clients ...";
        std::ofstream os(clients_path_ );
        size_t sz = save_ptr<User,Client >(os, filter_user_by_type(users_, User::Type::client ));
        std::cout << " saved " << sz << std::endl;
    }
    {
        std::cout << "Saving trucks  ...";
        std::ofstream os(trucks_path_  );
        size_t sz = save_ptr<Truck,Truck >(os, trucks_);
        std::cout << " saved " << sz << std::endl;
    }
    {
        std::cout << "Saving services...";
        std::ofstream os(services_path_);
        os << Service::next_id_ << "\n";
        size_t sz = save_ptr<Service,Service>(os, services_);
        std::cout << " saved " << sz << std::endl;
    }
}
