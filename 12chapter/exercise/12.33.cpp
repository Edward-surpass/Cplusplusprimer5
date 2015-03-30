#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <memory>
#include <utility>
#include <initializer_list>
#include <map>
#include <set>
#include <vector>
using namespace std;
class str_blob_ptr;
class str_blob{
    friend class str_blob_ptr;
private:
    shared_ptr<vector<string>> data;
    void check(vector<string>::size_type i,const string &msg) const;
public:
    str_blob():data(make_shared<vector<string>>()){}
    str_blob(initializer_list<string> il);
    vector<string>::size_type size()const {return data->size();}
    bool empty()const{return data->empty();}
    void push_back(const string &t){data->push_back(t);}
    void pop_back();
    string &front();
    const string &front()const;
    string &back();
    const string &back()const;
    string &operator[](const vector<string>::size_type &);
    str_blob_ptr begin();
    str_blob_ptr end();
};
str_blob::str_blob(initializer_list<string> il):data(make_shared<vector<string>>(il)){}
void str_blob::pop_back()
{
    check(0,"pop_back on empty str_blob");
    data->pop_back();
}
string &str_blob::front()
{
    check(0,"front on empty str_blob");
    return data->front();
}
string &str_blob::back()
{
    check(0,"back on empty str_blob");
    return data->back();
}
void str_blob::check(vector<string>::size_type i,const string &msg)const
{
    if(i >= data->size())
        throw out_of_range(msg);
}
const string & str_blob::front()const
{
    check(0,"front on empty str_blob");
    return data->front();
}
const string &str_blob::back()const 
{
    check(0,"back on empty str_blob");
    return data->back();
}
string &str_blob::operator[](const vector<string>::size_type &i)
{
    check(i,"out of range");
    return (*data)[i];
}
shared_ptr<vector<int>> creat_v()
{
    return make_shared<vector<int>>();
}
void push_v(shared_ptr<vector<int>> p)
{
    int i = 0;
    while(cin >> i)
        p->push_back(i);
}
void print_v(shared_ptr<vector<int>> p)
{
    for(auto &e:*p)
        cout << e << " ";
    cout << endl;
}
class str_blob_ptr{
private:
    weak_ptr<vector<string>> wptr;
    vector<string>::size_type curr;
    shared_ptr<vector<string>> check(vector<string>::size_type t ,const string &)const;
public:
    str_blob_ptr()=default;
    str_blob_ptr(str_blob &a,vector<string>::size_type sz = 0):wptr(a.data),curr(sz){}
    string &deref() const;//*
    str_blob_ptr &incr();//++curr
};
shared_ptr<vector<string>> str_blob_ptr::check(vector<string>::size_type i,const string &msg)const
{
   shared_ptr<vector<string>> ret = wptr.lock();
   if(!ret)
       throw runtime_error("unbound str_blob_ptr");
   if(i > ret->size())
       throw out_of_range(msg);
   return ret;
}
string &str_blob_ptr::deref()const
{
    shared_ptr<vector<string>> p = check(0,"dereference past end");
    return (*p)[curr];
}
str_blob_ptr &str_blob_ptr::incr()
{
    check(0,"increment past end of str_blob_ptr");
    ++curr;
    return *this;
}
str_blob_ptr str_blob::begin()
{
    return str_blob_ptr(*this);
}
str_blob_ptr str_blob::end(){
    return str_blob_ptr(*this,data->size());
}
class query_result;
class text_query{
private:
    shared_ptr<str_blob> file;
    map<string,shared_ptr<set<vector<string>::size_type>>> wm;
public:
    text_query() = default;
    text_query(ifstream &);
    query_result query(const string &s)const;
};
text_query::text_query(ifstream &is):file(new str_blob)
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
    shared_ptr<str_blob> file;
public:
    query_result()=default;
    query_result(const string &s,const shared_ptr<set<vector<string>::size_type>> l,const shared_ptr<str_blob> f):sought(s),lines(l),file(f){}
    str_blob_ptr begin();
    str_blob_ptr end();
    shared_ptr<str_blob> get_file()
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
str_blob_ptr query_result::begin()
{
    return str_blob_ptr(*file,0);
}
str_blob_ptr query_result::end()
{
    return str_blob_ptr(*file,(*file).size()-1);
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
int main()
{
    ifstream my_text("textexample");
    run_queries(my_text);
    return 0;
}
