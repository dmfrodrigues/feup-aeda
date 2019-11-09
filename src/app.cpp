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
    save_all();
    list_clients();
    list_managers();
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
    std::cout << "Error: " << s << std::endl;
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
    return utils::linearfind(users_.begin(), users_.end(), u, [](const User *m, const User::Username &s){ return (m->get_username() == s); });
}

User* App::verifyUser(const std::string &username, const std::string &password) {
    const std::vector<User*>::iterator it = find_user(Client::Username(username));
    if (it == users_.end()) throw App::InvalidCredentials("Invalid username (username not found).");
    if ((*it)->verifyCredentials(password)) return *it;
    throw App::InvalidCredentials("Invalid credentials (password doesn't match).");
}

bool App::guestMenu(User *user) {
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
                std::cout << "Invalid operation\n"; wait();
                continue;
            }

            int operation;
            try {
                operation = std::stoi(v[0]);
            } catch (std::invalid_argument &e) {
                std::cout << "Invalid operation.\n";
                wait();
                continue;
            } catch (...) {
                wait();
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
                        std::cerr << "ERROR: " << ic.getMsg() << "\n";
                    }
                }
                break;
                case 2:
                    return false;
                    break;
                default:
                    std::cout << "Invalid operation.\n";
                    wait();
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

bool App::userMenu(const User* const user) {
    try {
        CLEAR();
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
    /*
    User *user = NULL;
    if (!guestMenu(user)) return;

    std::cout << "Check 1(login)\n";
    std::cout << "Check 1(login)\n";*/
    try {
        addUser();

    } catch(App::RepeatedId &e) {
        std::cerr << "ERROR: " << e.what() << "\n";
    }
    wait();

    list_clients();

}

App::InvalidCredentials::InvalidCredentials(const std::string &msg):
    std::runtime_error(msg), msg_(msg){}

const std::string& App::InvalidCredentials::getMsg() const { return msg_; }

App::RepeatedId::RepeatedId(const std::string &id):
    runtime_error("Repeated id "+std::string(id)), id_(id){}
const std::string& App::RepeatedId::get_id() const{ return id_; }
