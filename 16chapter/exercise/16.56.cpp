/*********************************************************************************
*     File Name           :     16.56.cpp
*     Created By          :     edward
*     Creation Date       :     [2015-04-26 09:51]
*     Last Modified       :     [2015-04-26 09:57]
*     Description         :      
**********************************************************************************/
#include <iostream>
#include <sstream>
#include <string>
template <typename T>
std::string debug_rep(const T &);
template <typename T>
std::string debug_rep(T *);
std::string debug_rep(const std::string &);
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
std::string debug_rep(const std::string &s)
{
    return '"' + s + '"';
}
template <typename T>
std::ostream &print(std::ostream &os,const T &t)
{
   return os << t;
}
template <typename T,typename ... Args>
std::ostream &print(std::ostream &os,const T &t, const Args &... rest){
    os << t << ",";
    return print(os,rest...);
}
template <typename ...Args>
std::ostream &errorMsg(std::ostream &os,const Args &... rest)
{
    return print(os,debug_rep(rest)...);
}
int main()
{
    std::string fcnname("ssls");
    const char *ch = "peter";
    char otherdata[] = "ewoiu";
    errorMsg(std::cout,fcnname,ch,otherdata,"ppp");
    return 0;
}
