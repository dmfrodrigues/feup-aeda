#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED

template<class T>
class Calendar{
private:
    Time t;
    std::vector<T> info;
public:
    Calendar(const Time &t_):t(t_){}
    void set_info(const std::vector<T> &v){ info = v; }
    std::ostream& draw(std::ostream &os) const{
        std::cout << "Calendar\n";
        
        return os;
    }
};

#endif //CALENDAR_H_INCLUDED
