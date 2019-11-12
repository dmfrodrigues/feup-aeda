#include "app.h"

#include <cassert> //#DEV

template<class T> void App::list_commands(){ T::unimplemented_function; }
template<> void App::list_commands<Client >(){
    std::cout << "\n"
              << "COMMANDS:\n\n"
              << "    sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0-4].\n"
              << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0-4].\n"
              << "    details \"\033[4mSTR\033[0m\"       Print details of client with username \033[4mSTR\033[0m\n"
              << "    reset               Reset to initial selection.\n"
              << "    back                Go back.\n";
    std::cout << std::endl;
}
template<> void App::list_commands<Driver >(){
    std::cout << "\n"
              << "COMMANDS:\n\n"
              << "    sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0-5].\n"
              << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0-5].\n"
              << "    details \"\033[4mSTR\033[0m\"       Print details of driver with username \033[4mSTR\033[0m\n"
              << "    reset               Reset to initial selection.\n"
              << "    back                Go back.\n";
    std::cout << std::endl;
}
template<> void App::list_commands<Manager>(){
    std::cout << "\n"
              << "COMMANDS:\n\n"
              << "    sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0-5].\n"
              << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0-5].\n"
              << "    details \"\033[4mSTR\033[0m\"       Print details of manager with username \033[4mSTR\033[0m\n"
              << "    reset               Reset to initial selection.\n"
              << "    back                Go back.\n";
    std::cout << std::endl;
}
template<> void App::list_commands<Truck  >(){
    std::cout << "\n"
              << "COMMANDS:\n\n"
              << "    sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0-4].\n"
              << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0-5].\n"
              << "    details \"\033[4mSTR\033[0m\"       Print details of truck with number plate \033[4mSTR\033[0m\n"
              << "    reset               Reset to initial selection.\n"
              << "    back                Go back.\n";
    std::cout << std::endl;
}
template<> void App::list_commands<Service>(){
    std::cout << "\n"
              << "COMMANDS:\n\n"
              << "    sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0,1,4-8].\n"
              << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0-7,9].\n"
              << "    details \"\033[4mSTR\033[0m\"       Print details of service with ID \033[4mSTR\033[0m\n"
              << "    reset               Reset to initial selection.\n"
              << "    back                Go back.\n";
    std::cout << std::endl;
}

