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
class has_ptr{
private:
    string *ps;
    int i;
    size_t *use;
public:
    has_ptr(const string &s = string()):ps(new string(s)),i(0),use(new size_t(1)){}
    has_ptr(const has_ptr &p):ps(p.ps),i(p.i),use(p.use){
        ++*use;
    }
    has_ptr(has_ptr &&);
    void my_print(){
        cout << *ps << endl;
    }
    has_ptr &operator=(const has_ptr &p);
    has_ptr &operator=(has_ptr &&);
    friend void swap(has_ptr &lh,has_ptr &rh)
    {
        std::swap(lh.ps,rh.ps);
        std::swap(lh.i,rh.i);
        std::swap(lh.use,rh.use);
        cout << "has_ptr swap is running" << endl;
    }
    friend bool operator<(const has_ptr &lh,const has_ptr &rh)
    {
        return (*lh.ps < *rh.ps);
    }
    friend ostream &operator<<(ostream &o,const has_ptr &rh)
    {
        return o << *rh.ps;
    }
    ~has_ptr();
};
has_ptr::has_ptr(has_ptr &&p):ps(p.ps),i(p.i),use(p.use)
{   
    p.ps = = nullptr;
    p.use = nullptr;
    p.i = 0;
}
has_ptr &has_ptr::operator=(const has_ptr &p)
{
    has_ptr temp(p);
    swap(*this,temp);
    return *this;
}
has_ptr::~has_ptr()
{
    --*use;
    if(*use == 0)
    {
        delete ps;
        delete use;
    }
}
int main()
{
    vector<has_ptr> hp;
    /*hp.push_back(has_ptr("hello"));
    hp.push_back(has_ptr("world"));
    hp.push_back(has_ptr("hello"));
    hp.push_back(has_ptr("world"));
    hp.push_back(has_ptr("llo"));
    hp.push_back(has_ptr("rlod"));
    hp.push_back(has_ptr("tt"));
    hp.push_back(has_ptr("a"));
    hp.push_back(has_ptr("b"));
    hp.push_back(has_ptr("c"));*/
    hp.push_back(has_ptr("d"));
    hp.push_back(has_ptr("rlod"));
    for(auto &e:hp)
        cout << e << " ";
    cout << endl;
    std::sort(hp.begin(),hp.end());
    cout << "==================" << endl;
    for(auto &e:hp)
        cout << e << " ";
    cout << endl;
    return 0;
}
