#include <iostream>
template <typename T,size_t N>
void print(const T(&arr)[N])
{
    for(auto &e:arr)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}
int main()
{
    int a[] = {1,2,3,4,5};
    print(a);
    return 0;
}
