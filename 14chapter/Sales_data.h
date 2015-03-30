//SALES_DATA_H Sales_data.h
//ss
#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
#include <iostream>
#include <sstream>
class Sales_data {
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend bool operator==(const Sales_data&,const Sales_data &);
    friend bool operator!=(const Sales_data&,const Sales_data &);
    friend std::ostream &print(std::ostream&, const Sales_data&);
    friend std::istream &read(std::istream&, Sales_data&);
    friend std::ostream &operator<<(std::ostream &,const Sales_data &);
    friend std::istream &operator>>(std::istream &,Sales_data &);
public:
    Sales_data():units_sold(0), revenue(0.0) {}
    Sales_data(const std::string &s):bookNo(s), units_sold(0), revenue(0.0){}
    Sales_data(const std::string &s, unsigned n, double p):bookNo(s), units_sold(n), revenue(p*n) {}
    // operations on Sales_data objects
    Sales_data(std::istream &);
    std::string isbn() const 
    {
        return bookNo;
    }
    Sales_data& combine(const Sales_data&);
    double avg_price() const;
private:
    std::string bookNo;
    unsigned units_sold;
    double revenue;
    Sales_data operator+(const Sales_data &);
    Sales_data &operator+=(const Sales_data &);
    Sales_data operator-(const Sales_data &);
    Sales_data &operator-=(const Sales_data &);
};
// nonmember Sales_data interface functions
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);
// used in future chapters
inline bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}
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
            else{
                std::string::size_type sz;
                rhs.units_sold = std::stoi(word,&sz);
            }
        }
    }
    return in;
}
#endif
