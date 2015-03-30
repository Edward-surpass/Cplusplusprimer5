#include <iostream>
#include <vector>
#include <string>
using namespace std;
class input_string
{
    public:
    string operator()(istream &in = cin)
    {
        string s;
        if(getline(in,s))
        {
            return std::move(s);
        }
        else
            return string();
    }
};
int main()
{
    vector<string> vstr;
    while(cin)
    {
       vstr.push_back(input_string()());
    }
    for(auto &e:vstr)
        cout << e << " ";
    return 0;
}
