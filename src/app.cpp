#include "app.h"

template<class T>
std::map<std::string, T> App::load(const std::string &path){
    std::ifstream is(path);
    is.exceptions(std::ifstream::eofbit | std::ifstream::badbit | std::ifstream::failbit);
    size_t N; is >> N;
    std::map<std::string, T> ret;
    while(N--){
        T m; is >> m;
        ret[m.get_name()] = m;
    }
    return ret;
}

template<class T>
void App::save(const std::string &path, const std::map<std::string, T> &m){
    std::ofstream os(path);
    os.exceptions(std::ifstream::eofbit | std::ifstream::badbit | std::ifstream::failbit);
    os << m.size() << "\n";
    for(const std::pair<std::string, T> &p:m){
        os << p.second << "\n";
    }
}

App::App(const std::string &base      ,
         const std::string &managers  , const std::string &drivers ,
         const std::string &clients   ,
         const std::string &trucks    , const std::string &services):
         managers_path_(base+managers), drivers_path_ (base+drivers ),
         clients_path_ (base+clients ),
         trucks_path_  (base+trucks  ), services_path_(base+services){
    managers_ = load<Manager>(managers_path_);
    save(managers_path_, managers_);
}

void App::start(){

}
