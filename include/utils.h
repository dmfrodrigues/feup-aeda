#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <string>
#include <stdexcept>
#include <vector>
#include <regex>

namespace utils{
    template<class T> class ufloat;
}

template<class T> std::istream& operator>>(std::istream &is,       utils::ufloat<T> &u);
template<class T> std::ostream& operator<<(std::ostream &os, const utils::ufloat<T> &u);

/**
 * @brief Utilities
 */
namespace utils {
    /**
     * @brief       Convert integer to string.
     * @param   i   Integer to convert
     * @return      String that resulted from converting \a i.
     */
    std::string itos(const long long int &i);

    /**
     * @brief       Replace all occurences of a string.
     * @param   s   Original string
     * @param   fr  String to be replaced
     * @param   to  String to replace \a fr
     * @return      String with replaced occurences
     */
    std::string strrep(const std::string &s, const std::string &fr, const std::string &to);

    /**
     * @brief       URL-encode string.
     * @param   s   Original string
     * @return      URL-encoded string
     */
     std::string urlencode(const std::string &s);

    /**
     * @brief       URL-decode string.
     * @param   s   URL-encoded string
     * @return      Decoded string
     */
    std::string urldecode(const std::string &s);

    template<class T>
    class ufloat{
    private:
        T u_;
    public:
        explicit ufloat():u_(0){}
        explicit ufloat(const T &u);

        friend std::istream& operator>> <>(std::istream &is,       utils::ufloat<T> &u);
        friend std::ostream& operator<< <>(std::ostream &os, const utils::ufloat<T> &u);

        class InvalidUFloat: public std::invalid_argument{
        private:
            T u_;
        public:
            explicit InvalidUFloat(const T &u);
            const T& get_ufloat() const;
        };
    };

    class string_regex{
    private:
        std::string s_;
        std::string REGEX_STR_;
    public:
        explicit string_regex(const std::string &REGEX_STR):REGEX_STR_(REGEX_STR){}
        string_regex& operator=(const std::string &s);

        explicit operator std::string() const;
        bool operator<(const utils::string_regex &s) const;

        friend std::istream& operator>>(std::istream &is,       utils::string_regex &s);
        friend std::ostream& operator<<(std::ostream &os, const utils::string_regex &s);

        class FailedRegex: public std::invalid_argument{
        private:
            const std::string s_;
            const std::string REGEX_STR_;
        public:
            FailedRegex(const std::string &s, const std::string &REGEX_STR);
            const std::string& get_string()const{ return s_; }
        };
    };

    template<class T, class Compare> void mergesort(std::vector<T> &v, const size_t &l, const size_t &r, Compare comp);
    template<class T, class Compare> void mergesort(std::vector<T> &v, Compare comp){ utils::mergesort(v, 0, v.size(), comp); }
    template<class T               > void mergesort(std::vector<T> &v){ utils::mergesort(v, std::less<T>()); }

    template<class Iterator, class T, class Compare> Iterator linearfind(Iterator l, Iterator r, T obj, Compare comp);
    template<class Iterator, class T               > Iterator linearfind(Iterator l, Iterator r, T obj){ utils::linearfind(l, r, obj, std::equal<T>()); }

    class InvalidIterator : public std::invalid_argument {
    public:
        InvalidIterator();
    };
}

///UFLOAT
template<class T> utils::ufloat<T>::ufloat(const T &u){
    if(u < 0.0)
        throw utils::ufloat<T>::InvalidUFloat(u);
    u_ = u;
}
template<class T> std::istream& operator>>(std::istream &is,       utils::ufloat<T> &u){ return (is >> u.u_); }
template<class T> std::ostream& operator<<(std::ostream &os, const utils::ufloat<T> &u){ return (os << u.u_); }
template<class T> utils::ufloat<T>::InvalidUFloat::InvalidUFloat(const T &u):
    std::invalid_argument("Invalid weight"),
    u_(u){}
template<class T> const T& utils::ufloat<T>::InvalidUFloat::get_ufloat()const{ return u_; }

///MEGESORT
template<class T, class Compare> void utils::mergesort(std::vector<T> &v, const size_t &l, const size_t &r, Compare comp){
    if(r-l <= 1) return;
    size_t m = l + (r-l)/2;
    utils::mergesort(v,l,m,comp); utils::mergesort(v,m,r,comp);
    size_t i = l, j = m;
    std::vector<T> w(r-l);
    size_t k = 0;
    while(i != m && j != r){
        if(comp(v[i],v[j])) w[k++] = v[i++];
        else                w[k++] = v[j++];
    }
    while(i != m) w[k++] = v[i++];
    while(j != r) w[k++] = v[j++];
    std::copy(w.begin(), w.end(), v.begin()+l);
}

template<class Iterator, class T, class Compare> Iterator linearfind(Iterator l, Iterator r, T obj, Compare comp){
    Iterator i = l;
    while(i != r){
        if(*i == obj) break;
        ++i;
    }
    return i;
}

#endif //UTILS_H_INCLUDED
