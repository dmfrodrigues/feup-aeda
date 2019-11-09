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

void App::list_clients_sort(std::vector<const Client*> &v, const std::vector<std::string> &s){
    if(s.size() != 2){ std::cout << "Error: wrong number of arguments" << std::endl; wait(); return; }
    int i; try{ i = utils::stoi(s[1]); } catch(const std::invalid_argument &e){ std::cout << "Error: invalid NUM" << std::endl; wait(); return; }
    switch(i){
    case 0: utils::mergesort(v, [](const Client *p1, const Client *p2){ return (p1->get_username   () < p2->get_username   ()); }); break;
    case 1: utils::mergesort(v, [](const Client *p1, const Client *p2){ return (p1->get_name       () < p2->get_name       ()); }); break;
    case 2: utils::mergesort(v, [](const Client *p1, const Client *p2){ return (p1->get_address    () < p2->get_address    ()); }); break;
    case 3: utils::mergesort(v, [](const Client *p1, const Client *p2){ return (p1->get_phonenumber() < p2->get_phonenumber()); }); break;
    case 4: utils::mergesort(v, [](const Client *p1, const Client *p2){ return (p1->get_vat        () < p2->get_vat        ()); }); break;
    default: std::cout << "Error: NUM outside range" << std::endl; wait(); break;
    }
}

void App::list_managers_sort(std::vector<const Manager*> &v, const std::vector<std::string> &s){
    if(s.size() != 2){ std::cout << "Error: wrong number of arguments" << std::endl; wait(); return; }
    int i; try{ i = utils::stoi(s[1]); } catch(const std::invalid_argument &e){ std::cout << "Error: invalid NUM" << std::endl; wait(); return; }
    switch(i){
    case 0: utils::mergesort(v, [](const Manager *p1, const Manager *p2){ return (p1->get_username   () < p2->get_username   ()); }); break;
    case 1: utils::mergesort(v, [](const Manager *p1, const Manager *p2){ return (p1->get_name       () < p2->get_name       ()); }); break;
    case 2: utils::mergesort(v, [](const Manager *p1, const Manager *p2){ return (p1->get_address    () < p2->get_address    ()); }); break;
    case 3: utils::mergesort(v, [](const Manager *p1, const Manager *p2){ return (p1->get_phonenumber() < p2->get_phonenumber()); }); break;
    case 4: utils::mergesort(v, [](const Manager *p1, const Manager *p2){ return (p1->get_vat        () < p2->get_vat        ()); }); break;
    case 5: utils::mergesort(v, [](const Manager *p1, const Manager *p2){ return (p1->get_base_salary() < p2->get_base_salary()); }); break;
    default: std::cout << "Error: NUM outside range" << std::endl; wait(); break;
    }
}

void App::list_clients_search(std::vector<const Client*> &v, const std::vector<std::string> &s){
    if(s.size() != 3){ std::cout << "Error: wrong number of arguments" << std::endl; wait(); return; }
    int i; try{ i = utils::stoi(s[1]); } catch(const std::invalid_argument &e){ std::cout << "Error: invalid NUM" << std::endl; wait(); return; }
    const std::string &str = s[2];
    std::function<bool(const Client*)> cmp;
    switch(i){
    case 0: cmp = [&str](const Client *p){ return (std::string(p->get_username   ()).find(str) != std::string::npos); }; break;
    case 1: cmp = [&str](const Client *p){ return (std::string(p->get_name       ()).find(str) != std::string::npos); }; break;
    case 2: cmp = [&str](const Client *p){ return (p->get_address().format()        .find(str) != std::string::npos); }; break;
    case 3: cmp = [&str](const Client *p){ return (std::string(p->get_phonenumber()).find(str) != std::string::npos); }; break;
    case 4: cmp = [&str](const Client *p){ return (std::string(p->get_vat        ()).find(str) != std::string::npos); }; break;
    default: std::cout << "Error: NUM outside range" << std::endl; wait(); return;
    }
    v = utils::filter(v,cmp);
}

