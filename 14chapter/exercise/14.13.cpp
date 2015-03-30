#include <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include "Sales_data.h"
using namespace std;
Sales_data &Sales_data::operator+=(const Sales_data &rhs)
{
    if(bookNo == rhs.bookNo)
    {
        units_sold += rhs.units_sold;
        revenue += rhs.revenue;
    }
    return *this;
}
Sales_data Sales_data::operator+(const Sales_data &rhs)
{
    Sales_data sum(*this);
    sum+=rhs;
    return sum;
}
Sales_data &Sales_data::operator-=(const Sales_data &rhs)
{
    if(bookNo == rhs.bookNo)
    {
        units_sold -= rhs.units_sold;
        revenue -= rhs.revenue;
    }
    return *this;
}
Sales_data Sales_data::operator-(const Sales_data &rhs)
{
    Sales_data sum(*this);
    sum -= rhs;
    return sum;
}
int main()
{
    Sales_data sd;
    std::cin >> sd;
    return 0;
}
