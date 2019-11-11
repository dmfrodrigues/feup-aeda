/**
 * @file person.h
 */

#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include "address.h"
#include "vat.h"
#include "phonenumber.h"
#include "currency.h"

/**
 * @brief %Person class.
 */
class Person {
private:
    std::string name_;
    PhoneNumber phonenumber_;
protected:
    /**
     * @brief Allows Person fields to be filled from info in input stream.
     * @param   is  Input stream
     */
    virtual std::istream& input(std::istream &is);
public:
    /** @brief Empty constructor */
    Person(){}
    /**
     * @brief Constructor accepting a name and a phone number.
     * @param   name        String containing name of person
     * @param   phonenumber Phone number
     */
    Person(const std::string &name, const PhoneNumber &phonenumber);

    virtual ~Person(){}

    virtual const std::string& get_name() const final{ return name_; }
    virtual const PhoneNumber& get_phonenumber() const final{ return phonenumber_; }

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);

    /** @brief Overload of <em> operator>> </em>. */
    friend std::istream& operator>>(std::istream &is,       Person &p);
    /** @brief Overload of <em> operator<< </em>. */
    friend std::ostream& operator<<(std::ostream &os, const Person &p);
};

/**
 * @brief %User class.
 *
 * A user must have his/her own credentials to login to the system.
 */
class User : public Person{
public:
    /** @brief %Username class. */
    class Username: public utils::string_regex{
    public:
        static const std::string REGEX_STR;
        explicit Username();
        explicit Username(const std::string &username);
        Username& operator=(const std::string &s);
    };
    class Password: public utils::string_regex{
    public:
        static const std::string REGEX_STR;
        explicit Password();
        explicit Password(const std::string &password);
        Password& operator=(const std::string &s);
    };

    /** @brief Type of users there are. */
    enum Type {
        client,
        driver,
        manager
    };
private:
    Username username_;
    Password password_;
    Address address_;
    VAT vat_;
protected:
    /**
     * @brief Allows User fields to be filled from info in input stream.
     * @param   is  Input stream
     */
    virtual std::istream& input(std::istream &is);
public:
    /** @brief Empty constructor */
    User():Person(){}
    /**
     * @brief Constructor accepting a name, a phone number and credentials.
     * @param   name        String containing name of user
     * @param   phonenumber Phone number
     * @param   username    Unique username in the program
     * @param   pswd        Password of the user
     */
    User(const std::string &name    , const PhoneNumber &phonenumber,
         const Username    &username, const Password    &password   ,
         const Address     &address , const VAT         &vat        );

    /** @brief Get username */
    const Username& get_username() const{ return username_     ; }
    const Username& get_id      () const{ return get_username(); }
    const Address&  get_address () const{ return address_      ; }
    const VAT&      get_vat     () const{ return vat_          ; }
    /**
     * @brief Gets the type of user.
     * @return User type
     */
    virtual User::Type get_type(void) const = 0;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);

    /**
     * @brief Tests if credentials given match with user.
     * @param username Username to verify
     * @param password Password to verify
     * @return If the credentials are valid
     */
    bool verifyCredentials(const std::string &password);

    /** @brief Overload of <em> operator>> </em>. */
    friend std::istream& operator>>(std::istream &is,       User &p);
    /** @brief Overload of <em> operator<< </em>. */
    friend std::ostream& operator<<(std::ostream &os, const User &p);
};

/**
 * @brief %Client class.
 *
 * A client is a user with privileges to request new services.
 * In order to issue bills, a client must have an Address and a VAT number.
 */
class Client: public User {
protected:
    /**
     * @brief Allows Client fields to be filled from info in input stream.
     * @param   is  Input stream
     */
    virtual std::istream& input(std::istream &is);
public:
    /** @brief Empty constructor */
    Client():User(){}
    /**
     * @brief Constructor accepting all information to construct a client.
     * @param   name        String containing name of client
     * @param   phonenumber Phone number
     * @param   user        Unique username in the program
     * @param   pswd        Password of the client
     * @param   address     Billing address of the client
     * @param   vat         VAT number of the client for billing purposes
     */
    Client(const std::string &name   , const PhoneNumber &phonenumber,
           const Username    &user   , const Password    &password   ,
           const Address     &address, const VAT         &vat        );

