#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <sstream>
using namespace std;
class query_result;
class text_query;
class query_base;
class word_query;
class not_query;
class binary_query;
class or_query;
class and_query;
class Query;
class text_query{
private:
    shared_ptr<vector<string>> file;
    map<string,shared_ptr<set<vector<string>::size_type>>> wm;
public:
    text_query() = default;
    text_query(ifstream &);
    query_result query(const string &s)const;
};
text_query::text_query(ifstream &is):file(new vector<string>)
{
    string line,word;
    int i = 0;
    file->push_back(" ");
    while(getline(is,line))
    {
        ++i;
        file->push_back(line);
        istringstream sin(line);
        while(sin>>word)
        {
            if(wm.find(word) == wm.end())
                wm[word] = make_shared<set<vector<string>::size_type>>();
            wm[word]->insert(i);
        }
    }
    /*string text;
    while(getline(is,text))
    {
        file->push_back(text);
        int n = file->size()-1;
        istringstream line(text);
        string word;
        while(line >> word)
        {
            auto &lines = wm[word];
            if(!lines)
                lines.reset(new set<vector<string>::size_type>);
            lines->insert(n);
        }
    }*/
}
class query_result{
    friend ostream &print(ostream &o,const query_result &qr);
private:
    string sought;
    shared_ptr<set<vector<string>::size_type>> lines;
    shared_ptr<vector<string>> file;
public:
    query_result()=default;
    query_result(const string &s,const shared_ptr<set<vector<string>::size_type>> l,const shared_ptr<vector<string>> f):sought(s),lines(l),file(f){}
    vector<string>::iterator begin();
    vector<string>::iterator end();
    shared_ptr<vector<string>> get_file()
    {
        return file;
    }
};
query_result text_query::query(const string &s)const
{
    auto p = wm.find(s);
    if(p == wm.end())
    {
        static shared_ptr<set<vector<string>::size_type>> nodata= make_shared<set<vector<string>::size_type>>();
        cout << "no date" << endl;
        return query_result(s,nodata,file);
    }
    return query_result(s,p->second,file);
}
vector<string>::iterator query_result::begin()
{
    return (*file).begin();
}
vector<string>::iterator query_result::end()
{
    return (*file).end();
}
ostream &print(ostream &o,const query_result &qr)
{
    for(auto e:*(qr.lines))
    {
        o << "(line" << e << ")" << (*qr.file)[e] << endl; 
    }
    return o;
}
void run_queries(ifstream &infile)
{
    text_query tq(infile);
    while(1)
    {
        cout << "enter word to look for,or q to quit:";
        string s;
        if(!(cin>>s)||s == "q") break;
        print(cout ,tq.query(s))<< endl;
    }
}
class query_base
{
    friend class Query;
protected:
    virtual ~query_base() = default;
private:    
    virtual query_result eval(const text_query &)const = 0;
    virtual string rep()const = 0;
};
class Query{
    friend Query operator~(const Query &);
    friend Query operator|(const Query &,const Query &);
    friend Query operator&(const Query &, const Query &);
    friend ostream & operator<<(ostream &os,const Query &query)
    {
        return os << query.rep();
    }
private:
    shared_ptr<query_base> q;
    Query(const shared_ptr<query_base> &);
public:
    Query() = default;
    Query(const string &s);
    query_result eval(const text_query &t)const{
        return q->eval(t);
    }
    string rep()const{
        cout << "Query::rep" << endl;
        return q->rep();
    }
};
Query::Query(const shared_ptr<query_base> &qb)
{
    cout << "Query shared_ptr<query_base>"<< endl;
    q = qb;
}
class word_query:public query_base{
    friend class Query;
private:
    const string word;
    word_query(const string &s):word(s){cout << "word_query"<< endl;}
    virtual query_result eval(const text_query &t)const override{
        return t.query(word);
    }
    virtual string rep()const override
    {
        cout << "word_query::rep()" << endl;
        return word;
    }
public:
    word_query() = default;
};
Query::Query(const string &s)
{
    cout << "Query const string s" << endl;
    q = make_shared<word_query>(word_query(s));
    //q = shared_ptr<query_base>(new word_query(s));
}
class not_query:public query_base{
    friend Query operator~(const Query &);
    private:
        not_query(const Query &rhs):query(rhs){cout << "not_query " << endl;}
        Query query;
        virtual query_result eval(const text_query &t)const override
        {
            return t.query(" ");
        }
        virtual string rep()const override
        {
            cout << "not_query::rep()" << endl;
           return string("~(") + query.rep() + ")";
        }

};
inline Query operator~(const Query &rhs)
{
    return Query(make_shared<not_query>(not_query(rhs)));
    //return Query(shared_ptr<query_base> (new not_query(rhs)));
}
int main()
{
    Query q2 = ~Query("sss");
    cout << "================" << endl;
    cout << q2 << endl;
    return 0;
}