void App::list_managers_search(std::vector<const Manager*> &v, const std::vector<std::string> &s){
    if(s.size() != 3){ std::cout << "Error: wrong number of arguments" << std::endl; wait(); return; }
    int i; try{ i = utils::stoi(s[1]); } catch(const std::invalid_argument &e){ std::cout << "Error: invalid NUM" << std::endl; wait(); return; }
    const std::string &str = s[2];
    std::function<bool(const Manager*)> cmp;
    switch(i){
    case 0: cmp = [&str](const Manager *p){ return (std::string(p->get_username   ()).find(str) != std::string::npos); }; break;
    case 1: cmp = [&str](const Manager *p){ return (std::string(p->get_name       ()).find(str) != std::string::npos); }; break;
    case 2: cmp = [&str](const Manager *p){ return (p->get_address().format()        .find(str) != std::string::npos); }; break;
    case 3: cmp = [&str](const Manager *p){ return (std::string(p->get_phonenumber()).find(str) != std::string::npos); }; break;
    case 4: cmp = [&str](const Manager *p){ return (std::string(p->get_vat        ()).find(str) != std::string::npos); }; break;
    case 5: cmp = [&str](const Manager *p){ return (Currency(std::stod(str))                    ==p->get_base_salary());};break;
    default: std::cout << "Error: NUM outside range" << std::endl; wait(); break;
    }
    v = utils::filter(v,cmp);
}

void App::list_clients() const{
    std::vector<const Client*> v = filter_users<Client>(users_, User::Type::client);
    while(true){
        CLEAR();
        print_list(v);
        list_clients_commands();
        std::vector<std::string> s = utils::parse_command(prompt());
        if(s.size() >= 1){
            if(s[0] == "sort"){
                list_clients_sort(v, s);
            }else if(s[0] == "search"){
                list_clients_search(v, s);
            }else if(s[0] == "reset"){
                if(s.size() != 1){ std::cout << "Error: wrong number of arguments" << std::endl; wait(); continue; }
                std::vector<User*> v1 = utils::filter(users_, [](const User *p){ return (p->get_type() == User::Type::client); });
                v = std::vector<const Client*>(v1.size());
                std::transform(v1.begin(), v1.end(), v.begin(), [](const User *p){
                    const Client *ret = dynamic_cast<const Client*>(p);
                    if(ret == nullptr) throw std::bad_cast();
                    return ret;
                });
            }else if(s[0] == "back"){
                if(s.size() != 1){ std::cout << "Error: wrong number of arguments" << std::endl; wait(); continue; }
                return;
            }else{
                std::cout << "Error: unrecognized command" << std::endl; wait();
            }
        }
    }
}

void App::list_managers(){
    std::vector<const Manager*> v = filter_users<Manager>(users_, User::Type::manager);
    while(true){
        CLEAR();
        print_list(v);
        list_managers_commands();
        std::vector<std::string> s = utils::parse_command(prompt());
        if(s.size() >= 1){
            if(s[0] == "sort"){
                list_managers_sort(v, s);
            }else if(s[0] == "search"){
                list_managers_search(v,s);
            }else if(s[0] == "reset"){
                if(s.size() != 1){ std::cout << "Error: wrong number of arguments" << std::endl; wait(); continue; }
                std::vector<User*> v1 = utils::filter(users_, [](const User *p){ return (p->get_type() == User::Type::manager); });
                v = std::vector<const Manager*>(v1.size());
                std::transform(v1.begin(), v1.end(), v.begin(), [](const User *p){
                    const Manager *ret = dynamic_cast<const Manager*>(p);
                    if(ret == nullptr) throw std::bad_cast();
                    return ret;
                });
            }else if(s[0] == "back"){
                if(s.size() != 1){ std::cout << "Error: wrong number of arguments" << std::endl; wait(); continue; }
                return;
            }else{
                std::cout << "Error: unrecognized command" << std::endl; wait();
            }
        }
    }
}
