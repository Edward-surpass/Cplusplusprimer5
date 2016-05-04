/*********************************************************************************
*     File Name           :     16.63.cpp
*     Created By          :     edward
*     Creation Date       :     [2015-04-27 07:58]
*     Last Modified       :     [2015-04-27 08:13]
*     Description         :      
**********************************************************************************/
#include <vector>
#include <string>
#include <iostream>
template <typename T>
std::size_t calc_fre(const std::vector<T> &vt,const T &t){
    std::size_t times = 0;
    for(auto e:vt)
    {
        if(e == t){
            ++times;
        }
    }
    return times;
}
std::size_t calc_fre(const std::vector<std::string> &vt,const char *const &t){
    std::size_t times = 0;
    std::string temp(t);
    for(auto e:vt)
    {
        if(e == temp){
            ++times;
        }
    }
    return times;
}
int main(){
    std::vector<double> vd = {1.2,2.5,2.5,7.7};
    std::vector<int> vi = {1,2,3,4,5,5,5,4,3};
    std::vector<std::string> vs = {"sss","asdf","sss","a","sss"};
    std::cout << calc_fre(vd,2.5) << std::endl;
    std::cout << calc_fre(vi,5) << std::endl;
    std::cout << calc_fre(vs,"a") << std::endl;
}
