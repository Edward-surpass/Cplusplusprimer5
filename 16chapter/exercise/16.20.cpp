#include <vector>
#include <iostream>
#include <typeinfo>
void print(const  std::vector<std::string> &t)
{
    for(std::vector<std::string>::const_iterator p = t.begin(); p != t.end();++p)
    {
        std::cout << *p << " ";
    }
}
int main()
{
    std::vector<std::string> vs({"qwerL","dddd","slagj"});
    print(vs);
    std::cout << std::endl;
    return 0;
}
