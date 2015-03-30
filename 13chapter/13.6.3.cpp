#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Foo
{
public:
    Foo sorted()&&;
    Foo sorted()const &;
    Foo sorted(bool (*)(const int &,const int &))const &;
    using Comp = bool (const int &,const int &);
    Foo sorted(Comp *)&&;
private:
    vector<int> data;
};
Foo Foo::sorted()&&
{
    sort(data.begin(),data.end());
    return *this;
}
Foo Foo::sorted()const&
{
    Foo ret(*this);
    sort(ret.data.begin(),ret.data.end());
    return ret;
}
