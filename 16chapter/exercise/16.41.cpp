#include <iostream>
#include <type_traits>
template <typename T>
auto sum(T lhs, T rhs) -> decltype(lhs+rhs)
{
    return lhs+rhs;
}
int main()
{
    sum(1,3);
}
