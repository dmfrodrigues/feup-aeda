#include "app.h"

#include <stdexcept>
#include <cassert>

void CLEAR(){
    int ev;
    if((ev = CLEAR_MACRO()))
        throw std::system_error(ev, std::system_category());
}

const float App::rate = 0.03;

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

App::~App() {
    for (User *user : users_)
        if (user != NULL)
            delete user;
    users_.clear();

    for (Truck *truck : trucks_)
        if (truck != NULL)
            delete truck;
    trucks_.clear();

    for (Service *service : services_)
        if (service != NULL)
            delete service;
    services_.clear();
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

bool App::confirm(const std::string &msg) {
    std::string input;
    while (true) {
        if (!utils::input(msg, input, std::cin, std::cout)) return false;
        utils::to_lower(input);
        if (input == "yes" || input == "y" || input == "no" || input == "n") break;
        std::cout << "Error: Only \'yes\'/\'y\' or \'no\'/\'n\' are valid options.\n";
    }
    if (input == "yes" || input == "y") return true;
    std::cout << "Operation cancelled.\n"; return false;
}

void App::error(const std::string &s){
    std::cerr << "Error: " << s << std::endl;
    wait();
}

bool App::get_schedule(const Driver *p, std::vector<std::pair<std::pair<Time,Time>, Service::ID> > &ret) const{
    Driver::Username u = p->get_username();
    std::vector<const Service*> vs;{
        std::vector<Service*> v = utils::filter(services_, [u](const Service *q){
            for(const Driver::Username &d:q->get_drivers()){
                if(d == u) return true;
            } return false;
        });
        vs = std::vector<const Service*>(v.begin(), v.end());
    }
    ret.clear();
    for(const Service *q:vs){
        ret.push_back(std::make_pair(std::make_pair(q->get_tbegin(),q->get_tend()),q->get_id()));
    }
    utils::mergesort(ret);
    for(size_t i = 0; i+1 < ret.size(); ++i)
        if(ret[i+1].first.first < ret[i].first.second){ //if the next service starts before the previous ends
            ret.clear();
            return false;
        }
    return true;
}

bool App::get_schedule(const Truck  *p, std::vector<std::pair<std::pair<Time,Time>, Service::ID> > &ret) const{
    Truck::NumberPlate u = p->get_numberplate();
    std::vector<const Service*> vs;{
        std::vector<Service*> v = utils::filter(services_, [u](const Service *q){
            for(const Truck::NumberPlate &d:q->get_trucks()){
                if(d == u) return true;
            } return false;
        });
        vs = std::vector<const Service*>(v.begin(), v.end());
    }
    ret.clear();
    for(const Service *q:vs){
        ret.push_back(std::make_pair(std::make_pair(q->get_tbegin(),q->get_tend()),q->get_id()));
    }
    utils::mergesort(ret);
    for(size_t i = 0; i+1 < ret.size(); ++i)
        if(ret[i+1].first.first < ret[i].first.second){ //if the next service starts before the previous ends
            ret.clear();
            return false;
        }
    return true;
}

std::vector<Driver*> App::get_available_drivers(const Time &tbegin, const Time &tend) const{
    std::vector<Driver*> ret;
    std::vector<User*> dv = App::filter_user_by_type(users_, User::Type::driver);
    for(User *p:dv){
        Driver *q = dynamic_cast<Driver*>(p);
        std::vector<std::pair<std::pair<Time,Time>, Service::ID> > v;
        assert(get_schedule(q, v));
        bool available = true;
        for(const auto &r:v){
            if(std::min(tbegin, r.first.first) < std::max(tend, r.first.second)){
                available = false;
                break;
            }
        }
        if(available) ret.push_back(q);
    }
    return ret;
}
std::vector<Truck *> App::get_available_trucks (const Time &tbegin, const Time &tend, const Cargo *c) const{
    std::vector<Truck*> ret;
    std::vector<Truck*> tv = utils::filter(trucks_, [c](const Truck *p){
        return (p->get_cargo()->can_carry(c));
    });
    for(Truck *p:tv){
        std::vector<std::pair<std::pair<Time,Time>, Service::ID> > v;
        assert(get_schedule(p, v));
        bool available = true;
        for(const auto &r:v){
            if(std::min(tbegin, r.first.first) < std::max(tend, r.first.second)){
                available = false;
                break;
            }
        }
        if(available) ret.push_back(p);
    }
    return ret;
}

std::vector<User*> App::filter_user_by_type(const std::vector<User*> &v, const User::Type &t) const {
    std::vector<User*> ret;
    for(User *p:v){
        if(p->get_type() == t){
            ret.push_back(p);
        }
    }
    return ret;
}

std::vector<Service*> App::filter_services_by_client(const std::vector<Service*> &v, const Client *client) const {
    std::vector<Service*> ret;
    for (Service *s : v)
        if (s->get_client() == client->get_username())
            ret.push_back(s);

    return ret;
}

std::vector<Service*> App::filter_services_by_driver(const std::vector<Service*> &v, const Driver *driver) const {
    std::vector<Service*> ret;
    for (Service *s : v)
        if (std::find(s->get_drivers().begin(), s->get_drivers().end(), driver->get_username()) != s->get_drivers().end())
            ret.push_back(s);

    return ret;
}


User* App::find_user(const User::Username &u) const{
    auto it = utils::find_if(users_.begin(), users_.end(), [u](const User *m){ return (m->get_username() == u); });
    if(it != users_.end()) return *it;
    else                   return NULL;
}

Truck* App::find_truck(const Truck::NumberPlate &np) const{
    auto it = utils::find_if(trucks_.begin(), trucks_.end(), [np](const Truck *truck) { return truck->get_numberplate() == np; });
    if(it != trucks_.end()) return *it;
    else                    return NULL;
}

Service* App::find_service(const std::string &id) const {
    auto it = utils::find_if(services_.begin(), services_.end(), [id](const Service *service) { return service->get_id() == id; });
    if(it != services_.end()) return *it;
    else                    return NULL;
}

User* App::verifyUser(const std::string &username, const std::string &password) {
    User *it = find_user(Client::Username(username));
    if (it == NULL) throw App::InvalidCredentials("Invalid username (username not found).");
    if (it->verifyCredentials(password)) return it;
    throw App::InvalidCredentials("Invalid credentials (password doesn't match).");
}

bool App::guestMenu(User* &user) {
    try {
        while (true) {
            CLEAR();
            std::cout <<    "╒═════════════════════════════════════════════╕\n"
                            "│                 Agency SML                  │\n"
                            "╞═════════════════════════════════════════════╡\n"
                            "│  Login                                  [1] │\n"
                            "│  Exit                                   [2] │\n"
                            "╘═════════════════════════════════════════════╛\n"
                            "                                               \n";
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
                        continue;
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
            std::cout <<    "╒═════════════════════════════════════════════╤═════════════════════════════════════════════╕\n"
                            "│             Service Management              │             Account Management              │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│  Request service                       [11] │  Edit account                          [21] │\n"
                            "│  Cancel service                        [12] │  View account                          [22] │\n"
                            "│  Service list                          [13] │  Change password                       [23] │\n"
                            "╞═════════════════════════════════════════════╡                                             │\n"
                            "│                Other operations             │                                             │\n"
                            "╞═════════════════════════════════════════════╡                                             │\n"
                            "│  Log out                               [31] │                                             │\n"
                            "╘═════════════════════════════════════════════╧═════════════════════════════════════════════╛\n"
                            "                                                                                             \n";
        } else if (user_type == User::Type::driver) {
            std::cout <<    "╒═════════════════════════════════════════════╤═════════════════════════════════════════════╕\n"
                            "│          Information visualization          │               Account Management            │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│  Service list                          [11] │  Edit account                          [21] │\n"
                            "│  Truck list                            [12] │  View account                          [22] │\n"
                            "╞═════════════════════════════════════════════╡  Change password                       [23] │\n"
                            "│                Other operations             │                                             │\n"
                            "╞═════════════════════════════════════════════╡                                             │\n"
                            "│  Log out                               [31] │                                             │\n"
                            "╘═════════════════════════════════════════════╧═════════════════════════════════════════════╛\n"
                            "                                                                                             \n";
        } else if (user_type == User::Type::manager) {
            std::cout <<    "╒═════════════════════════════════════════════╤═════════════════════════════════════════════╕\n"
                            "│             Service Management              │               Truck Management              │\n"
                            "├─────────────────────────────────────────────┼─────────────────────────────────────────────┤\n"
                            "│  Add service                           [11] │  Add truck                             [21] │\n"
                            "│  Delete service                        [12] │  Edit truck                            [22] │\n"
                            "│                                             │  Delete truck                          [23] │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│              Client management              │               Driver Management             │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│  Add client                            [31] │  Add driver                            [41] │\n"
                            "│  Edit client                           [32] │  Edit driver                           [42] │\n"
                            "│  Delete client                         [33] │  Delete driver                         [43] │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│              Manager management             │          Information visualization          │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│  Add manager                           [51] │  Service list                          [61] │\n"
                            "│  Edit manager                          [52] │  Truck list                            [62] │\n"
                            "│  Delete manager                        [53] │  Client list                           [63] │\n"
                            "│                                             │  Driver list                           [64] │\n"
                            "│                                             │  Manager list                          [65] │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│               Account Management            │                Other operations             │\n"
                            "╞═════════════════════════════════════════════╪═════════════════════════════════════════════╡\n"
                            "│  Edit account                          [71] │  Save                                  [81] │\n"
                            "│  View account                          [72] │  Log out                               [82] │\n"
                            "│  Change password                       [73] │                                             │\n"
                            "╘═════════════════════════════════════════════╧═════════════════════════════════════════════╛\n"
                            "                                                                                             \n";
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
                switch (option) {
                //SERVICE MANAGEMENT                                            //ACCOUNT MANAGEMENT
                case 11: addService(user); wait();                   break;     case 21: editUser<Client>(user); wait();                    break;
                case 12: deleteService(user); wait();                break;     case 22: CLEAR(); App::display(dynamic_cast<Client*>(user), User::Type::manager); wait(); break;
                case 13: list_services(user);                        break;     case 23: changePassword(user); wait();  break;
                //OTHER OPERATIONS
                case 31: return true;                                break;
                default:
                    error("Invalid operation.");
                    break;
                }

            } else if (user_type == User::Type::driver) {
                switch (option) {
                //INFORMATION VISUALIZATION                                     //ACCOUNT MANAGEMENT
                case 11: list_services(user);                        break;     case 21: editUser<Driver>(user); wait();                    break;
                case 12: list_trucks();                              break;     case 22: CLEAR(); App::display(dynamic_cast<Driver*>(user), User::Type::manager); wait(); break;
                                                                                case 23: changePassword(user); wait();  break;
                //OTHER OPERATIONS
                case 31: return true;                                break;
                default:
                    error("Invalid operation.");
                    break;
                }

            } else if (user_type == User::Type::manager) {
                switch (option) {
                //SERVICE MANAGEMENT                                            //TRUCK MAANAGEMENT
                case 11: addService(); wait();                      break;      case 21: addTruck(); wait();                                break;
                case 12: deleteService(); wait();                   break;      case 22: editTruck(); wait();                               break;
                                                                                case 23: deleteTruck(); wait();                             break;

                //CLIENT MANAGEMENT                                             //DRIVER MANAGEMENT
                case 31: addUser(User::Type::client); wait();       break;      case 41: addUser(User::Type::driver); wait();                      break;
                case 32: editUser<Client>(User::Type::client); wait(); break;      case 42: editUser<Driver>(User::Type::driver); wait();             break;
                case 33: deleteUser<Client>(User::Type::client); wait(); break;      case 43: deleteUser<Driver>(User::Type::driver); wait();           break;

                //MANAGER MANAGEMENT                                            //INFORMATION VISUALIZATION
                case 51: addUser(User::Type::manager); wait();             break;      case 61: list_services();                                   break;
                case 52: editUser<Manager>(User::Type::manager); wait();    break;      case 62: list_trucks();                                     break;
                case 53: deleteUser<Manager>(User::Type::manager); wait();  break;      case 63: list_clients();                                    break;
                                                                                case 64: list_drivers();                                    break;
                                                                                case 65: list_managers();                                   break;

                //ACCOUNT MANAGEMENT                                            //OTHER OPERATIONS
                case 71: editUser<Manager>(user); wait(); wait();                       break;  case 81: save_all();                                    break;
                case 72: CLEAR(); App::display(dynamic_cast<Manager*>(user), User::Type::manager); wait();    break;  case 82: return true;                                   break;
                case 73: changePassword(user); wait();  break;

                default:
                    error("Invalid operation.");
                    break;
                }
            }
        }
    } catch (...) {
        return false;
    }
    return true;
}

