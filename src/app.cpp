#include "app.h"

#include <stdexcept>

void CLEAR(){
    int ev;
    if((ev = CLEAR_MACRO()))
        throw std::system_error(ev, std::system_category());
}

template<class ID, class T>
void App::load(std::ifstream &is, std::map<ID, T> &m_in){
    is.exceptions(std::ifstream::eofbit | std::ifstream::badbit | std::ifstream::failbit);
    size_t N; is >> N;
    m_in = std::map<ID, T>();
    while(N--){
        T m; is >> m;
        if(m_in.find(m.get_id()) != m_in.end())
            throw App::RepeatedId((std::string)m.get_id());
        m_in[m.get_id()] = m;
    }
}
template<class ID, class T>
void App::load_ptr(std::ifstream &is, std::map<ID, T*> &m_in){
    is.exceptions(std::ifstream::eofbit | std::ifstream::badbit | std::ifstream::failbit);
    size_t N; is >> N;
    m_in = std::map<ID, T*>();
    while(N--){
        T *m = new T(); is >> *m;
        if(m_in.find(m->get_id()) != m_in.end()){
            auto id = m->get_id();
            delete m;
            throw App::RepeatedId((std::string)id);
        }
        m_in[m->get_id()] = m;
    }
}

template<class ID, class T>
void App::save(std::ofstream &os, const std::map<ID, T> &m_out){
    os.exceptions(std::ifstream::eofbit | std::ifstream::badbit | std::ifstream::failbit);
    os << m_out.size() << "\n";
    for(const std::pair<ID, T> &p:m_out){
        os << p.second << "\n";
    }
    os << std::flush;
}
template<class ID, class T>
void App::save_ptr(std::ofstream &os, const std::map<ID, T*> &m_out){
    os.exceptions(std::ifstream::eofbit | std::ifstream::badbit | std::ifstream::failbit);
    os << m_out.size() << "\n";
    for(const std::pair<ID, T*> &p:m_out){
        os << *p.second << "\n";
    }
    os << std::flush;
}

void App::load_all(){
    { std::cout << "Loading managers..." << std::flush; std::ifstream is(managers_path_); load    (is, managers_); std::cout << " loaded " << managers_.size() << std::endl; }
    { std::cout << "Loading drivers ..." << std::flush; std::ifstream is(drivers_path_ ); load    (is, drivers_ ); std::cout << " loaded " << drivers_ .size() << std::endl; }
    { std::cout << "Loading clients ..." << std::flush; std::ifstream is(clients_path_ ); load    (is, clients_ ); std::cout << " loaded " << clients_ .size() << std::endl; }
    { std::cout << "Loading trucks  ..." << std::flush; std::ifstream is(trucks_path_  ); load_ptr(is, trucks_  ); std::cout << " loaded " << trucks_  .size() << std::endl; }
    {
        std::cout << "Loading services..." << std::flush;
        std::ifstream is(services_path_);
        is >> Service::next_id_;
        load(is, services_);
        std::cout << " loaded " << services_.size() << std::endl;
    }
}

void App::save_all(){
    { std::cout << "Saving managers..."; std::ofstream os(managers_path_); save    (os, managers_); std::cout << " saved " << managers_.size() << std::endl; }
    { std::cout << "Saving drivers ..."; std::ofstream os(drivers_path_ ); save    (os, drivers_ ); std::cout << " saved " << drivers_ .size() << std::endl; }
    { std::cout << "Saving clients ..."; std::ofstream os(clients_path_ ); save    (os, clients_ ); std::cout << " saved " << clients_ .size() << std::endl; }
    { std::cout << "Saving trucks  ..."; std::ofstream os(trucks_path_  ); save_ptr(os, trucks_  ); std::cout << " saved " << trucks_  .size() << std::endl; }
    {
        std::cout << "Saving services...";
        std::ofstream os(services_path_);
        os << Service::next_id_ << "\n";
        save(os, services_);
        std::cout << " saved " << services_.size() << std::endl;
    }
}

App::App(const std::string &base      ,
         const std::string &managers  , const std::string &drivers ,
         const std::string &clients   ,
         const std::string &trucks    , const std::string &services):
         managers_path_(base+managers), drivers_path_ (base+drivers ),
         clients_path_ (base+clients ),
         trucks_path_  (base+trucks  ), services_path_(base+services){
    std::cout << "Starting app..." << std::endl;
    load_all();
    save_all();
    list_clients();
    std::cout << std::endl;
    list_managers();
}

void App::request_service(){

}

void App::print_list(const std::vector<const Client*> &v) const{
    std::cout << "╒════════════════╤═══════════════════════════════════════╤═══════════════════════════════╤═══════════════════════╤══════════════════╕" << std::endl;
    std::cout << "│ Username [0]   │ Name [1]                              │ Address [2]                   │ Phone number [3]      │ VAT [4]          │" << std::endl;
    std::cout << "╞════════════════╪═══════════════════════════════════════╪═══════════════════════════════╪═══════════════════════╪══════════════════╡" << std::endl;
    for(const Client* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_username()                 ,13) << "\t │ "
                  << utils::ljust((std::string)p->get_name()                     ,36) << "\t │ "
                  << utils::ljust((std::string)p->get_address().format("%street"),28) << "\t │ "
                  << utils::ljust((std::string)p->get_phonenumber()              ,20) << "\t │ "
                  << utils::rjust((std::string)p->get_vat()                      ,16) <<   " │"
                  << std::endl;
    }
    std::cout << "╘════════════════╧═══════════════════════════════════════╧═══════════════════════════════╧═══════════════════════╧══════════════════╛" << std::endl;
}

