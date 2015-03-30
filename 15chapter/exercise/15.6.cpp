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
private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};
bulk_quote::bulk_quote(const std::string &book,const double sales_price,std::size_t qty,const double disc):Quote(book,sales_price),min_qty(qty),discount(disc){}
double bulk_quote::net_price(std::size_t cnt)const
{
    if(cnt > min_qty)
        return cnt *(1-discount)*price;
    else
        return cnt *price;
}
double print_total(std::ostream &os,const Quote &item,std::size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN:" << item.isbn() << "#slod:" << n << "total due:" << ret << std::endl;
    return ret;
}
int main()
{
    Quote Qt("001",10);
    bulk_quote bq("002",25,30,0.2);
    std::cout << print_total(std::cout,Qt,35) << std::endl;
    std::cout << print_total(std::cout,bq,35) << std::endl;
    return 0;
}