    /**
     * @brief Gets the type of user.
     * @return UserType::client type
     */
    virtual User::Type get_type(void) const;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);

    /** @brief Overload of <em> operator>> </em>. */
    friend std::istream& operator>>(std::istream &is,       Client &p);
    /** @brief Overload of <em> operator<< </em>. */
    friend std::ostream& operator<<(std::ostream &os, const Client &p);
};

/**
 * @brief %Employee class.
 *
 * An employee is a User that is paid by the company.
 */
class Employee: public User {
private:
    Currency base_salary_;
protected:
    virtual std::istream& input(std::istream &is);
public:
    /** @brief Empty constructor */
    Employee():User(){}
    /**
     * @brief Constructor accepting all information to construct an employee.
     * @param   name        String containing name of employee
     * @param   phonenumber Phone number
     * @param   user        Unique username in the program
     * @param   pswd        Password of the client
     * @param   base_salary Base salary of the employee
     */
    Employee(const std::string &name       , const PhoneNumber &phonenumber,
             const Username    &user       , const Password    &password   ,
             const Address     &address    , const VAT      &vat           ,
             const Currency    &base_salary);

    Currency get_base_salary() const{ return base_salary_; }

    /**
     * @brief Gets the type of user.
     * @return User type
     */
    virtual User::Type get_type(void) const = 0;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);


    /** @brief Overload of <em> operator>> </em>. */
    friend std::istream& operator>>(std::istream &is,       Employee &p);
    /** @brief Overload of <em> operator<< </em>. */
    friend std::ostream& operator<<(std::ostream &os, const Employee &p);
};

/**
 * @brief %Manager class.
 *
 * A manager has permissions to make any modification to data in the program.
 */
class Manager: public Employee {
protected:
    virtual std::istream& input(std::istream &is);
public:
    /** @brief Empty constructor */
    Manager():Employee(){}
    /**
     * @brief Constructor accepting all information to construct a manager.
     * @param   name        String containing name of manager
     * @param   phonenumber Phone number
     * @param   user        Unique username in the program
     * @param   pswd        Password of the manager
     * @param   base_salary Base salary of the manager
     */
    Manager(const std::string &name       , const PhoneNumber &phonenumber,
            const Username    &user       , const Password    &password   ,
            const Address     &address    , const VAT      &vat           ,
            const Currency    &base_salary);

    /**
     * @brief Gets the type of user.
     * @return UserType::manager type
     */
    virtual User::Type get_type(void) const;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);

    /** @brief Overload of <em> operator>> </em>. */
    friend std::istream& operator>>(std::istream &is,       Manager &p);
    /** @brief Overload of <em> operator<< </em>. */
    friend std::ostream& operator<<(std::ostream &os, const Manager &p);
};

/**
 * @brief %Driver class.
 *
 * A driver makes deliveries.
 */
class Driver: public Employee {
protected:
    virtual std::istream& input(std::istream &is);
public:
    /** @brief Empty constructor */
    Driver():Employee(){}
    /**
     * @brief Constructor accepting all information to construct a driver.
     * @param   name        String containing name of driver
     * @param   phonenumber Phone number
     * @param   user        Unique username in the program
     * @param   pswd        Password of the driver
     * @param   base_salary Base salary of the driver
     */
    Driver(const std::string &name       , const PhoneNumber &phonenumber,
           const Username    &user       , const Password    &password   ,
           const Address     &address    , const VAT      &vat           ,
           const Currency    &base_salary);

    /**
     * @brief Gets the type of user.
     * @return UserType::driver type
     */
    virtual User::Type get_type(void) const;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);


    /** @brief Overload of <em> operator>> </em>. */
    friend std::istream& operator>>(std::istream &is,       Driver &p);
    /** @brief Overload of <em> operator<< </em>. */
    friend std::ostream& operator<<(std::ostream &os, const Driver &p);
};

#endif //PERSON_H_INCLUDED
