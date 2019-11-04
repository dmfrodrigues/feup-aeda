#include "app.h"

App::App(const std::string &base      ,
         const std::string &managers  , const std::string &drivers ,
         const std::string &clients   ,
         const std::string &trucks    , const std::string &services):
         managers_path_(base+managers), drivers_path_ (base+drivers ),
         clients_path_ (base+clients ),
         trucks_path_  (base+trucks  ), services_path_(base+services){
    load_managers(managers_path_);
}

std::map<std::string, Manager> App::load_managers(const std::string &managers_path){

    return std::map<std::string, Manager>();
}

void App::start(){

}
