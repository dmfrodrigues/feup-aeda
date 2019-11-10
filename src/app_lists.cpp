#include "app.h"

template<class Base, class Deriv, class Type>
std::vector<const Deriv*> App::filter_users(const std::vector<const Base*> &v, const Type &t){
    std::vector<const Base*> v1 = utils::filter(v, [&t](const Base *p){ return (p->get_type() == t); });
    std::vector<const Deriv*> retv = std::vector<const Deriv*>(v1.size());
    std::transform(v1.begin(), v1.end(), retv.begin(), [](const Base *p){
        const Deriv *ret = dynamic_cast<const Deriv*>(p);
        if(ret == nullptr) throw std::bad_cast();
        return ret;
    });
    return retv;
}

void App::list_clients_commands(){
    std::cout << "\n"
              << "COMMANDS:\n\n"
              << "    sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0,4].\n"
              << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0,4].\n"
              << "    details \"\033[4mSTR\033[0m\"       Print details of client with username \033[4mSTR\033[0m\n"
              << "    reset               Reset to initial selection.\n"
              << "    back                Go back.\n";
    std::cout << std::endl;
}

void App::list_drivers_commands(){
    std::cout << "\n"
              << "COMMANDS:\n\n"
              << "    sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0,5].\n"
              << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0,5].\n"
              << "    details \"\033[4mSTR\033[0m\"       Print details of driver with username \033[4mSTR\033[0m\n"
              << "    reset               Reset to initial selection.\n"
              << "    back                Go back.\n";
    std::cout << std::endl;
}

void App::list_managers_commands(){
    std::cout << "\n"
              << "COMMANDS:\n\n"
              << "    sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0,5].\n"
              << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0,5].\n"
              << "    details \"\033[4mSTR\033[0m\"       Print details of manager with username \033[4mSTR\033[0m\n"
              << "    reset               Reset to initial selection.\n"
              << "    back                Go back.\n";
    std::cout << std::endl;
}

void App::list_commands(const User::Type &t){
    switch(t){
        case User::Type::client : list_clients_commands (); break;
        case User::Type::driver : list_drivers_commands (); break;
        case User::Type::manager: list_managers_commands(); break;
        default: break;
    }
}

void App::list_commands(const Truck::Type &t){
    std::cout << "\n"
              << "COMMANDS:\n\n"
              << "    sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0,5].\n"
              << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0,5].\n"
              << "    details \"\033[4mSTR\033[0m\"       Print details of truck with number plate \033[4mSTR\033[0m\n"
              << "    reset               Reset to initial selection.\n"
              << "    back                Go back.\n";
    std::cout << std::endl;
}

