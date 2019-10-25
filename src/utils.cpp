#include "utils.h"

string itos(const long long int &i){
    string ret;
    stringstream ss;
    ss << i;
    ss >> ret;
    return ret;
}
