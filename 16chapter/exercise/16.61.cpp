/*********************************************************************************
*     File Name           :     16.61.cpp
*     Created By          :     edward
*     Creation Date       :     [2015-04-26 10:52]
*     Last Modified       :     [2015-04-26 11:07]
*     Description         :      
**********************************************************************************/
#include <memory>
#include <string>
#include <iostream>
template<typename T,typename ...Args>
std::shared_ptr<T> MakeShared(Args &&...rest){
    std::allocator<T> alloc = std::allocator<T>();
    auto p = alloc.allocate(1);
    alloc.construct(p,std::forward<Args>(rest)...);
    return std::shared_ptr<T>(p);
}
int main(){
    std::shared_ptr<std::string> p = MakeShared<std::string>(3,'s');
    std::cout << *p << std::endl;
}
