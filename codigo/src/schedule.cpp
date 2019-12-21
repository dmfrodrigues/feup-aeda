#include "schedule.h"

bool Schedule::cmp(const Service *s1, const Service *s2){
    return (s1->get_tbegin() < s2->get_tbegin());
}
Schedule::Schedule():st(Schedule::cmp){}
bool Schedule::is_available(const Service *s) const{
    auto it = st.upper_bound(s);
    const Service *s1 = nullptr, *s2 = nullptr;
    if(it != st.end  ()) s2 = *it;
    if(it != st.begin()) s1 = *(--it);
    bool good1 = (s1 == nullptr || s1->get_tend() <= s->get_tbegin());
    bool good2 = (s2 == nullptr || s->get_tend() <= s2->get_tbegin());
    return good1 && good2;
}
bool Schedule::add_service(const Service *s){
    if(is_available(s)){
        st.insert(s);
        return true;
    }else return false;
}
