/**
 * @file workshop.h
 */

#ifndef WORKSHOP_H_INCLUDED
#define WORKSHOP_H_INCLUDED

#include <string.h>
#include <set.h>

#include "../include/utils.h"

/**
 * @brief Class representing a workshop.
 * @ref Workshop
 */
class Workshop {

public:
    /** @brief %ID class */
    class ID: public utils::string_regex {
    public:
        /// @brief Regex an ID is supposed to match.
        static const std::string ID_STR;
        /// @brief Default constructor.
        explicit ID();
        /// @brief Constructor accepting string as argument for construction.
        explicit ID(const std::string &id);
        /// @brief Overload of \a operator=.
        ID& operator=(const std::string &s);
    };
private:
    /** @brief Workshop display name */
    std::string name_;
    /** @brief Workshop ID */
    std::string id_;
    /** @brief Brands that workshop is specialized */
    std::set<std::string> brands_;
    /** @brief Days until workshop is available */
    int availability_;
protected:
    /**
     * @brief Allows Workshop fields to be filled from input stream.
     * @param   is  Input stream
     */
     std::istream& input(std::istream &is);
public:
    /** @brief Default Constructor. */
    Workshop();
    /** @brief Destructor */
    ~Workshop();

    /// @brief Get workshop name. */
    const std::string&          get_name(void)          const;
    /// @brief Get workshop ID. */
    const std::string&          get_id(void)            const;
    /// @brief Get brands. */
    const std::set<std::string> get_brands(void)        const;
    /// @brief Get workshop availability. */
    int                         get_availability(void)  const;

    /// @brief Overload of \a operator>> .
    friend std::istream& operator>>(std::istream &is,       User &p);
    /// @brief Overload of \a operator<< .
    friend std::ostream& operator<<(std::ostream &os, const User &p);

};

#endif /* end of include guard: WORKSHOP_H_INCLUDED */
