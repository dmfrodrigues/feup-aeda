#include "app.h"

#include <stdexcept>

void CLEAR(){
    int ev;
    if((ev = CLEAR_MACRO()))
        throw std::system_error(ev, std::system_category());
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
    list_managers();
    display(dynamic_cast<const Client *>(filter_user_by_type(users_, User::Type::client )[2]));
    display(dynamic_cast<const Manager*>(filter_user_by_type(users_, User::Type::manager)[0]));
}

void App::request_service(){

}

std::vector<User*> App::filter_user_by_type(const std::vector<User*> &v, const User::Type &t){
    std::vector<User*> ret;
    for(User *p:v){
        if(p->get_type() == t){
            ret.push_back(p);
        }
    }
    return ret;
}

void App::list_clients(){
    //CLEAR();
    std::vector<const Client*> v;
    auto it = users_.begin();
    for(const User* p:users_){
        if(p->get_type() == User::Type::client){
            v.push_back(dynamic_cast<const Client*>(p));
        }
    }
    print_list(v);
}

void App::list_managers(){
    //CLEAR();
    std::vector<const Manager*> v;
    auto it = users_.begin();
    for(const User* p:users_){
        if(p->get_type() == User::Type::manager){
            v.push_back(dynamic_cast<const Manager*>(p));
        }
    }
    print_list(v);
}

User* App::find_user(const User::Username &u){
    auto it1 = utils::linearfind(users_.begin(), users_.end(), u, [](const User *m, const User::Username &s){ return (m->get_username() == s); });
    if(it1 != users_.end()) return *it1;
    return NULL; //#CHANGE
}

User* App::verifyUser(const std::string &username, const std::string &password) {
    User *user = find_user(Client::Username(username));
    if (user->verifyCredentials(password)) return user;
    throw App::InvalidCredentials("Invalid credentials (password doesn't match).");
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
        User::Type user_type = user->get_type();
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
