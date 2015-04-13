#include <iostream>
#include <string>
class Quote
{
public:
    Quote() = default;
    Quote(const std::string &book,const double sales_price):bookNo(book),price(sales_price){}
    std::string isbn()const{return std::move(bookNo);}
    virtual double net_price(std::size_t n)const
    {
        return n*price;
    }
    virtual ~Quote() = default;
private:
    std::string bookNo;
protected:
    double price = 0.0;
};
class bulk_quote:public Quote
{
public:
    bulk_quote() = default;
    bulk_quote(const std::string &book,const double sales_price,std::size_t,const double);
    double net_price(std::size_t n)const override;
    ~bulk_quote() = default;
};
double print_total(std::ostream &os,const Quote &item,std::size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN:" << item.isbn() << "#slod:" << n << "total due:" << ret << std::endl;
    return ret;
}
