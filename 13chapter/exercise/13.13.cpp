#include <iostream>
#include <vector>
using namespace std;
class X{
private:
public:
    X(){cout << "X()" << endl;}
    X(const X&x){cout << "X(const X&x)" << endl;}
    X operator=(const X&x){cout << "operator=(const X&x)" << endl;}
    ~X(){cout << "~X()" << endl;}
};
X my_test1(X x)//实参传递拷贝一次
{
    return x;//函数返回拷贝一次
}
X my_test2(const X &x)//引用不拷贝
{
    return x;//函数返回拷贝一次
}
X my_test3()
{
    X *p = new X;//无参构造函数
    return *p;//函数返回拷贝一次
}
X my_test4()
{
    X x;
    return x;//会返回临时变量，不拷贝,但是必须要有拷贝构造函数，比如拷贝构造函数在私有成员里就不行
}
X my_test5()
{
    vector<X> vx;
    vx.push_back(X());//无参构造函数,并用拷贝构造函数拷贝一份放入vector
    return vx[0];//函数返回拷贝一次
}
int main()
{
    my_test5();
    return 0;
}