void App::list_sort_getcomp(int i, std::function<bool(const Client*, const Client*)> &cmp){
    switch(i){
        case 0: cmp = [](const Client *p1, const Client *p2){ return (p1->get_username   () < p2->get_username   ()); }; break;
        case 1: cmp = [](const Client *p1, const Client *p2){ return (p1->get_name       () < p2->get_name       ()); }; break;
        case 2: cmp = [](const Client *p1, const Client *p2){ return (p1->get_address    () < p2->get_address    ()); }; break;
        case 3: cmp = [](const Client *p1, const Client *p2){ return (p1->get_phonenumber() < p2->get_phonenumber()); }; break;
        case 4: cmp = [](const Client *p1, const Client *p2){ return (p1->get_vat        () < p2->get_vat        ()); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}

void App::list_sort_getcomp(int i, std::function<bool(const Driver*, const Driver*)> &cmp){
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

void App::list_sort_getcomp(int i, std::function<bool(const Truck*, const Truck*)> &cmp){
    cmp = [](const Truck *p1, const Truck *p2){ return true; };
    /*
    switch(i){
        case 0: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_username   () < p2->get_username   ()); }; break;
        case 1: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_name       () < p2->get_name       ()); }; break;
        case 2: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_address    () < p2->get_address    ()); }; break;
        case 3: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_phonenumber() < p2->get_phonenumber()); }; break;
        case 4: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_vat        () < p2->get_vat        ()); }; break;
        case 5: cmp = [](const Manager *p1, const Manager *p2){ return (p1->get_base_salary() < p2->get_base_salary()); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
    */
}

void App::list_filter_getvalid(int i, const std::string &str, std::function<bool(const Client*)> &cmp){
    switch(i){
        case 0: cmp = [str](const Client *p){ return (std::string(p->get_username   ()).find(str) != std::string::npos); }; break;
        case 1: cmp = [str](const Client *p){ return (std::string(p->get_name       ()).find(str) != std::string::npos); }; break;
        case 2: cmp = [str](const Client *p){ return (p->get_address().format()        .find(str) != std::string::npos); }; break;
        case 3: cmp = [str](const Client *p){ return (std::string(p->get_phonenumber()).find(str) != std::string::npos); }; break;
        case 4: cmp = [str](const Client *p){ return (std::string(p->get_vat        ()).find(str) != std::string::npos); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}

void App::list_filter_getvalid(int i, const std::string &str, std::function<bool(const Driver*)> &cmp){
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

void App::list_filter_getvalid(int i, const std::string &str, std::function<bool(const Truck*)> &cmp){
    cmp = [](const Truck *p){ return true; };
    /*
    switch(i){
        case 0: cmp = [str](const Manager *p){ return (std::string(p->get_username   ()).find(str) != std::string::npos); }; break;
        case 1: cmp = [str](const Manager *p){ return (std::string(p->get_name       ()).find(str) != std::string::npos); }; break;
        case 2: cmp = [str](const Manager *p){ return (p->get_address().format()        .find(str) != std::string::npos); }; break;
        case 3: cmp = [str](const Manager *p){ return (std::string(p->get_phonenumber()).find(str) != std::string::npos); }; break;
        case 4: cmp = [str](const Manager *p){ return (std::string(p->get_vat        ()).find(str) != std::string::npos); }; break;
        case 5: cmp = [str](const Manager *p){ return (Currency(std::stod(str))                    ==p->get_base_salary());};break;
        default: throw std::invalid_argument("NUM outside range");
    }
    */
}

template<class Base, class Deriv, class Type> void App::list(const std::vector<const Base*> &w, const Type &t) const{
    std::vector<const Deriv*> v = filter_users<Base,Deriv,Type>(w, t);
    while(true){
        CLEAR();
        print_list(v);
        list_commands(t);
        std::vector<std::string> s = utils::parse_command(prompt());
        if(s.size() >= 1){
            //====SORT==========================================================
            if(s[0] == "sort"){
                if(s.size() != 2){ error("wrong number of arguments"); continue; }
                int i; try{ i = utils::stoi(s[1]); } catch(const std::invalid_argument &e){ error("invalid NUM"); continue; }
                std::function<bool(const Deriv*, const Deriv*)> cmp;
                try{
                    list_sort_getcomp(i, cmp);
                    utils::mergesort(v,cmp);
                }catch(const std::invalid_argument &e){ error(e.what()); }
            }else
            //====SEARCH========================================================
            if(s[0] == "search"){
                if(s.size() != 3){ error("wrong number of arguments"); continue; }
                int i; try{ i = utils::stoi(s[1]); } catch(const std::invalid_argument &e){ error("invalid NUM"); continue; }
                std::function<bool(const Deriv*)> cmp;
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
                  [&u](const Deriv *p){ return (std::string(p->get_id()) == u); });
                if(it == v.end()){ error("no such username in table"); continue; }
                std::cout << std::endl;
                display(dynamic_cast<const Deriv*>(*it));
                std::cout << std::endl;
                wait();
            }else
            //====RESET=========================================================
            if(s[0] == "reset"){
                if(s.size() != 1) error("wrong number of arguments");
                else              v = filter_users<Base,Deriv,Type>(w, t);
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

void App::list_clients() const{
    std::vector<const User*> v(users_.begin(), users_.end());
    list<User,Client ,User::Type>(v, User::Type::client);
}

void App::list_drivers() const{
    std::vector<const User*> v(users_.begin(), users_.end());
    list<User,Driver ,User::Type>(v, User::Type::driver);
}

void App::list_managers() const{
    std::vector<const User*> v(users_.begin(), users_.end());
    list<User,Manager,User::Type>(v, User::Type::manager);
}

void App::list_trucks() const{
    std::vector<const Truck*> v(trucks_.begin(), trucks_.end());
    list<Truck,Truck,Truck::Type>(v, Truck::Type::truck);
}
