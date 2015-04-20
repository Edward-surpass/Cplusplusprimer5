#include "Sales_data.h"
#include <iostream>
template<typename T>
int compare(const T &lhs,const T &rhs)
{
    return (lhs < rhs); 
}
int main()
{
    Sales_data sd1("00",5,0.1);
    Sales_data sd2("10",5,0.5);
    std::cout << compare(sd1,sd2) << std::endl;//此例中Sales_data会隐式转换为double比较
}
