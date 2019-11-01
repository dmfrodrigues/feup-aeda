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
    /**
     * @brief   Overload of <em> operator>> </em>. Expects input in @ref Time::DEFAULT_FORMAT.
     */
    friend std::istream& operator>>(std::istream &is,       Time &t);
    /**
     * @brief   Overload of <em> operator<< </em>. Prints in @ref Time::DEFAULT_FORMAT.
     */
    friend std::ostream& operator<<(std::ostream &os, const Time &t);

    class InvalidTimeFormat: public std::invalid_argument{
    private:
        std::string fmt_;
    public:
        InvalidTimeFormat(const std::string &fmt);
        const std::string& get_format() const;
    };
};

const std::string Time::DEFAULT_FORMAT = "%Y%m%d_%H%M%S";
const std::string Time::DEFAULT_TIME   = "00000000_000000";

#endif //TIME_H_INCLUDED
