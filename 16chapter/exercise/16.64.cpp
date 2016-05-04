/*********************************************************************************
*     File Name           :     16.63.cpp
*     Created By          :     edward
*     Creation Date       :     [2015-04-27 07:58]
*     Last Modified       :     [2015-04-27 08:40]
*     Description         :      
**********************************************************************************/
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <type_traits>
template <typename T>
std::size_t calc_fre(const std::vector<T> &vt,const T t){
    std::cout << "T" << std::endl;
    std::size_t times = 0;
    for(auto e:vt)
    {
        if(e == t){
            ++times;
        }
    }
    return times;
}
template <>
std::size_t calc_fre(const std::vector<const char*> &vc,const char *const t){ //如果是引用,则对于字符串字面常量,类型为const char &[N],而不是指针,所用不能处理字符串字面常量
    std::cout << "double const char *const " << std::endl;
    std::size_t times = 0;
    for(auto e:vc)
    {
        if(!strcmp(e,t)){
            ++times;
        }
    }
    return times;
}
//std::size_t calc_fre(const std::vector<std::string> &vt,const char *const t){
//    std::cout << "string const char *const &" << std::endl;
//    std::size_t times = 0;
//    std::string temp(t);
//    for(auto e:vt)
//    {
//        if(e == temp){
//            ++times;
//        }
//    }
//    return times;
//}
int main(){
    std::vector<double> vd = {1.2,2.5,2.5,7.7};
    std::vector<int> vi = {1,2,3,4,5,5,5,4,3};
    std::vector<const char *> vc = {"sss","asdf","sss","a","sss"};
    std::vector<std::string> vs = {"sss","asdf","sss","a","sss"};
    std::cout << calc_fre(vd,2.5) << std::endl;
    std::cout << calc_fre(vi,5) << std::endl;
    std::cout << calc_fre(vc,"a") << std::endl;
}
