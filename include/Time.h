#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

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
     * @brief Constructor accepting date in @ref DEFAULT_FORMAT.
     */
    Time(const std::string &s);

    /**
     * @brief   Overload of <em> operator>> </em>. Expects input in @ref Time::DEFAULT_FORMAT.
     */
    friend std::istream& operator>>(std::istream &is,       Time &t);
    /**
     * @brief   Overload of <em> operator<< </em>. Prints in @ref Time::DEFAULT_FORMAT.
     */
    friend std::ostream& operator<<(std::ostream &os, const Time &t);
};

const std::string Time::DEFAULT_FORMAT = "%Y%m%d_%H%M%S";

#endif //TIME_H_INCLUDED
