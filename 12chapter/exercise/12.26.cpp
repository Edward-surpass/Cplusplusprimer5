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
int main()
{
    int n = 10;
    allocator<string> alloc;
    string *p = alloc.allocate(n);
    string s,*q = p;
    while (cin>>s&&(q != p+10))
        alloc.construct(q++,s);
    for(q=p;q!=p+10;++q)
        cout << *q << " ";
    cout << endl;
    return 0;
}
