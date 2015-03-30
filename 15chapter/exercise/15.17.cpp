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
        std::cout << "jilei" << std::endl;
        return n*price;
    }
    virtual ~Quote() = default;
private:
    std::string bookNo;
protected:
    double price = 0.0;
};
class disc_quote:public Quote
{
public:
    disc_quote() = default;
    disc_quote(const std::string &book,const double sales_price,std::size_t qty,const double disc):Quote(book,sales_price),min_qty(qty),discount(disc){}
    virtual double net_price(std::size_t n)const override = 0;
    ~disc_quote()override = default;
protected:
    std::size_t min_qty;
    double discount;
};
class bulk_quote:public disc_quote
{
public:
    bulk_quote() = default;
    bulk_quote(const std::string &book,const double sales_price,std::size_t,const double);
    double net_price(std::size_t n)const override;
    ~bulk_quote() = default;
};
    bulk_quote::bulk_quote(const std::string &book,const double sales_price,std::size_t qty,const double disc):disc_quote(book,sales_price,qty,disc){}
double bulk_quote::net_price(std::size_t cnt)const
{
    std::cout << "paishenglei" << std::endl;
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
class bulk_quote_min:public disc_quote
{
public:
    bulk_quote_min() = default;
    bulk_quote_min(const std::string &book,const double sales_price,std::size_t mqty,const double disc):disc_quote(book,sales_price,mqty,disc){}
    double net_price(std::size_t n)const override;
    ~bulk_quote_min() = default;
};
double bulk_quote_min::net_price(const std::size_t n)const
{
    if(n <=min_qty )
        return n*(1-discount)*price;
    else
        return (min_qty*(1-discount)*price + (n-min_qty)*price);
}
int main()
{
    disc_quote dq("0141",25.2,20,0.2);
    return 0;
}
