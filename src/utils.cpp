#include "utils.h"

std::string itos(const long long int &i){
    std::stringstream ss;
    ss << i;
    return ss.str();
}

std::string strrep(const std::string &s, const std::string &fr, const std::string &to){
    std::string ret = s;
    size_t i;
    do{
        i = ret.find(fr);
        if(i != std::string::npos)
            ret = ret.replace(i, fr.size(), to);
    }while(i != std::string::npos);
    return ret;
}
