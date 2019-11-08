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
    std::map<Manager ::Username, Manager> managers_;
    std::map<Driver  ::Username, Driver > drivers_ ;
    std::map<Client  ::Username, Client > clients_ ;
    std::map<Truck::NumberPlate, Truck *> trucks_  ;
    std::map<std::string, Service> services_;
    ///PRIVATE FUNCTIONS
    ///Load & save functions
    template<class ID, class T> static void load    (std::ifstream &is,       std::map<ID, T > &m_in);
    template<class ID, class T> static void load_ptr(std::ifstream &is,       std::map<ID, T*> &m_in);
    template<class ID, class T> static void save    (std::ofstream &os, const std::map<ID, T > &m_out);
    template<class ID, class T> static void save_ptr(std::ofstream &os, const std::map<ID, T*> &m_out);
    void load_all();
    void save_all();
    ///Operations
    void request_service();

    User* verifyUser(const std::string &username, const std::string &password);
public:
    App(const std::string &base    ,
        const std::string &managers, const std::string &drivers ,
        const std::string &clients ,
        const std::string &trucks  , const std::string &services);

    bool guestMenu(User *user);

    bool userMenu(User *user);

    void start();

    class InvalidCredentials: public std::runtime_error {
    private:
        std::string msg_;
    public:
        InvalidCredentials(const std::string &msg);
        const std::string& getMsg() const;
    };

    class RepeatedId: public std::runtime_error {
    private:
        std::string id_;
    public:
        RepeatedId(const std::string &id);
        const std::string& get_id() const;
    };
};

#endif //APP_H_INCLUDED
