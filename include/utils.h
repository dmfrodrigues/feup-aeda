#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <string>
#include <stdexcept>

/**
 * @brief Utilities
 */
namespace utils {
    /**
     * @brief       Convert integer to string.
     * @param   i   Integer to convert
     * @return      String that resulted from converting \a i.
     */
    std::string itos(const long long int &i);

    /**
     * @brief       Replace all occurences of a string.
     * @param   s   Original string
     * @param   fr  String to be replaced
     * @param   to  String to replace \a fr.
     */
    std::string strrep(const std::string &s, const std::string &fr, const std::string &to);

    class InvalidIterator : public std::invalid_argument {
    public:
        InvalidIterator();
    };
}

#endif //UTILS_H_INCLUDED
