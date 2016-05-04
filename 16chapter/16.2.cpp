#include <iostream>
#include <typeinfo>
#include <vector>
#include <type_traits>
template <typename T,typename Q = typename std::remove_reference<T>::type>
void fun(T &&)
{
    std::vector<Q> v;
    std::cout << typeid(T).name() << std::endl;
}
void fun1(const int c)
{
    std::cout << c << std::endl;
}
int main()
{
    int i =3;
    fun(i); 
    return 0;
}
