#include <iostream>
#include <sstream>
#include <string>
template <typename T>
std::string debug_rep(const T &);
template <typename T>
std::string debug_rep(T *);
std::string debug_rep(const char *p){
    return debug_rep(std::string(p));
}
std::string debug_rep(char *p){
    return debug_rep(std::string(p));
}
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
int main()
{
    std::string str("helllo");
    std::cout << debug_rep("helllo") << std::endl;
    return 0;
}
