/*********************************************************************************
*     File Name           :     16.62.cpp
*     Created By          :     edward
*     Creation Date       :     [2015-04-26 19:38]
*     Last Modified       :     [2015-04-26 20:16]
*     Description         :      
**********************************************************************************/
#include <unordered_set>
#include <string>
#include <iostream>
#include <sstream>
#include <hash_map>
class Sales_data {
    friend struct std::hash<Sales_data>;
    friend std::ostream &operator<<(std::ostream &,const Sales_data &);
    friend std::istream &operator>>(std::istream &,Sales_data &);
    friend bool operator==(const Sales_data &lhs,const Sales_data &rhs);
public:
    Sales_data():units_sold(0), revenue(0.0) {}
    Sales_data(const std::string &s):bookNo(s), units_sold(0), revenue(0.0){}
    Sales_data(const std::string &s, unsigned n, double p):bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data &operator=(const std::string &);
    // operations on Sales_data objects
    Sales_data(std::istream &);
    std::string isbn() const 
    {
        return bookNo;
    }
    Sales_data& combineIsbn(const Sales_data&);
    double avg_price() const;
    Sales_data operator+(const Sales_data &);
    Sales_data &operator+=(const Sales_data &);
    Sales_data operator-(const Sales_data &);
    Sales_data &operator-=(const Sales_data &);
    operator std::string()const;
    operator double()const;
private:
    std::string bookNo;
    unsigned units_sold;
    double revenue;
};
// used in future chapters
inline bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}
namespace std{
template <>
struct hash<Sales_data>{
    typedef size_t result_type;
    typedef Sales_data argument_type;
    size_t operator()(const Sales_data &)const;
};
size_t hash<Sales_data>::operator()(const Sales_data &sd)const{
    return std::hash<std::string>()(sd.isbn()) ^ std::hash<unsigned>()(sd.units_sold) ^ std::hash<double>()(sd.revenue);
}
}
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
bool operator==(const Sales_data &lhs,const Sales_data &rhs){
    return (lhs.isbn() == rhs.isbn()) && (lhs.units_sold == rhs.units_sold) && (lhs.revenue == rhs.revenue);
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
int main(){
    std::unordered_multiset<Sales_data> SDset; 
    SDset.insert(Sales_data());
    SDset.insert(Sales_data("ss"));
    SDset.insert(Sales_data("ss",3,2.5));
    for(auto p = SDset.begin();p != SDset.end();++p)
        std::cout << *p << " ";
    std::cout << std::endl;
    return 0;
}
