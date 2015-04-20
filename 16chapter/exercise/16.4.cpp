#include <vector>
#include <iostream>
#include <list>
template<typename T,typename Q>
T find(const T &beg,const T &end,const Q &val)
{
    T b =beg;
    while(b < end && *b != val)
    {
        ++b;
    }
    return b;
}
int main()
{
    std::vector<int> a({2,3,4,5,6,7});
    std::cout << *find(a.begin(),a.end(),4) << std::endl;
    return 0;
}
