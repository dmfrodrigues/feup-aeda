/**
 * @file service.h
 */

#ifndef SERVICE_H_INCLUDED
#define SERVICE_H_INCLUDED

#include <vector>

#include "person.h"
#include "Time.h"
#include "cargo.h"
#include "truck.h"

/**
 * @brief Class to store all the information concerning a transport service.
 */
class Service{
private:
    std::string id_;
    Client::Username client_user_;
    Person contact1_;
    Person contact2_;
    Time t_begin_;
    Time t_end_;
    Address a_begin_;
    Address a_end_;
    Cargo *cargo_;
    std::vector<Truck::NumberPlate> trucks_;
public:
    static int next_id_;

    Service(){}

    /**
     * @brief Constructor that accepts all the information concerning a transport service.
     * @param   client_user     Pointer to @ref Client to which the service will be provided
     * @param   contact1        @ref Person that should be contacted on loading
     * @param   contact2        @ref Person that should be contacted on arrival and unloading
     * @param   t_begin         @ref Time at which the driver should leave the headquarters
     * @param   t_end           @ref Time at which the driver is expected to reach the headquarters
     * @param   a_begin         @ref Address at which the cargo should be loaded
     * @param   a_end           @ref Address at which the cargo should be unloaded
     */
    Service(const Client::Username &client_user, const Person &contact1, const Person &contact2,
            Time t_begin, Time t_end,
            Address a_begin, Address a_end,
            Cargo *cargo);

    const std::string& get_id()const{ return id_; }

    /** @brief Overload of <em> operator>> </em>. */
    friend std::istream& operator>>(std::istream &is,       Service &s);
    /** @brief Overload of <em> operator<< </em>. */
    friend std::ostream& operator<<(std::ostream &os, const Service &s);
};

#endif //SERVICE_H_INCLUDED
