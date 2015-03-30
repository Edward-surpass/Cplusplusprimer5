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
class text1{
private:
    int num;
    text1( const text1 &t):num(t.num){cout << "text1的拷贝构造函数执行" << endl;}
public:
    text1(int n):num(n){cout << "text1参数为1的构造函数执行" << endl;}
};
class text2{
private:
    int num;
public:
    text2(int n):num(n){cout << "text2参数为1的构造函数执行" << endl;}
    text2( const text2 &t):num(t.num){cout << "text2的拷贝构造函数执行" << endl;}
};
class text3{
private:
    int num;
public:
    explicit text3(int n):num(n){cout << "text3参数为1的构造函数执行" << endl;}
    text3( const text3 &t):num(t.num){cout << "text3的拷贝构造函数执行" << endl;}
};
text2 my_test(text2 tt)
{
    //text2 tt(6);返回临时变量时，不会调用拷贝构造，编译器会把这个临时变量返回
    return tt;//返回值调用拷贝构造函数
}
int main()
{
    /*text1 a(5);
    text2 b(5);
    text3 c(5);
    text1 t1 = 5;//拷贝构造函数为私有
    text2 t2 = 5;
    text3 t3 = 5;//一个参数的构造函数为explicit
    //调用非explicit的一个参数的构造函数，必须要有拷贝构造函数,若拷贝构造函数不存在，如为私有，则此调用不成功。
    text1 t3(text1(5));//拷贝构造函数为私有
    text2 t4(text2(5));//有拷贝构造函数 但是只会调用一个参数的构造函数
    text3 t5(text3(5));
    //此调用也是只调用一个参数的构造函数，但是必须要有拷贝构造函数
    text1 t6= a;//拷贝构造寒素为私有
    text2 t7= b;
    text3 t8= c;//会调用拷贝构造函数
    text1 t9 = text1(5);//拷贝构造寒素为私有
    text2 t10 = text2(5);//调用一个参数的构造函数，但必须有拷贝构造函数
    text3 t11 = text3(5);//调用一个参数的构造函数，但必须有拷贝构造函数
    */
    text2 t12(5);
    my_test(t12);//实参传递调用拷贝构造函数
    return 0;
}
