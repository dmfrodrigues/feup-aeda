#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

using namespace std;

/**
 * Integer to string
 */
string itos(const long long int &i);

/**
 * String to time
 */
chrono::system_clock::time_point stot(string s);

/**
 * Time to string
 */
string ttos(const chrono::system_clock::time_point &tp);

#endif //UTILS_H_INCLUDED
