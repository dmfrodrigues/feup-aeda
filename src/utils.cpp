#include "utils.h"

#include <iomanip>
#include <sstream>

std::string utils::itos(const long long int &i){
    std::stringstream ss;
    ss << i;
    return ss.str();
}

std::string utils::strrep(const std::string &s, const std::string &fr, const std::string &to){
    std::string ret = s;
    size_t i;
    do{
        i = ret.find(fr);
        if(i != std::string::npos)
            ret = ret.replace(i, fr.size(), to);
    }while(i != std::string::npos);
    return ret;
}

std::string utils::urlencode(const std::string &s){
    std::ostringstream ss;
    ss.fill('0');
    ss << std::hex;
    for(const char &c:s){
        if(isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            ss << c;
        }else{
            ss << std::uppercase << '%'
               << std::setw(2) << int((unsigned char)c)
               << std::nouppercase;
        }
    }
    return ss.str();
}

std::string utils::urldecode(const std::string &s){
    std::string ret;
    size_t i = 0;
    while(i < s.size()){
        if(s[i] == '%'){
            if(i+2 >= s.size()) return ret;
            std::stringstream ss;
            ss << std::hex << s.substr(i+1,2);
            int a; ss >> a;
            ret += char(a);
            i += 3;
        }else{
            ret += s[i++];
        }
    }
    return ret;
}

///STRING_REGEX
utils::string_regex& utils::string_regex::operator=(const std::string &s){
    if(!std::regex_match(s, std::regex(REGEX_STR_)))
        throw FailedRegex(s, REGEX_STR_);
    s_ = s;
    return *this;
}
namespace utils{
    std::istream& operator>>(std::istream &is,       utils::string_regex &s){
        std::string ss; is >> ss;
        s = ss;
        return is;
    }
    std::ostream& operator<<(std::ostream &os, const utils::string_regex &s){ return (os << s.s_); }
}
utils::string_regex::FailedRegex::FailedRegex(const std::string &s, const std::string &REGEX_STR):
    std::invalid_argument("Invalid string ("+s+") does not match regex ("+REGEX_STR+")"),
    s_(s){}
///INVALID ITERATOR
utils::InvalidIterator::InvalidIterator():
    std::invalid_argument("Invalid iterator (iterator is out of the range)") {}
