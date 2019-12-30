#include "workshop.h"

//ID
const std::string Workshop::ID::ID_STR = "^\\w*$";
Workshop::ID::ID(): string_regex(Workshop::ID::ID_STR) {}
Workshop::ID::ID(const std::string &id): ID() {
    *this = id;
}
ID& Workshop::ID::operator=(const std::string &s) {
    string_regex::operator=(s);
    return *this;
}

//Workshop
std::istream & Workshop::input(std::istream &is) {
    std::string s; is >> s;
    try {
        name_ = utils::urldecode(s);
    } catch (...) {
        is.setstate(std::ios::failbit);
    }
    is >> id_;
    int no_brands = 0;
    is >> no_brands;
    for (int i = 0; i < no_brands; i++) {
        std::string brand;
        is >> s;
        try {
            brand = utils::urldecode(s);
            brands_.insert(brand);
        } catch (...) {
            is.setstate(std::ios::failbit);
        }
    }
    is >> availability_;
    return is;
}

Workshop::Workshop() {}
Workshop::~Workshop() {}

const std::string&      Workshop::get_name()            const { return name_; }
const std::string&      Workshop::get_id()              const { return id_; }
const std::set<string> Workshop::get_brands()           const { return brands_; }
int                     Workshop::get_availability()    const { return availability_; }

std::istream& operator>>(std::istream &is,       Workshop &w){ return w.input(is); }
std::ostream& operator<<(std::ostream &os, const Workshop &w){
    os << utils::urlencode(w.name_) << "\n"
       << w.id_                     << "\n"
       << w.brands_.size()          << "\n";
    for (auto it = w.brands_.begin(); it != w.brands_.end(); it++)
        os << utils::urlencode(*it) << "\n";
    os << w.availability_;
    return os;
}
