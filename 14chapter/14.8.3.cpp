#include <iostream>
#include <string>
#include <map>
#include <functional>
using namespace std;
int add(int i,int j)
{
    return i+j;
}
class divide
{
public:
    int operator()(int denominator,int divisor)
    {
        return denominator/divisor;
    }
};
int main()
{
    auto mod = [](int i,int j){return i%j;};
    function<int(int,int)> f1 = add;
    function<int(int,int)> f2 = divide();
    function<int(int,int)> f3 = mod;
    map<string,function<int(int,int)>> binops{
        {"+",[](int i,int j){return add(i,j);}},
        {"-",std::minus<int>()},
        {"*",[](int i,int j){return i*j;}},
        {"/",divide()},
        {"%",function<int(int,int)>(add)}
    };
    string opt;
    int i,j;
    while(1)
    {
        cout << "please intput ooperator,q is quit" << endl;
        cin >> opt;
        cout << "please input two operand" << endl;
        cin >> i >> j;
        cout << binops[opt](i,j) << endl;
    }
    return 0;
}
