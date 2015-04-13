#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <set>
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
    virtual Quote *clone()const &;
    virtual Quote *clone()&&;
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
Quote *Quote::clone()const &
{
    return new Quote(*this);
}
Quote *Quote::clone()&&
{
    return new Quote(std::move(*this));
}
class bulk_quote:public Quote
{
public:
    using Quote::Quote;
    bulk_quote() = default;
    bulk_quote(const std::string &book,const double sales_price,std::size_t,const double);
    bulk_quote operator=(const bulk_quote&);
    double net_price(std::size_t n)const override;
    bulk_quote *clone()const & override;
    bulk_quote *clone()&& override;
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
bulk_quote *bulk_quote::clone()const &
{
    return new bulk_quote(*this);
}
bulk_quote *bulk_quote::clone()&& 
{
   return new bulk_quote(std::move(*this));
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
    bulk_quote_min *clone()const & override;
    bulk_quote_min *clone()&& override;
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
bulk_quote_min *bulk_quote_min::clone()const &
{
    return new bulk_quote_min(*this);
}
bulk_quote_min *bulk_quote_min::clone()&& 
{
    return new bulk_quote_min(std::move(*this));
}
class basket
{
public:
    void add_items(const std::shared_ptr<Quote> &sale);
    void add_items(const Quote &);
    void add_items(Quote &&);
    double total_receipt(std::ostream&)const;
private:
    static bool compare(const std::shared_ptr<Quote> &lhs,const std::shared_ptr<Quote> &rhs)
    {
        return lhs->isbn() < rhs->isbn();
    }
    std::multiset<std::shared_ptr<Quote>,decltype(compare)*> items{compare};
};
void basket::add_items(const std::shared_ptr<Quote> &sale)
{
    items.insert(sale);
}
void basket::add_items(const Quote &sale)
{
    items.insert(std::shared_ptr<Quote>(sale.clone()));
}
void basket::add_items(Quote &&sale)
{
    items.insert(std::shared_ptr<Quote> (std::move(sale).clone()));
}
double basket::total_receipt(std::ostream &out)const
{
    double sum = 0;
    for(auto iter = items.cbegin();iter != items.cend(); iter = items.upper_bound(*iter))
        sum += print_total(out,**iter,items.count(*iter));
    out << "Total Sale:" << sum << std::endl;
    return sum;
}

int main()
{
    basket bk;
    Quote Qt("000",5);
    bk.add_items(Qt);
    bk.add_items(bulk_quote("001",10,2,0.8));
    bk.add_items(bulk_quote("001",10,2,0.8));
    bk.add_items(bulk_quote("001",10,2,0.8));
    bk.add_items(bulk_quote_min("002",20,5,0.6));
    bk.total_receipt(std::cout);
    return 0;
}
