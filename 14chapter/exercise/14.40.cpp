#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class is_short
{
public:
    bool operator()(const string&a,const string &b)const
    {
        return a.size() < b.size();
    }
};
class big_sz
{
private:
    size_t sz;
public:
    big_sz(const size_t &i):sz(i){}
    bool operator()(const string &a)const{return a.size() >= sz;}
};
class print_str
{
private:
    ostream &os;
    char c;
public:
   print_str(ostream &os = cout, const char &c = ' '):os(os),c(c){} 
   void operator()(const string &s)
   {
       os << s << c;
   }
};
void biggies(vector<string> &words,vector<string>::size_type sz)
{
    sort(words.begin(),words.end());
    auto end_unique = unique(words.begin(),words.end());
    words.erase(end_unique,words.end());
    stable_sort(words.begin(),words.end(),is_short());
    auto wc = find_if(words.begin(),words.end(),big_sz(sz));
    auto count = words.end() - wc;
    for_each(wc,words.end(),print_str(cout,'*'));
    cout << endl;
}
int main()
{
    vector<string> vstr = {"sss","aa","sdfsadf"};
    biggies(vstr,3);
    return 0;
}
