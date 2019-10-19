#include "utils.h"

std::string itos(const long long int &i){
    std::string ret;
    std::stringstream ss;
    ss << i;
    ss >> ret;
    return ret;
}
