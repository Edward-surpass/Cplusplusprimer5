#include <iostream>
#include <string>
#include <memory>
template <typename T>
int compare(const T &v1, const T &v2)
{
    if(v1 < v2) return -1;
    else return v1 >v2;
}
int main()
{
    std::cout << compare<std::string>("b","c") << std::endl;

}
