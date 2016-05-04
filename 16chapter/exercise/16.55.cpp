/*********************************************************************************
*     File Name           :     16.53.cpp
*     Created By          :     edward
*     Creation Date       :     [2015-04-25 16:33]
*     Last Modified       :     [2015-04-26 10:20]
*     Description         :      
**********************************************************************************/
#include <iostream>
template <typename T,typename ... Args>
std::ostream &print(std::ostream &os,const T &t, const Args &... rest){
    if(t==0)
        return print(os,rest...);
    else
        return os;
}
int main()
{
    print(std::cout,3,"ss",8.9,0,"po");
    std::cout << std::endl;
    return 0;
}
