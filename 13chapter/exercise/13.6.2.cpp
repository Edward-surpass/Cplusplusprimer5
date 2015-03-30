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
public:
    has_ptr(const string &s = string()):ps(new string(s)),i(0){}
    has_ptr(const has_ptr &p):i(p.i){
        ps = new string(*(p.ps) );
        cout << "拷贝构造函数执行" << endl;
    }
    has_ptr(has_ptr &&)noexcept;
    void my_print(){
        if(ps)
            cout << *ps << endl;
        else
            cout << "string is nullptr" << endl;
    }
    has_ptr &operator=(has_ptr p);
    ~has_ptr(){delete ps;}
};
has_ptr &has_ptr::operator=(has_ptr p)
{
    string *p_f = new string(*p.ps);
    delete ps;
    ps = p_f;
    i = p.i;
    cout << "operator= is going" << endl;
    p.my_print() ;
    return *this;
}
has_ptr::has_ptr(has_ptr &&p)noexcept:ps(p.ps),i(p.i)
{
    p.ps = nullptr;
    cout << "移动构造函数执行" << endl;
}
int main()
{
    has_ptr hp("hello");
    has_ptr hp2("world");
    hp = std::move(hp2);
    hp.my_print();
    hp2.my_print();
    return 0;
}
