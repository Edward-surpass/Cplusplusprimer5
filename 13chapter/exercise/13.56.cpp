#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Foo
{
public:
    Foo sorted()&&;
    Foo sorted()const &;
private:
    vector<int> data;
};
Foo Foo::sorted()&&
{
    cout << "&&" << endl;
    sort(data.begin(),data.end());
    return *this;
}
Foo Foo::sorted()const&
{
    cout << "&" << endl;
    return Foo(*this).sorted();
}
int main()
{
    Foo fo1;
    fo1.sorted();
    return 0;
}
