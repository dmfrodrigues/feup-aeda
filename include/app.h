#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include "person.h"
#include "truck.h"
#include "service.h"

#include <fstream>

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
    template<class T> static std::map<std::string, T > load    (const std::string &path);
    template<class T> static std::map<std::string, T*> load_ptr(const std::string &path);
    template<class T> static void save(const std::string &managers_path, const std::map<std::string, T> &m);
public:
    App(const std::string &base    ,
        const std::string &managers, const std::string &drivers ,
        const std::string &clients ,
        const std::string &trucks  , const std::string &services);

    bool guestMenu(User *user);

    bool userMenu(User *user);

    void start();

    bool save_all();

    class RepeatedName: public std::runtime_error {
    private:
        std::string name_;
    public:
        RepeatedName(const std::string &name);
        const std::string& get_name() const;
    };
};

#endif //APP_H_INCLUDED
