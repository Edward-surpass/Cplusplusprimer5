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
    has_ptr(const has_ptr &p):ps(p.ps),i(0),use(p.use){
        ++*use;
    }
    void my_print(){
        cout << *ps << endl;
    }
    has_ptr &operator=(const has_ptr &p);
    ~has_ptr();
};
has_ptr &has_ptr::operator=(const has_ptr &p)
{
    ++*p.use;
    if(--*use == 0)
    {
        delete ps;
        delete use;
    }
    i = p.i;
    use = p.use;
    ps = p.ps;
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
    has_ptr hp("hello"),hp1("world");
    hp1 = hp;
    hp.my_print();
    hp1.my_print();
    return 0;
}
