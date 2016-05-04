#include <iostream>
#include <sstream>
#include <string>
template <typename T>
std::string debug_rep(const T &);
template <typename T>
std::string debug_rep(T *);
template <typename T>
std::string debug_rep(const T &t)
{
    std::ostringstream oss;
    oss << t;
    return oss.str();
}
template <typename T>
std::string debug_rep(T *p)
{
    std::ostringstream oss;
    std::cout << "pointer: " << p;
    if (p)
        oss << " " << debug_rep(*p);
    else
        oss << "null pointer";
    return oss.str();
}
template<>
std::string debug_rep(const char *ch){
    return debug_rep(std::string(ch));
}
template<>
std::string debug_rep(char *ch){
    return debug_rep(std::string(ch));
}
std::string debug_rep(const char *p){
    std::cout << "chongzai const char *" << std::endl;
    return debug_rep(std::string(p));
}
std::string debug_rep(char *p){
    return debug_rep(std::string(p));
}
int main()
{
    std::string str("helllo");
    std::cout << debug_rep("helllo") << std::endl;
    return 0;
}
