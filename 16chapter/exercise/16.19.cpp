#include <vector>
#include <iostream>
template<typename T>
void print(const T &t)
{
    for(typename T::size_type p = 0; p < t.size();++p)
        std::cout << t[p] << " ";
}
int main()
{
    std::vector<std::string> vs({"qwerL","dddd","slagj"});
    print(vs);
    std::cout << std::endl;
    return 0;
}
