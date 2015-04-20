#include <iostream>
#include <typeinfo>
template <typename T,size_t N>
T *begin(T (&arr)[N])
{
    return arr+0;
}
template <typename T,size_t N>
T *end(T (&arr)[N])
{
    return arr+N;
}
template <typename T,size_t N>
const T *cbegin(const T (&arr)[N])
{
    return arr+0;
}
template <typename T,size_t N>
const T *cend(const T (&arr)[N])
{
    return arr+N;
}
int main()
{
    int a[] = {2,3,4,5};
    const int *p = begin(a);
    for(;p != end(a);++p)
        std::cout << *p << " ";
    std::cout << std::endl;
}
