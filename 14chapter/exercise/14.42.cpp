#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;
class print_vi
{
public:
    void operator()(const int &i)
    {
        cout << i << " ";
    }

};
int main()
{
    vector<int> vi = {1,2,3,1025,2342,2222,234235,3222};
    unsigned count = count_if(vi.begin(),vi.end(),bind(greater<int>(),std::placeholders::_1,1024));
    cout << count << endl;
    vector<string> vs = {"pooh","pooh","asdf","pioiop"};
    vector<string>::iterator temps = find_if(vs.begin(),vs.end(),bind(not_equal_to<string>(),std::placeholders::_1,"pooh"));
    cout << *temps << endl;
    for_each(vi.begin(),vi.end(),[](int &i)->int{i = i*2;return i;});
    for_each(vi.begin(),vi.end(),print_vi());
    cout << endl;
    cout << multiplies<int>()(3,4) << endl;
    return 0;
}