void App::list_sort_getcomp(int i, std::function<bool(const Client *, const Client *)> &cmp){
    switch(i){
        case 0: cmp = [](const Client *p1, const Client *p2){ return (p1->get_username   () < p2->get_username   ()); }; break;
        case 1: cmp = [](const Client *p1, const Client *p2){ return (p1->get_name       () < p2->get_name       ()); }; break;
        case 2: cmp = [](const Client *p1, const Client *p2){ return (p1->get_address    () < p2->get_address    ()); }; break;
        case 3: cmp = [](const Client *p1, const Client *p2){ return (p1->get_phonenumber() < p2->get_phonenumber()); }; break;
        case 4: cmp = [](const Client *p1, const Client *p2){ return (p1->get_vat        () < p2->get_vat        ()); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_sort_getcomp(int i, std::function<bool(const Driver *, const Driver *)> &cmp){
    switch(i){
        case 0: cmp = [](const Driver *p1, const Driver *p2){ return (p1->get_username   () < p2->get_username   ()); }; break;
        case 1: cmp = [](const Driver *p1, const Driver *p2){ return (p1->get_name       () < p2->get_name       ()); }; break;
        case 2: cmp = [](const Driver *p1, const Driver *p2){ return (p1->get_address    () < p2->get_address    ()); }; break;
        case 3: cmp = [](const Driver *p1, const Driver *p2){ return (p1->get_phonenumber() < p2->get_phonenumber()); }; break;
        case 4: cmp = [](const Driver *p1, const Driver *p2){ return (p1->get_vat        () < p2->get_vat        ()); }; break;
        case 5: cmp = [](const Driver *p1, const Driver *p2){ return (p1->get_base_salary() < p2->get_base_salary()); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_sort_getcomp(int i, std::function<bool(const Manager*, const Manager*)> &cmp){
    switch(i){
        case 0: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_username   () < p2->get_username   ()); }; break;
        case 1: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_name       () < p2->get_name       ()); }; break;
        case 2: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_address    () < p2->get_address    ()); }; break;
        case 3: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_phonenumber() < p2->get_phonenumber()); }; break;
        case 4: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_vat        () < p2->get_vat        ()); }; break;
        case 5: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_base_salary() < p2->get_base_salary()); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_sort_getcomp(int i, std::function<bool(const Truck  *, const Truck  *)> &cmp){
    switch(i){
        case 0: cmp = [](const Truck *p1, const Truck *p2){ return (p1->get_numberplate      () < p2->get_numberplate      ()); }; break;
        case 1: cmp = [](const Truck *p1, const Truck *p2){ return (p1->get_plateregisterdate() < p2->get_plateregisterdate()); }; break;
        case 2: cmp = [](const Truck *p1, const Truck *p2){ return (p1->get_fuel             () < p2->get_fuel             ()); }; break;
        case 3: cmp = [](const Truck *p1, const Truck *p2){ return (p1->get_range            () < p2->get_range            ()); }; break;
        case 4: cmp = [](const Truck *p1, const Truck *p2){ return (p1->get_category         () < p2->get_category         ()); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_sort_getcomp(int i, std::function<bool(const Service*, const Service*)> &cmp){
    switch(i){
        case 0: cmp = [](const Service *p1, const Service *p2){ return (p1->get_id    () < p2->get_id    ()); }; break;
        case 1: cmp = [](const Service *p1, const Service *p2){ return (p1->get_client() < p2->get_client()); }; break;
        case 4: cmp = [](const Service *p1, const Service *p2){ return (p1->get_tbegin() < p2->get_tbegin()); }; break;
        case 5: cmp = [](const Service *p1, const Service *p2){ return (p1->get_tend  () < p2->get_tend  ()); }; break;
        case 6: cmp = [](const Service *p1, const Service *p2){ return (p1->get_abegin().format("%district %city") < p2->get_abegin().format("%district %city")); }; break;
        case 7: cmp = [](const Service *p1, const Service *p2){ return (p1->get_aend  ().format("%district %city") < p2->get_aend  ().format("%district %city")); }; break;
        case 8: cmp = [](const Service *p1, const Service *p2){
            if(p1->get_cargo()->get_type() != p2->get_cargo()->get_type()) return (p1->get_cargo()->get_type  () < p2->get_cargo()->get_type  ());
            return                                                                (p1->get_cargo()->get_weight() < p2->get_cargo()->get_weight());
        }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}

void App::list_filter_getvalid(int i, const std::string &str, std::function<bool(const Client *)> &cmp){
    switch(i){
        case 0: cmp = [str](const Client *p){ return (std::string(p->get_username   ()).find(str) != std::string::npos); }; break;
        case 1: cmp = [str](const Client *p){ return (std::string(p->get_name       ()).find(str) != std::string::npos); }; break;
        case 2: cmp = [str](const Client *p){ return (p->get_address().format()        .find(str) != std::string::npos); }; break;
        case 3: cmp = [str](const Client *p){ return (std::string(p->get_phonenumber()).find(str) != std::string::npos); }; break;
        case 4: cmp = [str](const Client *p){ return (std::string(p->get_vat        ()).find(str) != std::string::npos); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_filter_getvalid(int i, const std::string &str, std::function<bool(const Driver *)> &cmp){
    switch(i){
        case 0: cmp = [str](const Driver *p){ return (std::string(p->get_username   ()).find(str) != std::string::npos); }; break;
        case 1: cmp = [str](const Driver *p){ return (std::string(p->get_name       ()).find(str) != std::string::npos); }; break;
        case 2: cmp = [str](const Driver *p){ return (p->get_address().format()        .find(str) != std::string::npos); }; break;
        case 3: cmp = [str](const Driver *p){ return (std::string(p->get_phonenumber()).find(str) != std::string::npos); }; break;
        case 4: cmp = [str](const Driver *p){ return (std::string(p->get_vat        ()).find(str) != std::string::npos); }; break;
        case 5: cmp = [str](const Driver *p){ return (Currency(std::stod(str))                    ==p->get_base_salary());};break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_filter_getvalid(int i, const std::string &str, std::function<bool(const Manager*)> &cmp){
    switch(i){
        case 0: cmp = [str](const Manager *p){ return (std::string(p->get_username   ()).find(str) != std::string::npos); }; break;
        case 1: cmp = [str](const Manager *p){ return (std::string(p->get_name       ()).find(str) != std::string::npos); }; break;
        case 2: cmp = [str](const Manager *p){ return (p->get_address().format()        .find(str) != std::string::npos); }; break;
        case 3: cmp = [str](const Manager *p){ return (std::string(p->get_phonenumber()).find(str) != std::string::npos); }; break;
        case 4: cmp = [str](const Manager *p){ return (std::string(p->get_vat        ()).find(str) != std::string::npos); }; break;
        case 5: cmp = [str](const Manager *p){ return (Currency(std::stod(str))                    ==p->get_base_salary());};break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_filter_getvalid(int i, const std::string &str, std::function<bool(const Truck  *)> &cmp){
    switch(i){
        case 0: cmp = [str](const Truck *p){ return (std::string(p->get_numberplate())            .find(str) != std::string::npos); }; break;
        case 1: cmp = [str](const Truck *p){ return (p->get_plateregisterdate().format("%Y/%m/%d").find(str) != std::string::npos); }; break;
        case 2: cmp = [str](const Truck *p){ return (Truck::fuel_string(p->get_fuel())            .find(str) != std::string::npos); }; break;
        case 3: cmp = [str](const Truck *p){ return utils::feq((float)p->get_range(), std::stof(str), 0.1)                        ; }; break;
        case 4: cmp = [str](const Truck *p){ return (std::string(p->get_category())               .find(str) != std::string::npos); }; break;
        case 5: cmp = [str](const Truck *p){ return (App::get_cargo_string(p)                     .find(str) != std::string::npos); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void App::list_filter_getvalid(int i, const std::string &str, std::function<bool(const Service*)> &cmp){
    switch(i){
        case 0: cmp = [str](const Service *p){ return (std::string(p->get_id())                   .find(str) != std::string::npos); }; break;
        case 1: cmp = [str](const Service *p){ return (std::string(p->get_client())               .find(str) != std::string::npos); }; break;
        case 2: cmp = [str](const Service *p){ return ((std::string(p->get_contact1().get_name())+" "+std::string(p->get_contact1().get_phonenumber())).find(str) != std::string::npos); }; break;
        case 3: cmp = [str](const Service *p){ return ((std::string(p->get_contact2().get_name())+" "+std::string(p->get_contact2().get_phonenumber())).find(str) != std::string::npos); }; break;
        case 4: cmp = [str](const Service *p){ return (p->get_tbegin().format("%Y/%m/%d %H:%M:%S").find(str) != std::string::npos); }; break;
        case 5: cmp = [str](const Service *p){ return (p->get_tend  ().format("%Y/%m/%d %H:%M:%S").find(str) != std::string::npos); }; break;
        case 6: cmp = [str](const Service *p){ return (p->get_abegin().format("(%district) %city").find(str) != std::string::npos); }; break;
        case 7: cmp = [str](const Service *p){ return (p->get_aend  ().format("(%district) %city").find(str) != std::string::npos); }; break;
        case 9: cmp = [str](const Service *p){
            const std::vector<Truck::NumberPlate> tv = p->get_trucks();
            const std::vector<Driver::Username  > dv = p->get_drivers();
            for(size_t j = 0; j < tv.size(); ++j){
                if(std::string(tv[j]).find(str) != std::string::npos ||
                   std::string(dv[j]).find(str) != std::string::npos) return true;
            }
            return false;
        }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}

template<class T> void App::list(std::vector<const T*> v) const{
    const std::vector<const T*> original = v;
    while(true){
        CLEAR();
        print_list(v);
        list_commands<T>();
        std::vector<std::string> s = utils::parse_command(prompt());
        if(s.size() >= 1){
            //====SORT==========================================================
            if(s[0] == "sort"){
                if(s.size() != 2){ error("wrong number of arguments"); continue; }
                int i; try{ i = utils::stoi(s[1]); } catch(const std::invalid_argument &e){ error("invalid NUM"); continue; }
                std::function<bool(const T*, const T*)> cmp;
                try{
                    list_sort_getcomp(i, cmp);
                    utils::mergesort(v,cmp);
                }catch(const std::invalid_argument &e){ error(e.what()); }
            }else
            //====SEARCH========================================================
            if(s[0] == "search"){
                if(s.size() != 3){ error("wrong number of arguments"); continue; }
                int i; try{ i = utils::stoi(s[1]); } catch(const std::invalid_argument &e){ error("invalid NUM"); continue; }
                std::function<bool(const T*)> cmp;
                try{
                    list_filter_getvalid(i, s[2], cmp);
                    v = utils::filter(v,cmp);
                }catch(const std::invalid_argument &e){ error(e.what()); }
            }else
            //====DETAILS=======================================================
            if(s[0] == "details"){
                if(s.size() != 2){ error("wrong number of arguments"); continue; }
                const std::string &u = s[1];
                auto it = utils::find_if(v.begin(), v.end(),
                  [&u](const T *p){ return (std::string(p->get_id()) == u); });
                if(it == v.end()){ error("no such username in table"); continue; }
                std::cout << std::endl;
                display(dynamic_cast<const T*>(*it));
                std::cout << std::endl;
                wait();
            }else
            //====RESET=========================================================
            if(s[0] == "reset"){
                if(s.size() != 1) error("wrong number of arguments");
                else              v = original;
            }else
            //====BACK==========================================================
            if(s[0] == "back"){
                if(s.size() != 1) error("wrong number of arguments");
                else              return;
            }else
            //====ERROR=========================================================
                error("unrecognized command");
        }
    }
}

void App::list_clients () const{
    std::vector<const User*> v(users_.begin(), users_.end());
    std::vector<const Client*> w = App::filter<User,Client,User::Type>(v, User::Type::client);
    list(w);
}
void App::list_drivers () const{
    std::vector<const User*> v(users_.begin(), users_.end());
    std::vector<const Driver*> w = App::filter<User,Driver,User::Type>(v, User::Type::driver);
    list(w);
}
void App::list_managers() const{
    std::vector<const User*> v(users_.begin(), users_.end());
    std::vector<const Manager*> w = App::filter<User,Manager,User::Type>(v, User::Type::manager);
    list(w);
}
void App::list_trucks  () const{
    std::vector<const Truck*> v(trucks_.begin(), trucks_.end());
    list(v);
}
void App::list_services() const{
    std::vector<const Service*> v(services_.begin(), services_.end());
    list(v);
}
void App::list_services(const User *user) const{
    std::vector<Service*> v = filter_services_by_user(services_, user);
    std::vector<const Service*> w(v.begin(), v.end());
    list(w);
}
