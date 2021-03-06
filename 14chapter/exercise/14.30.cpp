#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <memory>
#include <utility>
#include <initializer_list>
using namespace std;
class const_str_blob_ptr;
class str_blob{
    friend class const_str_blob_ptr;
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
    const const_str_blob_ptr begin();
    const const_str_blob_ptr end();
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
shared_ptr<vector<int>> creat_v()
{
    return make_shared<vector<int>>();
}
class const_str_blob_ptr{
private:
    weak_ptr<vector<string>> wptr;
    vector<string>::size_type curr;
    shared_ptr<vector<string>> check(vector<string>::size_type t ,const string &)const;
public:
    const_str_blob_ptr()=default;
    const_str_blob_ptr(const str_blob &a,vector<string>::size_type sz = 0):wptr(a.data),curr(sz){}
    const string &deref() const;//解应用
    const string &operator*()const;
    const string *operator->()const;
    const const_str_blob_ptr &incr();//递增curr
    friend bool operator<(const const_str_blob_ptr &a,const const_str_blob_ptr &b)
    {
        return a.curr < b.curr;
    }
};
shared_ptr<vector<string>> const_str_blob_ptr::check(vector<string>::size_type i,const string &msg)const
{
   shared_ptr<vector<string>> ret = wptr.lock();
   if(!ret)
       throw runtime_error("unbound const_str_blob_ptr");
   if(i > ret->size())
       throw out_of_range(msg);
   return ret;
}
const string &const_str_blob_ptr::deref()const
{
    shared_ptr<vector<string>> p = check(0,"dereference past end");
    return (*p)[curr];
}
const string &const_str_blob_ptr::operator*()const
{
    auto p = check(curr,"dereference past end");
    return (*p)[curr];
}
const string *const_str_blob_ptr::operator->()const
{
    return &(operator*());
}
const const_str_blob_ptr &const_str_blob_ptr::incr()
{
    check(0,"increment past end of const_str_blob_ptr");
    ++curr;
    return *this;
}
const const_str_blob_ptr str_blob::begin()
{
    return const_str_blob_ptr(*this);
}
const const_str_blob_ptr str_blob::end(){
    return const_str_blob_ptr(*this,data->size());
}

int main()
{
    ifstream fin("12.20resource");
    str_blob re1220;
    string line,word;
    while(getline(fin,line))
    {
        istringstream sin(line);
        while(sin>>word)
            re1220.push_back(word);
    }
    for(const_str_blob_ptr p = re1220.begin();p < re1220.end();p.incr())
        cout << p.deref() << endl;
    return 0;
}
