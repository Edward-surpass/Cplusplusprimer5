#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;
class div_int
{
private:
    int a;
public:
    div_int(int i):a(i){}
    bool operator()(int &i){return modulus<int>()(i,a) == 0;}
};
int main()
{
    vector<int> vi = {2,4,6,8};
    cout<<((find_if_not(vi.begin(),vi.end(),div_int(2)) == vi.end())?1:0) << endl;
    return 0;
}
