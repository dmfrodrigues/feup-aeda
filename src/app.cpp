#include "app.h"

template<class T>
std::map<std::string, T> App::load(const std::string &path){
    std::ifstream is(path);
    is.exceptions(std::ifstream::eofbit | std::ifstream::badbit | std::ifstream::failbit);
    size_t N; is >> N;
    std::map<std::string, T> ret;
    while(N--){
        T m; is >> m;
        if(ret.find(m.get_id()) != ret.end())
            throw App::RepeatedName(m.get_name());
        ret[m.get_id()] = m;
    }
    return ret;
}
template<class T>
std::map<std::string, T*> App::load_ptr(const std::string &path){
    std::ifstream is(path);
    is.exceptions(std::ifstream::eofbit | std::ifstream::badbit | std::ifstream::failbit);
    size_t N; is >> N;
    std::map<std::string, T> ret;
    while(N--){
        T *m = new T(); is >> *m;
        ret[m->get_id()] = m;
    }
    return ret;
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

App::App(const std::string &base      ,
         const std::string &managers  , const std::string &drivers ,
         const std::string &clients   ,
         const std::string &trucks    , const std::string &services):
         managers_path_(base+managers), drivers_path_ (base+drivers ),
         clients_path_ (base+clients ),
         trucks_path_  (base+trucks  ), services_path_(base+services){
    managers_ = load    <Manager>(managers_path_);
    drivers_  = load    <Driver >(drivers_path_ );
    clients_  = load    <Client >(clients_path_ );
    //trucks_   = load_ptr<Truck  >(trucks_path_  );
    //services_ = load    <Service>(services_path_);
    save_all();

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
                         "Solicit resignation????   [13]    Change password          [23]\n"
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

bool App::save_all(){
    save(managers_path_, managers_);
    save(drivers_path_ , drivers_ );
    save(clients_path_ , clients_ );
}

App::RepeatedName::RepeatedName(const std::string &name):
    runtime_error("Repeated name "+name),
    name_(name){}

const std::string& App::RepeatedName::get_name() const{ return name_; }
