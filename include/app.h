#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include "person.h"
#include "truck.h"
#include "service.h"

#include <fstream>

#if defined(_WIN32)
    #define CLEAR_MACRO() system("cls"  )
#elif defined(unix) || defined(__unix__) || defined(__unix)
    #define CLEAR_MACRO() system("clear")
#endif

void CLEAR();

class App{
private:
    ///PRIVATE VARIABLES
    //Static const
    // Command string
    static const std::string OPSTR;
    //Paths
    const std::string base_path_    ;
    const std::string managers_path_;
    const std::string drivers_path_ ;
    const std::string clients_path_ ;
    const std::string trucks_path_  ;
    const std::string services_path_;
    //Vectors
    std::vector<User*> users_ ;
    std::vector<Truck*> trucks_  ;
    std::vector<Service*> services_;
    ///PRIVATE FUNCTIONS
    ///IO
    template<class Base, class Deriv, class ID> static size_t load_ptr(std::ifstream &is,       std::vector<Base*> &m_in );
    template<class Base, class Deriv          > static size_t save_ptr(std::ofstream &os, const std::vector<Base*> &m_out);
    void load_all();
    void save_all();
    ///Display
    void print_list(const std::vector<const Manager*> &v) const;
    void print_list(const std::vector<const Driver *> &v) const;
    void print_list(const std::vector<const Client *> &v) const;
    template<class Deriv> static std::vector<const Deriv*> filter_users(const std::vector<User*> &v, const User::Type &t);
    void display(const Manager *p) const;
    void display(const Driver  *p) const;
    void display(const Client  *p) const;
    ///Operations
    std::string prompt() const;
    void wait() const;
    void request_service();

    std::vector<User*> filter_user_by_type(const std::vector<User*> &v, const User::Type &t);
    void list_clients () const;
    static void list_clients_commands();
    void list_managers();
    static void list_managers_commands();

    const std::vector<User*>::iterator find_user(const User::Username &u);

    User* verifyUser(const std::string &username, const std::string &password);
public:
    App(const std::string &base    ,
        const std::string &managers, const std::string &drivers ,
        const std::string &clients ,
        const std::string &trucks  , const std::string &services);

    bool guestMenu(User *user);

    bool userMenu(const User* const user);

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
