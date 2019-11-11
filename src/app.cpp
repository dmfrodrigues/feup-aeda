#include "app.h"

#include <stdexcept>

void CLEAR(){
    int ev;
    if((ev = CLEAR_MACRO()))
        throw std::system_error(ev, std::system_category());
}

const std::string App::OPSTR = "Operation$ ";

App::App(const std::string &base      ,
         const std::string &managers  , const std::string &drivers ,
         const std::string &clients   ,
         const std::string &trucks    , const std::string &services):
         managers_path_(base+managers), drivers_path_ (base+drivers ),
         clients_path_ (base+clients ),
         trucks_path_  (base+trucks  ), services_path_(base+services){
    std::cout << "Starting app..." << std::endl;
    load_all();
}

std::string App::prompt(){
    std::cout << OPSTR;
    std::string ret;
    std::getline(std::cin, ret);
    return ret;
}

void App::wait(){
    std::string b;
    std::cout << "(Press 'Enter' to continue)";
    std::getline(std::cin, b);
}

void App::error(const std::string &s){
    std::cerr << "Error: " << s << std::endl;
    wait();
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

const std::vector<User*>::iterator App::find_user(const User::Username &u){
    return utils::find_if(users_.begin(), users_.end(), [u](const User *m){ return (m->get_username() == u); });
}

const std::vector<Truck*>::iterator App::find_truck(const Truck::NumberPlate &np) {
    return utils::find_if(trucks_.begin(), trucks_.end(), [np](const Truck *truck) { return truck->get_numberplate() == np; });
}

User* App::verifyUser(const std::string &username, const std::string &password) {
    const std::vector<User*>::iterator it = find_user(Client::Username(username));
    if (it == users_.end()) throw App::InvalidCredentials("Invalid username (username not found).");
    if ((*it)->verifyCredentials(password)) return *it;
    throw App::InvalidCredentials("Invalid credentials (password doesn't match).");
}

bool App::guestMenu(User* &user) {
    try {
        while (true) {
            CLEAR();
            std::cout << "Agency SML                    \n"
                         "==============================\n"
                         "Login                      [1]\n"
                         "Exit                       [2]\n";

            // LOGIN PROCESS
            std::string cmd; std::cout << "\n" << OPSTR; getline(std::cin, cmd);
            std::vector<std::string> v = utils::parse_command(cmd);
            if(v.size() != 1){
                error("Invalid operation.");
                continue;
            }

            int operation;
            try {
                operation = std::stoi(v[0]);
            } catch (std::invalid_argument &e) {
                error("Invalid operation.");
                continue;
            } catch (...) {
                error("Unkown error.");
                continue;
            }

            switch (operation) {
                case 1:
                {
                    std::string username, password;
                    std::cout << "Username: "; std::getline(std::cin, username);
                    std::cout << "Password: "; std::getline(std::cin, password);
                    try {
                        user = verifyUser(username, password);
                        std::cout << "Login Success\n";
                        return true;
                    } catch (App::InvalidCredentials &ic) {
                        error(ic.getMsg());
                    }
                }
                break;
                case 2:
                    return false;
                    break;
                default:
                    error("Invalid operation.");
                    continue;
            }
            wait();
            // CREATE ACCOUNT PROCESS
        }
    } catch (...) {
        return false;
    }
    return true;
}

bool App::printUserMenu(User::Type user_type) {
    try {
        CLEAR();
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

bool App::userMenu(User *user, User::Type user_type) {
    try {
        int option;
        while (true) {
            if (!printUserMenu(user_type)) return false;

            if (!utils::input(App::OPSTR, option, std::cin, std::cout)) return true;

            if (user_type == User::Type::client) {

            } else if (user_type == User::Type::driver) {

            } else if (user_type == User::Type::manager) {

            }
        }
    } catch (...) {
        return false;
    }
    return true;
}

void App::start(){
    /*
    User *user = NULL;
    if (!guestMenu(user)) return;

    std::cout << "Check 1(login)\n";
    std::cout << "Check 1(login)\n";*/
    #ifdef TELMO

        list_trucks();
        deleteTruck();

        wait();

        list_trucks();

    #endif
    #ifdef DIOGO
        //save_all();
        //list_clients();
        //list_drivers();
        //list_managers();
        //list_trucks();
        display(services_[0]);
    #endif

    #if !defined(TELMO) && !defined(DIOGO)
    // main app
        User *user = NULL;
        while (true) {
            if (!guestMenu(user)) break;

            User::Type user_type = user->get_type();

            if (!userMenu(user_type)) {
                error("Unexpected error.");
                break;
            }
        }
        delete user;


    #endif
}

App::InvalidCredentials::InvalidCredentials(const std::string &msg):
    std::runtime_error(msg), msg_(msg){}

const std::string& App::InvalidCredentials::getMsg() const { return msg_; }

App::RepeatedId::RepeatedId(const std::string &id):
    runtime_error("Repeated id "+std::string(id)), id_(id){}
const std::string& App::RepeatedId::get_id() const{ return id_; }
