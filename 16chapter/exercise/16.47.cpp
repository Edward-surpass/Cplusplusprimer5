#include <iostream>
#include <utility>
template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2)
{
   f(std::forward<T2>(t2),std::forward<T1>(t1));
}
void fun1(int &a,int &b)
{
    std::cout << a <<  " " << b++ << std::endl;
}
void fun(int &&a,int &&b)
{
    std::cout << a <<  " " << b << std::endl;
}
int main()
{
    int a = 2,b = 5;
    flip(fun1,a,b);
    flip(fun,std::move(a),std::move(b));
    std::cout << a << std::endl;
    return 0;
}
