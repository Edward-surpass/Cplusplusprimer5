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
class A
{
private:
    int a;
public:
    A(){cout << "A" << endl;}
    A(int a):a(a){cout << "A(a)" << endl;}
    ~A(){cout << "~A" << endl;}
    friend bool operator<(const A &a,const A &b)
    {
        return a.a < b.a;
    }
};
int main()
{
    set<int *> iset;
    int a = 1,b = 2;
    int *p = &a;
    iset.insert(&a);
    iset.insert(&b);
    iset.erase(p);
    cout << 123 << endl;
    return 0;
}
