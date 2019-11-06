#include "app.h"

template<class ID, class T>
void App::load(std::ifstream &is, std::map<ID, T> &ret){
    is.exceptions(std::ifstream::eofbit | std::ifstream::badbit | std::ifstream::failbit);
    size_t N; is >> N;
    ret = std::map<ID, T>();
    while(N--){
        T m; is >> m;
        if(ret.find(m.get_id()) != ret.end())
            throw App::RepeatedId(m.get_id());
        ret[m.get_id()] = m;
    }
}
template<class ID, class T>
void App::load_ptr(std::ifstream &is, std::map<ID, T*> &ret){
    is.exceptions(std::ifstream::eofbit | std::ifstream::badbit | std::ifstream::failbit);;
    size_t N; is >> N;
    ret = std::map<ID, T*>();
    while(N--){
        T *m = new T(); is >> *m;
        if(ret.find(m->get_id()) != ret.end()){
            auto id = m->get_id();
            delete m;
            throw App::RepeatedId(id);
        }
        ret[m->get_id()] = m;
    }
}

template<class T>
void App::save(const std::string &path, const std::map<std::string, T> &m){
    std::ofstream os(path);
    os.exceptions(std::ifstream::eofbit | std::ifstream::badbit | std::ifstream::failbit);
    os << m.size() << "\n";
    for(const std::pair<std::string, T> &p:m){
        os << p.second << "\n";
    }
}

void App::load_all(){
    { std::cout << "Loading managers..."; std::ifstream is(managers_path_); load    (is, managers_); std::cout << " Done\n"; }
    { std::cout << "Loading drivers ..."; std::ifstream is(drivers_path_ ); load    (is, drivers_ ); std::cout << " Done\n"; }
    { std::cout << "Loading clients ..."; std::ifstream is(clients_path_ ); load    (is, clients_ ); std::cout << " Done\n"; }
    { std::cout << "Loading trucks  ..."; std::ifstream is(trucks_path_  ); load_ptr(is, trucks_  ); std::cout << " Done\n"; }
    {
        std::cout << "Loading services...";
        std::ifstream is(services_path_);
        is >> Service::next_id_;
        load(is, services_);
        std::cout << " Done\n";
    }
}

bool App::save_all(){
    save(managers_path_, managers_);
    save(drivers_path_ , drivers_ );
    save(clients_path_ , clients_ );
}

App::App(const std::string &base      ,
         const std::string &managers  , const std::string &drivers ,
         const std::string &clients   ,
         const std::string &trucks    , const std::string &services):
         managers_path_(base+managers), drivers_path_ (base+drivers ),
         clients_path_ (base+clients ),
         trucks_path_  (base+trucks  ), services_path_(base+services){
    load_all();
    save_all();
}

void App::request_service(){

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
}

void App::start(){

}

App::RepeatedId::RepeatedId(const std::string &id):
    runtime_error("Repeated id "+std::string(id)), id_(id){}
const std::string& App::RepeatedId::get_id() const{ return id_; }
