#include "app.h"

template<class Deriv>
std::vector<const Deriv*> App::filter_users(const std::vector<User*> &v, const User::Type &t){
    std::vector<User*> v1 = utils::filter(v, [&t](const User *p){ return (p->get_type() == t); });
    std::vector<const Deriv*> retv = std::vector<const Deriv*>(v1.size());
    std::transform(v1.begin(), v1.end(), retv.begin(), [](const User *p){
        const Deriv *ret = dynamic_cast<const Deriv*>(p);
        if(ret == nullptr) throw std::bad_cast();
        return ret;
    });
    return retv;
}

void App::list_clients_commands(){
    std::cout << "\n"
              << "Commands:\n"
              << "sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0,4].\n"
              << "search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0,4].\n"
              << "reset               Reset to initial selection.\n"
              << "back                Go back.\n";
    std::cout << std::endl;
}

void App::list_managers_commands(){
    std::cout << "\n"
              << "Commands:\n"
              << "sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0,5].\n"
              << "search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0,5].\n"
              << "reset               Reset to initial selection.\n"
              << "back                Go back.\n";
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

template<class T> void App::list_users(const User::Type &t) const{
    std::vector<const T*> v = filter_users<T>(users_, t);
    while(true){
        CLEAR();
        print_list(v);
        list_clients_commands();
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
            //====RESET=========================================================
            if(s[0] == "reset"){
                if(s.size() != 1) error("wrong number of arguments");
                else              v = filter_users<T>(users_, User::Type::client);
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
    list_users<Client>(User::Type::client);
}

void App::list_drivers() const{
    list_users<Driver>(User::Type::driver);
}

void App::list_managers() const{
    list_users<Manager>(User::Type::manager);
}