void App::print_list(const std::vector<const Manager*> &v) const{
    std::cout << "╒════════════════╤═══════════════════════════════════════╤═══════════════════════════════╤═══════════════════════╤══════════════════╤═════════════════╕" << std::endl;
    std::cout << "│ Username [0]   │ Name [1]                              │ Address [2]                   │ Phone number [3]      │ VAT [4]          │ Base salary [5] │" << std::endl;
    std::cout << "╞════════════════╪═══════════════════════════════════════╪═══════════════════════════════╪═══════════════════════╪══════════════════╪═════════════════╡" << std::endl;
    for(const Manager* p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p->get_username()                 ,13) << "\t │ "
                  << utils::ljust((std::string)p->get_name()                     ,36) << "\t │ "
                  << utils::ljust((std::string)p->get_address().format("%street"),28) << "\t │ "
                  << utils::ljust((std::string)p->get_phonenumber()              ,20) << "\t │ "
                  << utils::rjust((std::string)p->get_vat()                      ,16) <<   " │ "
                  << utils::rjust(utils::ftos("%.2f", p->get_base_salary())      ,15) <<   " │"
                  << std::endl;
    }
    std::cout << "╘════════════════╧═══════════════════════════════════════╧═══════════════════════════════╧═══════════════════════╧══════════════════╧═════════════════╛" << std::endl;
}

void App::list_clients(){
    //CLEAR();
    std::vector<const Client*> v(clients_.size());
    auto it = clients_.begin();
    for(const Client* &p:v) p = &((it++)->second);
    print_list(v);
}

void App::list_managers(){
    //CLEAR();
    std::vector<const Manager*> v(managers_.size());
    auto it = managers_.begin();
    for(const Manager* &p:v) p = &((it++)->second);
    print_list(v);
}

User* App::verifyUser(const std::string &username, const std::string &password) {
    try {
        User *user = &clients_.at(Client::Username(username));
        if (user->verifyCredentials(password)) return user;
        throw App::InvalidCredentials("Invalid credentials (password doesn't match).");
    } catch (std::out_of_range &oor) { }
    try {
        User *user = &drivers_.at(Driver::Username(username));
        if (user->verifyCredentials(password)) return user;
        throw App::InvalidCredentials("Invalid credentials (password doesn't match).");
    } catch (std::out_of_range &oor) { }
    try {
        User *user = &managers_.at(Manager::Username(username));
        if (user->verifyCredentials(password)) return user;
        throw App::InvalidCredentials("Invalid credentials (password doesn't match).");
    } catch (std::out_of_range &oor) {
        throw App::InvalidCredentials("Username not found (no matches for username " + username + " ).");
    }
    throw App::InvalidCredentials("Invalid credentials.");
}

bool App::guestMenu(User *user) {
    try {
        std::cout << "Agency SML                    \n"
                     "==============================\n"
                     "LOGIN                      [1]\n"
                     "CREATE NEW ACCOUNT         [2]\n";
        // LOGIN PROCESS
        // ...
        // CREATE ACCOUNT PROCESS
    } catch (...) {
        return false;
    }
    return true;
}

bool App::userMenu(User *user) {
    try {
        User::Type user_type = user->get_user_type();
        if (user_type == User::Type::client) {
            std::cout << "Service Management                Account Management           \n"
                         "==============================    =============================\n"
                         "Request service           [11]    Change address           [21]\n"
                         "Edit service              [12]    Change VAT               [22]\n"
                         "Cancel service            [13]    Change password          [23]\n"
                         "Service list              [14]                                 \n"
                         "                                                               \n";


        } else if (user_type == User::Type::driver) {
            std::cout << "Service Management                Account Management           \n"
                         "==============================    =============================\n"
                         "Service list              [11]    Change address           [21]\n"
                         "Solicit lay-off           [12]    Change VAT               [22]\n"
                         "Resign                    [13]    Change password          [23]\n"
                         "                                                               \n"
                         "Information visualization                                      \n"
                         "==============================    =============================\n"
                         "Statistics                [31]                                 \n"
                         "Trucks Information        [32]                                 \n"
                         "                                                               \n";

        } else if (user_type == User::Type::manager) {
            std::cout << "Services Management               Truck Management             \n"
                         "==============================    =============================\n"
                         "Add service               [11]    Add truck                [21]\n"
                         "Edit service              [12]    Edit truck               [22]\n"
                         "Delete service            [13]    Delete truck             [23]\n"
                         "                                                               \n"
                         "Client Management                 Driver Management            \n"
                         "==============================    =============================\n"
                         "Add client                [31]    Add driver               [41]\n"
                         "Edit client               [32]    Edit driver              [42]\n"
                         "Delete client             [33]    Delete driver            [43]\n"
                         "                                                               \n"
                         "Information visualization         Other operations             \n"
                         "==============================    =============================\n"
                         "Service list              [51]    Save                     [61]\n"
                         "Truck list                [52]    Exit                     [62]\n"
                         "Client list               [53]                                 \n"
                         "Driver list               [54]                                 \n"
                         "$$$$$ things              [55]                                 \n"
                         "                                                               \n";
        }


    } catch(...) {
        return false;
    }
    return true;
}

void App::start(){

}

App::InvalidCredentials::InvalidCredentials(const std::string &msg):
    std::runtime_error(msg){}

const std::string& App::InvalidCredentials::getMsg() const { return msg_; }

App::RepeatedId::RepeatedId(const std::string &id):
    runtime_error("Repeated id "+std::string(id)), id_(id){}
const std::string& App::RepeatedId::get_id() const{ return id_; }
