#include <iostream>
#include <vector>
template <typename T>
auto fcn3(T beg,T end)->decltype(*beg+0)
{
    return *beg;
}
int main()
{
    std::vector<std::string> vc({"sss","saf","sdgfsf"});
    std::cout << fcn3(vc.begin(),vc.end()) << std::endl;
    return 0;
}
