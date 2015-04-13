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
class bulk_quote_min:public Quote
{
private:
    std::size_t min_qty;
    double discount;
public:
    bulk_quote_min() = default;
    bulk_quote_min(const std::string &book,const double sales_price,std::size_t miqt,const double disc):Quote(book,sales_price),min_qty(miqt),discount(disc){}
    double print_total(const std::size_t cnt);
    ~bulk_quote_min() = default;
};
double bulk_quote_min::print_total(const std::size_t cnt)
{
    if(cnt <=min_qty )
        return cnt*(1-discount)*price;
    else
        return (min_qty*(1-discount)*price + (cnt-min_qty)*price);
}
int main()
{
    Quote Qt("001",10);
    bulk_quote bq("002",25,30,0.2);
    bulk_quote_min bqm("003",25,30,0.2);
    Quote *q = &bq;
    q->net_price(35);
    bq.net_price(35);
    Qt.net_price(35);
    return 0;
}
