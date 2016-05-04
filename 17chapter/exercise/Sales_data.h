#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
#include <iostream>
#include <sstream>
class Sales_data {
    friend std::ostream &operator<<(std::ostream &,const Sales_data &);
    friend std::istream &operator>>(std::istream &,Sales_data &);
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

#endif