void App::start(){
    #ifdef TELMO

        Time t = Time();

        t.input_time("2019/06/22 23:43:05");

        std::cout << t << "\n";

        t.input_date("2019/11/13");

        std::cout << t << "\n";

    #endif
    #ifdef DIOGO
        save_all();
        //list_clients();
        //list_drivers();
        //list_managers();
        //list_trucks();
        //print_list(std::vector<const Service*>(services_.begin(), services_.end()), User::Type::client);
        //list_services();
        //list_services();
        //addService();
        //wait();
        //list_services();
        //save_all();
    #endif

    #if !defined(TELMO) && !defined(DIOGO)
    // main app
        User *user = NULL;
        while (true) {
            if (!guestMenu(user)) break;

            if (user == NULL) continue;

            User::Type user_type = user->get_type();

            if (!userMenu(user, user_type)) {
                error("Unexpected error.");
                break;
            }
        }
        save_all();
    #endif
}

App::InvalidCredentials::InvalidCredentials(const std::string &msg):
    std::runtime_error(msg), msg_(msg){}

const std::string& App::InvalidCredentials::getMsg() const { return msg_; }

App::RepeatedId::RepeatedId(const std::string &id):
    runtime_error("Repeated id "+id), id_(id){}
const std::string& App::RepeatedId::get_id() const{ return id_; }
