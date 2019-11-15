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
public:
    /** @brief ID type */
    typedef std::string ID;
private:
    ID id_;
    Client::Username client_user_;
    Person contact1_;
    Person contact2_;
    Time t_begin_;
    Time t_end_;
    Address a_begin_;
    Address a_end_;
    Distance distance_;
    Cargo *cargo_ = NULL;
    std::vector<Truck ::NumberPlate> trucks_;
    std::vector<Driver::Username   > drivers_;
    Currency cost_;
    Currency revenue_;
public:
    /** @brief ID of next service*/
    static int next_id_;

    /** @brief Empty constructor. */
    Service();
    /**
     * @brief Constructor creates an empty service linked to a specific user.
     * @param   client_user     Pointer to @ref Client to which the service will be provided
     */
    Service(const Client::Username &client_user);
    /** @brief Destructor */
    ~Service();

    /// @brief Get ID
    const std::string&      get_id      () const;
    /// @brief Get client
    const Client::Username& get_client  () const;
    /// @brief Get contact 1
    const Person&           get_contact1() const;
    /// @brief Get contact 2
    const Person&           get_contact2() const;
    /// @brief Get time of arrival to loading address
    const Time&             get_tbegin  () const;
    /// @brief Get time of arrival to unloading address
    const Time&             get_tend    () const;
    /// @brief Get loading address
    const Address&          get_abegin  () const;
    /// @brief Get unloading address
    const Address&          get_aend    () const;
    /// @brief Get distance between the two addresses
    const Distance&         get_distance() const;
    /// @brief Get pointer to cargo
    const Cargo*            get_cargo   () const;
    /// @brief Get trucks assigned to this service
    const std::vector<Truck ::NumberPlate>& get_trucks () const;
    /// @brief Get drivers assigned to this service
    const std::vector<Driver::Username   >& get_drivers() const;
    /// @brief Get cost of making this service
    const Currency& get_cost   () const;
    /// @brief Get revenue from this service
    const Currency& get_revenue() const;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allocate service to the necessary number of trucks and drivers
     */
    bool allocate(std::vector<const Truck*> tv, std::vector<const Driver*> dv);

    /** @brief Overload of <em> operator>> </em>. */
    friend std::istream& operator>>(std::istream &is,       Service &s);
    /** @brief Overload of <em> operator<< </em>. */
    friend std::ostream& operator<<(std::ostream &os, const Service &s);
};

#endif //SERVICE_H_INCLUDED
