#include <iostream>
#include <string>
#include <vector>
class Quote
{
public:
    Quote() = default;
    Quote(const std::string &book):bookNo(book){}
    Quote(const std::string &book,const double sales_price):bookNo(book),price(sales_price){}
    Quote operator=(const Quote &);
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
Quote Quote::operator=(const Quote &rhs)
{
    bookNo = rhs.bookNo;
    price = rhs.price;
    std::cout << "Quote operator=" << std::endl;
    return *this;
}
class bulk_quote:public Quote
{
public:
    using Quote::Quote;
    bulk_quote() = default;
    bulk_quote(const std::string &book,const double sales_price,std::size_t,const double);
    bulk_quote operator=(const bulk_quote&);
    double net_price(std::size_t n)const override;
    ~bulk_quote() = default;
private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};
bulk_quote bulk_quote::operator=(const bulk_quote& rhs)
{
    Quote::operator=(rhs);
    min_qty = rhs.min_qty;
    discount = rhs.discount;
    std::cout << "bulk_quote operator=" << std::endl;
    return *this;
}
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
    using Quote::Quote;
    bulk_quote_min() = default;
    bulk_quote_min(const std::string &book,const double sales_price,std::size_t miqt,const double disc):Quote(book,sales_price),min_qty(miqt),discount(disc){}
    bulk_quote_min operator=(const bulk_quote_min&);
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
bulk_quote_min bulk_quote_min::operator=(const bulk_quote_min&rhs)
{
    Quote::operator=(rhs);
    min_qty = rhs.min_qty;
    discount = rhs.discount;
    std::cout << "bulk_quote_min operator=" << std::endl;
    return *this;
}
int main()
{
    std::vector<Quote> vQ;
    Quote Qt("001",10);
    bulk_quote bq("002",25,30,0.2);
    bulk_quote_min bqm("003",25,30,0.2);
    bulk_quote bq1("003");
    vQ.push_back(Qt);
    vQ.push_back(bq);
    double allprice = 0;
    for(auto &e:vQ)
    {
        allprice += e.net_price(40);
    }
    std::cout << allprice << std::endl;
    return 0;
}
