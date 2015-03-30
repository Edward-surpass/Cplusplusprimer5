#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;
class is_in
{
private:
    unsigned sz;
public:
    is_in(const unsigned &i):sz(i){}
    bool operator()(const string &s){return s.size() == sz;}
};
int main()
{
    string s;
    vector<int> a(10,0);
    ifstream ifs("14.38example");
    while(ifs >> s)
    {
        if(is_in(1)(s))
            ++a[0];
        else if(is_in(2)(s))
            ++a[1];
        else if(is_in(3)(s))
            ++a[2];
        else if(is_in(4)(s))
            ++a[3];
        else if(is_in(5)(s))
            ++a[4];
        else if(is_in(6)(s))
            ++a[5];
        else if(is_in(7)(s))
            ++a[6];
        else if(is_in(8)(s))
            ++a[7];
        else if(is_in(9)(s))
            ++a[8];
        else if(is_in(10)(s))
            ++a[9];
    }
    for(size_t i = 0; i < 10;++i)
        cout << a[i] << " ";
    return 0;
}
