/*********************************************************************************
*     File Name           :     16.51.cpp
*     Created By          :     edward
*     Creation Date       :     [2015-04-25 16:13]
*     Last Modified       :     [2015-04-25 16:33]
*     Description         :      
**********************************************************************************/
#include <iostream>
template <typename T,typename ...Args>
void foo(const T &t,const Args &...rest){
    std::cout << sizeof...(Args) << std::endl;
    std::cout << sizeof...(rest) << std::endl;
}
int main(){
    foo(3,"ss",9.9);
    foo(3,"ss");
    foo("ss");
    return 0;
}
