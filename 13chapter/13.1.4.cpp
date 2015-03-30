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
    has_ptr(const has_ptr &p):i(0){
        delete ps;
        ps = new string(*(p.ps) + " world");
    }
    has_ptr operator=(const has_ptr &p);
    ~has_ptr(){delete ps;}
    void my_print(){
        cout << *ps << endl;
    }
};
has_ptr has_ptr::operator=(const has_ptr &p)
{
    delete ps;
    ps = new string(*p.ps);
    return *this;
}
int main()
{
    has_ptr hp("hello");
    has_ptr hp1 = hp;
    hp.my_print();
    hp1.my_print();
    return 0;
}
