#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <sstream>
#include <memory>
#include <utility>
#include <initializer_list>
using namespace std;
class str_blob{
    friend bool operator==(const str_blob &,const str_blob &);
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
    friend class str_blob_ptr;
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
struct connection{
    public:
       connection(){cout << "connection" << endl;} 
};
void disconnect(connection p)
{
    cout << "disconnect" << endl;
    return;
}
void end_connection(connection *p)
{
    disconnect (*p);
}
bool operator==(const str_blob &lhs,const str_blob &rhs)
{
    return lhs.data == rhs.data;
}
int main()
{
    return 0;
}
