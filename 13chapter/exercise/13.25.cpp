#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <sstream>
#include <memory>
#include <utility>
#include <initializer_list>
using namespace std;
class str_blob_ptr;
class str_blob{
    friend class str_blob_ptr;
private:
    shared_ptr<vector<string>> data;
    void check(vector<string>::size_type i,const string &msg) const;
public:
    str_blob():data(make_shared<vector<string>>()){cout << "str_blob无参构造函数执行" << endl;}
    str_blob(initializer_list<string> il);
    str_blob(const str_blob &sb);
    str_blob &operator=(const str_blob &sb);
    vector<string>::size_type size()const {return data->size();}
    bool empty()const{return data->empty();}
    void push_back(const string &t){data->push_back(t);}
    void pop_back();
    string &front();
    const string &front()const;
    string &back();
    const string &back()const;
    str_blob_ptr begin();
    str_blob_ptr end();
    void my_print(){
        for(auto &e:*data)
            cout << e << " ";
        cout << endl;
    }
};
str_blob::str_blob(initializer_list<string> il):data(make_shared<vector<string>>(il)){}
str_blob::str_blob(const str_blob &sb){
    data = make_shared<vector<string>>(*sb.data);
}
str_blob &str_blob::operator=(const str_blob &sb){
    data = make_shared<vector<string>>(*sb.data); 
    return *this;
}
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
    string &deref() const; //解引用
    str_blob_ptr &incr(); //递增下标
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
int main()
{
    str_blob sb1({"hello","world"});
    str_blob sb2 = {"edward","surpass"};
    sb1.my_print();
    sb2.my_print();
    sb2 = sb1;
    sb1.push_back("love");
    sb1.my_print();
    sb2.my_print();
    return 0;
}
