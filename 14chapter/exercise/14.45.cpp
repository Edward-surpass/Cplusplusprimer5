#include <string>
#include <iostream>
#include <sstream>
class Sales_data {
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend std::ostream &print(std::ostream&, const Sales_data&);
    friend std::istream &read(std::istream&, Sales_data&);
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
    Sales_data& combine(const Sales_data&);
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
int main()
{
    Sales_data sd("001",5,20.2);
    Sales_data sd2("002",10,0.2);
    std::cout << static_cast<std::string>(sd) << std::endl;
    return 0;
}
