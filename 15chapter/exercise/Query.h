#ifndef QUERY_H
#define QUERY_H
#include "text_query.h"
class query_base;
class Query{
    friend Query operator~(const Query &);
    friend Query operator|(const Query &,const Query &);
    friend Query operator&(const Query &, const Query &);
    friend ostream & operator<<(ostream &os,const Query &query)
    {
        return os << query.rep();
    }
private:
    //shared_ptr<query_base> q;
    query_base *q;
    //Query(const shared_ptr<query_base> &);
    Query(const query_base *);
public:
    Query() = default;
    Query(const string &s);
    Query(const Query &);
    Query(Query &&);
    Query &operator=(const Query &);
    Query &operator=(Query &&);
    query_result eval(const text_query &)const;
    string rep()const;
    ~Query();
};
class query_base
{
    friend class Query;
protected:
    virtual ~query_base() = default;
private:    
    virtual query_result eval(const text_query &)const = 0;
    virtual string rep()const =0;

};
class word_query:public query_base{
    friend class Query;
private:
    const string word;
    word_query(const string &s);
    virtual query_result eval(const text_query &t)const override;
    virtual string rep()const override;
public:
    word_query() = default;
};
class not_query:public query_base{
    friend Query operator~(const Query &);
    private:
        not_query(const Query &rhs);
        Query query;
        virtual query_result eval(const text_query &t)const override;
        virtual string rep()const override;
};
class binary_query:public query_base{
    protected:
        binary_query(const Query &l,const Query &r,const string &s);
        virtual string rep()const override;
        Query lhs,rhs;
        string op_sym;
};
class and_query:public binary_query{
    friend Query operator&(const Query &,const Query &);
    and_query(const Query &qyf,const Query &qys);
    virtual query_result eval(const text_query &t)const override;
};  
class or_query:public binary_query{
    friend Query operator|(const Query &,const Query &);
    or_query(const Query &qyf,const Query &qys);
    virtual query_result eval(const text_query &t)const override;
};
#endif
