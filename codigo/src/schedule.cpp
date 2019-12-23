#include "schedule.h"

bool Schedule::cmp(const Service *s1, const Service *s2){
    return (s1->get_tbegin() < s2->get_tbegin());
}
Schedule::Schedule():st(Schedule::cmp),valid(true){}
bool Schedule::is_available(const Service *s) const{
    auto it = st.upper_bound(s);
    const Service *s1 = nullptr, *s2 = nullptr;
    if(it != st.end  ()) s2 = *it;
    if(it != st.begin()) s1 = *(--it);
    bool good1 = (s1 == nullptr || s1->get_tend() <= s->get_tbegin());
    bool good2 = (s2 == nullptr || s->get_tend() <= s2->get_tbegin());
    return good1 && good2;
}
void Schedule::add_service(const Service *s){
    valid = valid && is_available(s);
    st.insert(s);
}
Schedule::operator bool() const{ return valid; }
std::ostream& Schedule::print_week(std::ostream &os, const Time &t) const{
    os << "Schedule:\n";
    std::vector<std::string> v = {"          ┌──────────────────────┬──────────────────────┬──────────────────────┬──────────────────────┬──────────────────────┬──────────────────────┬──────────────────────┐",
                                  "          │ Mon                  │ Tue                  │ Wed                  │ Thu                  │ Fri                  │ Sat                  │ Sun                  │",
                                  "┌─────────┼──────────────────────┼──────────────────────┼──────────────────────┼──────────────────────┼──────────────────────┼──────────────────────┼──────────────────────┤"};
    for(int h = 0; h < 24; ++h){
        std::string s1 = utils::itos((h  )%24); if(s1.size() < 2) s1 = "0"+s1;
        std::string s2 = utils::itos((h+1)%24); if(s2.size() < 2) s2 = "0"+s2;
        v.push_back("│ "+s1+"h-"+s2+"h │                      │                      │                      │                      │                      │                      │                      │");
        v.push_back("├─────────┼──────────────────────┼──────────────────────┼──────────────────────┼──────────────────────┼──────────────────────┼──────────────────────┼──────────────────────┤");
    }
    v[v.size()-1] = "└─────────┴──────────────────────┴──────────────────────┴──────────────────────┴──────────────────────┴──────────────────────┴──────────────────────┴──────────────────────┘";
    for(const std::string &s:v) os << s << "\n";
    return os;
}
