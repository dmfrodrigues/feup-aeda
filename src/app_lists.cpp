#include "app.h"

void App::list_clients(){
    //CLEAR();
    std::vector<const Client*> v;{
        std::vector<User*> v1 = utils::filter(users_, [](const User *p){ return (p->get_type() == User::Type::client); });
        v = std::vector<const Client*>(v1.size());
        std::transform(v1.begin(), v1.end(), v.begin(), [](const User *p){ return dynamic_cast<const Client*>(p); });
    }
    while(true){
        CLEAR();
        print_list(v);
        std::cout << "\n"
                  << "Commands:\n"
                  << "sort \033[4mNUM\033[0m            Sort by property \033[4mNUM\033[0m [0,4].\n"
                  << "search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restrict list to elements that contain \033[4mSTR\033[0m in property \033[4mNUM\033[0m [0,4].\n"
                  << "reset               Reset to initial selection.\n"
                  << "back                Go back.\n";
        std::cout << std::endl;
        std::vector<std::string> s = utils::parse_command(prompt());
        if(s.size() >= 1){
            if(s[0] == "sort"){
                if(s.size() != 2){ std::cout << "Error: wrong number of arguments" << std::endl; wait(); continue; }
                int i;
                try{
                    i = std::stoi(s[1]);
                }catch(const std::invalid_argument &e){
                    std::cout << "Error: invalid NUM" << std::endl;
                    wait();
                    continue;
                }
                switch(i){
                case 0: utils::mergesort(v, [](const Client *p1, const Client *p2){ return (p1->get_username   () < p2->get_username   ()); }); break;
                case 1: utils::mergesort(v, [](const Client *p1, const Client *p2){ return (p1->get_name       () < p2->get_name       ()); }); break;
                case 2: utils::mergesort(v, [](const Client *p1, const Client *p2){ return (p1->get_address    () < p2->get_address    ()); }); break;
                case 3: utils::mergesort(v, [](const Client *p1, const Client *p2){ return (p1->get_phonenumber() < p2->get_phonenumber()); }); break;
                case 4: utils::mergesort(v, [](const Client *p1, const Client *p2){ return (p1->get_vat        () < p2->get_vat        ()); }); break;
                default: std::cout << "Error: NUM outside range" << std::endl; wait(); break;
                }
            }else if(s[0] == "search"){
                if(s.size() != 3){ std::cout << "Error: wrong number of arguments" << std::endl; wait(); continue; }
                int i;
                try{
                    i = std::stoi(s[1]);
                }catch(const std::invalid_argument &e){
                    std::cout << "Error: invalid NUM" << std::endl;
                    wait();
                    continue;
                }
                const std::string &str = s[2];
                switch(i){
                case 0: v = utils::filter(v, [&str](const Client *p){ return (std::string(p->get_username()).find(str) != std::string::npos); }); break;
                case 1: v = utils::filter(v, [&str](const Client *p){ return (std::string(p->get_name    ()).find(str) != std::string::npos); }); break;
                case 2: v = utils::filter(v, [&str](const Client *p){ return (p->get_address().format().find(str) != std::string::npos); }); break;
                case 3: v = utils::filter(v, [&str](const Client *p){ return (std::string(p->get_phonenumber()).find(str) != std::string::npos); }); break;
                case 4: v = utils::filter(v, [&str](const Client *p){ return (std::string(p->get_vat()).find(str) != std::string::npos); }); break;
                default: std::cout << "Error: NUM outside range" << std::endl; wait(); break;
                }
            }else if(s[0] == "reset"){
                if(s.size() != 1){ std::cout << "Error: wrong number of arguments" << std::endl; wait(); continue; }
                v = std::vector<const Client*>();
                auto it = users_.begin();
                for(const User* p:users_)
                    if(p->get_type() == User::Type::client)
                        v.push_back(dynamic_cast<const Client*>(p));
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
    //CLEAR();
    std::vector<User*> v1 = utils::filter(users_, [](const User *p){ return (p->get_type() == User::Type::client); });
    std::vector<const Manager*> v(v1.size()); std::transform(v1.begin(), v1.end(), v.begin(), [](const User *p){ return dynamic_cast<const Manager*>(p); });
    print_list(v);
}
