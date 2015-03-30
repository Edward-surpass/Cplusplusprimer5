#include <iostream>
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
    string str = input_string()();
    cout << str << endl;
    return 0;
}
