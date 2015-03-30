#include <iostream>
#include "Sales_data.h"
using namespace std;
bool operator==(const Sales_data &lhs,const Sales_data &rhs)
{
    return lhs.bookNo == rhs.bookNo && lhs.units_sold == rhs.units_sold &&lhs.revenue == rhs.revenue; 
}
bool operator!=(const Sales_data &lhs,const Sales_data &rhs)
{
    return !(lhs == rhs);
}
int main()
{
    return 0;
}
