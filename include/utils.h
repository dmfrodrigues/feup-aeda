#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

/**
 * Integer to string
 */
std::string itos(const long long int &i);

/**
 * String to time
 */
std::chrono::system_clock::time_point stot(const std::string &s);

/**
 * Time to string
 */
std::string ttos(const std::chrono::system_clock::time_point &tp);

#endif //UTILS_H_INCLUDED
