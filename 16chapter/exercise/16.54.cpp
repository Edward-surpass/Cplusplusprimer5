/*********************************************************************************
*     File Name           :     16.53.cpp
*     Created By          :     edward
*     Creation Date       :     [2015-04-25 16:33]
*     Last Modified       :     [2015-04-25 16:48]
*     Description         :      
**********************************************************************************/
#include <iostream>
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
class test{
    int a;
};
int main()
{
    print(std::cout,90);
    std::cout << std::endl;
    print(std::cout,3,"ss",8.9);
    std::cout << std::endl;
    print(std::cout,3,"ss",8.9,999,"po",test());
    std::cout << std::endl;
    return 0;
}
