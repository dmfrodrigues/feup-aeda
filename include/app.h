#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include "person.h"
#include "truck.h"
#include "service.h"

class App{
private:
    ///PRIVATE VARIABLES
    //Paths
    const std::string base_path_    ;
    const std::string managers_path_;
    const std::string drivers_path_ ;
    const std::string clients_path_ ;
    const std::string trucks_path_  ;
    const std::string services_path_;
    //Vectors
    std::map<std::string, Manager> managers_;
    std::map<std::string, Driver > drivers_ ;
    std::map<std::string, Client > clients_ ;
    std::map<std::string, Truck *> trucks_  ;
    std::map<std::string, Service> services_;
    ///PRIVATE FUNCTIONS
    std::map<std::string, Manager> load_managers(const std::string &managers_path);
public:
    App(const std::string &base    ,
        const std::string &managers, const std::string &drivers ,
        const std::string &clients ,
        const std::string &trucks  , const std::string &services);
    void start();
};

#endif //APP_H_INCLUDED
