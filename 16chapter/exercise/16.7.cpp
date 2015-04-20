#include <iostream>
#include <typeinfo>
template <typename T,size_t N>
constexpr const size_t arr_size(const T (&arr)[N])
{
    return N;
}
int main()
{
    int a[] = {2,3,4,5};
    std::cout << arr_size(a) << std::endl;
}
