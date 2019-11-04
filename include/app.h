#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include "person.h"
#include "truck.h"

class App{
private:
    const std::string base_path_;
    const std::string clients_path_;
    const std::string managers_path_;
    const std::string trucks_path_;
    const std::string services_path_;
public:
    App(const std::string &base,
        const std::string &clients, const std::string &managers,
        const std::string &drivers, const std::string &trucks,
        const std::string &services);
};

#endif //APP_H_INCLUDED
