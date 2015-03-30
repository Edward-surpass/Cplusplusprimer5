#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
class is_equal
{
    public:
bool operator()(const int &a,const int &b)
{
    return a == b;
}
};
int main()
{
    vector<int> vi({1,2,3,4,5,6,1,2,3});
    sort(vi.begin(),vi.end());
    for(auto &e:vi)
        cout << e << " ";
    cout << "================" << endl;
    auto p = unique(vi.begin(),vi.end(),is_equal());
    for(auto &e:vi)
        cout << e << " ";
    return 0;
}
