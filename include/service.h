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
    Currency expenses_;
    Currency price_;
public:
    /** @brief ID of next service*/
    static int next_id_;

    /** @brief Empty constructor. */
    Service():expenses_(0), price_(0){}
    /** @brief Destructor */
    ~Service() { delete cargo_; }

    /**
     * @brief Constructor that accepts all the information concerning a transport service.
     * @param   client_user     Pointer to @ref Client to which the service will be provided
     * @param   contact1        @ref Person that should be contacted on loading
     * @param   contact2        @ref Person that should be contacted on arrival and unloading
     * @param   t_begin         @ref Time at which the driver should leave the headquarters
     * @param   t_end           @ref Time at which the driver is expected to reach the headquarters
     * @param   a_begin         @ref Address at which the cargo should be loaded
     * @param   a_end           @ref Address at which the cargo should be unloaded
     * @param   distance        Distance between the two addresses
     * @param   cargo           Pointer to cargo the client wants to be transported
     * @param   expenses        Expenses this service had to the company
     * @param   price           Price the company charged the client for this service
     */
    Service(const Client::Username &client_user, const Person &contact1, const Person &contact2,
            Time t_begin, Time t_end,
            Address a_begin, Address a_end,
            Distance distance, Cargo *cargo,
            Currency expenses, Currency price);

    /**
     * @brief Constructor creates an empty service linked to a specific user.
     * @param   client_user     Pointer to @ref Client to which the service will be provided
     */
    Service(const Client::Username &client_user): client_user_(client_user), expenses_(0), price_(0), id_(utils::itos(next_id_++)){}

    const std::string&      get_id      () const{ return id_         ; }
    /// @brief Get client
    const Client::Username& get_client  () const{ return client_user_; }
    /// @brief Get contact 1
    const Person&           get_contact1() const{ return contact1_   ; }
    /// @brief Get contact 2
    const Person&           get_contact2() const{ return contact2_   ; }
    /// @brief Get time of arrival to loading address
    const Time&             get_tbegin  () const{ return t_begin_    ; }
    /// @brief Get time of arrival to unloading address
    const Time&             get_tend    () const{ return t_end_      ; }
    /// @brief Get loading address
    const Address&          get_abegin  () const{ return a_begin_    ; }
    /// @brief Get unloading address
    const Address&          get_aend    () const{ return a_end_      ; }
    /// @brief Get distance between the two addresses
    const Distance&         get_distance() const{ return distance_   ; }
    /// @brief Get pointer to cargo
    const Cargo*            get_cargo   () const{ return cargo_      ; }
    /// @brief Get trucks assigned to this service
    const std::vector<Truck ::NumberPlate>& get_trucks () const{ return trucks_ ; }
    /// @brief Get drivers assigned to this service
    const std::vector<Driver::Username   >& get_drivers() const{ return drivers_; }
    /// @brief Get expenses of making this service
    const Currency& get_expenses() const { return expenses_; };
    /// @brief Get price charged to the client for this service
    const Currency& get_price   () const { return price_   ; };
    /**
     * @brief Allocate service to the necessary number of trucks and drivers
     */
    bool allocate(std::vector<const Truck*> tv, std::vector<const Driver*> dv);

    /** @brief Overload of <em> operator>> </em>. */
    friend std::istream& operator>>(std::istream &is,       Service &s);
    /** @brief Overload of <em> operator<< </em>. */
    friend std::ostream& operator<<(std::ostream &os, const Service &s);

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    bool in(std::istream &is, std::ostream &os);
};

#endif //SERVICE_H_INCLUDED
