/**
 * @file Time.h
 */

#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <string>
#include <stdexcept>
#include <ctime>

/**
 * @brief Encapsulate time in a simple class with a few methods
 */
class Time {
private:
    std::tm t_;
public:
    /**
     * @brief Default date format
     */
    static const std::string DEFAULT_FORMAT;
    /**
     * @brief Default time/date if none is set
     */
    static const std::string DEFAULT_TIME;
    /**
     * @brief Constructor accepting date in @ref DEFAULT_FORMAT.
     */
    Time(const std::string &s = DEFAULT_TIME);

    /**
     * @brief Format date with format string.
     * @param   fmt Format string
     * @return  string with formatted date
     */
    std::string format(const std::string &fmt = Time::DEFAULT_FORMAT) const;
    /** @brief   Overload of <em> operator>> </em>. Expects input in @ref Time::DEFAULT_FORMAT. */
    friend std::istream& operator>>(std::istream &is,       Time &t);
    /** @brief   Overload of <em> operator<< </em>. Prints in @ref Time::DEFAULT_FORMAT. */
    friend std::ostream& operator<<(std::ostream &os, const Time &t);

    /**
     * @brief   Class for denoting an invalid time format
     */
    class InvalidTimeFormat: public std::invalid_argument{
    private:
        std::string fmt_;
    public:
        /**
         * @brief Constructor accepting the time format that caused the exception.
         *
         * Also sets the string returned by <em> std::exception::what() </em>.
         * @param   fmt     Time format
         */
        InvalidTimeFormat(const std::string &fmt);
        /**
         * @brief   Get time format from which the exception was constructed.
         * @return  Time format
         */
        const std::string& get_format() const;
    };
};

#endif //TIME_H_INCLUDED
