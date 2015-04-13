#include "15.41.h"
#include <algorithm>
Query::Query(const string &s):q(new word_query(s)),re_count(new size_t(1)){}
Query::Query(const Query &qe):q(qe.q),re_count(qe.re_count){
    ++(*re_count);
}
Query &Query::operator=(const Query &rhs)
{
    Query temp(rhs);
    if(--*re_count == 0)
    {
        delete re_count;
        delete q;
    }
    q = temp.q;
    re_count = temp.re_count;
    ++*re_count;
    return *this;
}
Query &Query::operator=(Query &&rhs)
{
    q = rhs.q;
    rhs.q = nullptr;
    re_count = rhs.re_count;
    rhs.re_count = nullptr;
    return *this;
}
Query::Query(query_base *qb,const size_t &re_c)
{
    re_count = new size_t(re_c);
    q = qb;
}
query_result Query::eval(const text_query &t)const
{
    return q->eval(t);
}
string Query::rep()const{
    return q->rep();
}
Query::~Query()
{
    if(--*re_count == 0)
    {
        delete re_count;
        delete q;
    }
}
word_query::word_query(const string &s):word(s){}
query_result word_query::eval(const text_query &t)const{
    return t.query(word);
}
string word_query::rep()const{

    return word;
}
inline Query operator~(const Query &rhs)
{
    query_base *p = new not_query(rhs);
    //return Query(make_shared<not_query>(not_query(rhs)));
    return Query(p,1);
}
not_query::not_query(const Query &rhs):query(rhs){}
query_result not_query::eval(const text_query &t)const
{
    query_result temp = t.query(query.rep());
    shared_ptr<vector<string>> file = temp.get_file();
    shared_ptr<set<vector<string>::size_type>> lines = make_shared<set<vector<string>::size_type>> (set<vector<string>::size_type>());
    set<vector<string>::size_type>::iterator p = temp.begin(),q = temp.end();
    vector<string>::size_type sz = file->size();
    for(vector<string>::size_type n =0; n < sz; ++n)
    {
        if(p == q || *p != n)
            lines->insert(n);
        else if(p != q)
            ++p;
    }
    return query_result(query.rep(),lines,file);
}
string not_query::rep()const
{
    return string("(~") + query.rep() + ")";
}
binary_query::binary_query(const Query &l,const Query &r,const string &s):lhs(l),rhs(r),op_sym(s){}
string binary_query::rep()const
{
    return string("(") + lhs.rep() + op_sym + rhs.rep() + ")";
}
inline Query operator&(const Query &lhs,const Query &rhs)
{
    query_base *p = new and_query(lhs,rhs);
    //return Query(make_shared<qand_query>(and_query(lhs,rhs)));
    return Query(p,1);
}
and_query::and_query(const Query &qyf,const Query &qys):binary_query(qyf,qys,"&"){}
query_result and_query::eval(const text_query &t)const
{
    query_result temp_l = lhs.eval(t), temp_r = rhs.eval(t);
    shared_ptr<set<vector<string>::size_type>> lines = make_shared<set<vector<string>::size_type>> (set<vector<string>::size_type>());
    set_intersection(temp_l.begin(),temp_l.end(),temp_r.begin(),temp_r.end(),inserter(*lines,lines->begin()));
    //set<vector<string>::size_type>::iterator pl = temp_r.begin(),ql = temp_r.end(),pr = temp_r.begin(),qr = temp_r.end(); 
    //while(pl != pr&&ql !=qr)
    //{
    //    if(*pl == *ql)
    //    {
    //        lines->insert(*pl);
    //        ++pl;++ql;
    //    }
    //    else if(*pl < *ql)
    //    {
    //        ++pl;
    //    }
    //    else
    //        ++ql;
    //}
    cout << "and_query::eval" << endl;
    return query_result(rep(),lines,temp_l.get_file());
}
inline Query operator|(const Query &lhs,const Query &rhs)
{
    query_base *p = new or_query(lhs,rhs);
    //return Query(make_shared<query_base>(or_query(lhs,rhs)));
    return Query(p,1);
}
or_query::or_query(const Query &qyf,const Query &qys):binary_query(qyf,qys,"|"){}
query_result or_query::eval(const text_query &t)const
{
    query_result temp_l = lhs.eval(t), temp_r = rhs.eval(t);
    shared_ptr<set<vector<string>::size_type>> lines = make_shared<set<vector<string>::size_type>> (set<vector<string>::size_type>());
    set_union(temp_l.begin(),temp_l.end(),temp_r.begin(),temp_r.end(),inserter(*lines,lines->begin()));
    //set<vector<string>::size_type>::iterator pl = temp_r.begin(),ql = temp_r.end(),pr = temp_r.begin(),qr = temp_r.end(); 
    //while(pl != pr&&ql !=qr)
    //{
    //    if(*pl == *ql)
    //    {
    //        lines->insert(*pl);
    //        ++pl;++ql;
    //    }
    //    else if(*pl < *ql)
    //    {
    //        lines->insert(*pl);
    //        ++pl;
    //    }
    //    else
    //        lines->insert(*ql++);
    //}
    return query_result(rep(),lines,temp_l.get_file());
}
int main()
{
    ifstream inf("15.39example");
    text_query tq(inf);
    Query q = Query("fiery") & Query("bird") | Query("wind");
    Query q1 =~Query("him");
    Query q3 = ~Query("him") | Query("at");
    Query q4 = q;
    cout << q;
    print(cout ,q.eval(tq));
    return 0;
}





