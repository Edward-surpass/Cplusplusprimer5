#include "Sales_data.h"
// used in future chapters
std::istream &operator>>(std::istream &in,Sales_data &rhs)
{
    std::string line,word;
    std::getline(in,line);
    if(in){
        std::stringstream cinstr(line);
        while(cinstr >> word)
        {
            if(word.find('-') < word.size())
            {
                rhs.bookNo = word;
            }
            else if(word.find_first_of('.') < word.size())
            {
                std::string::size_type sz;
                rhs.revenue = std::stod(word,&sz);
            }
            else
            {
                std::string::size_type sz;
                rhs.units_sold = std::stoi(word,&sz);
            }
        }
    }
    return in;
}
std::ostream &operator<<(std::ostream &o,const Sales_data &rhs)
{
    return o << rhs.bookNo << ":" << rhs.units_sold << " " << rhs.revenue;
}
Sales_data &Sales_data::operator=(const std::string &s)
{
    bookNo = s;
    units_sold = 0;
    revenue = 0;
    return *this;
}
Sales_data Sales_data::operator+(const Sales_data &rhs)
{
    Sales_data temp;
    temp.bookNo = bookNo;
    temp.units_sold = units_sold + rhs.units_sold;
    temp.revenue = revenue + rhs.revenue;
    return std::move(temp);
}
Sales_data &Sales_data::operator+=(const Sales_data &rhs)
{
    return *this = *this + rhs;
}
Sales_data::operator std::string()const
{
    return bookNo;
}
Sales_data::operator double()const
{
    return revenue;
}
