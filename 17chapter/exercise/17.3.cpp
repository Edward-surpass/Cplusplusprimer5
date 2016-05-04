#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <memory>
#include <utility>
#include <initializer_list>
#include <map>
#include <set>
#include <vector>
#include <tuple>
using namespace std;
class query_result;
class text_query{
private:
    shared_ptr<vector<string>> file;
    map<string,shared_ptr<set<vector<string>::size_type>>> wm;
public:
    typedef shared_ptr<set<vector<string>::size_type>> line_ptr;
    typedef shared_ptr<vector<string>> file_ptr;
    text_query() = default;
    text_query(ifstream &);
    tuple<string,line_ptr, file_ptr> query(const string &s)const;
};
text_query::text_query(ifstream &is):file(new vector<string>)
{
    string line,word;
    int i = 0;
    file->push_back(" ");
    while(getline(is,line))
    {
        ++i;
        file->push_back(line);
        istringstream sin(line);
        while(sin>>word)
        {
            if(wm.find(word) == wm.end())
                wm[word] = make_shared<set<vector<string>::size_type>>();
            wm[word]->insert(i);
        }
    }
}
tuple<string, text_query::line_ptr, text_query::file_ptr> text_query::query(const string &s)const
{
    auto p = wm.find(s);
    if(p == wm.end())
    {
        static shared_ptr<set<vector<string>::size_type>> nodata= make_shared<set<vector<string>::size_type>>();
        cout << "no date" << endl;
        return tuple<string, text_query::line_ptr, text_query::file_ptr>(s,nodata,file);
    }
    return tuple<string, text_query::line_ptr, text_query::file_ptr>(s,p->second,file);
}
ostream &print(ostream &o,const tuple<string, text_query::line_ptr, text_query::file_ptr> &qr)
{
    for(auto e:*(std::get<1>(qr)))
    {
        o << "(line" << e << ")" << (*get<2>(qr))[e] << endl; 
    }
    return o;
}
void run_queries(ifstream &infile)
{
    text_query tq(infile);
    while(1)
    {
        cout << "enter word to look for,or q to quit:";
        string s;
        if(!(cin>>s)||s == "q") break;
        print(cout ,tq.query(s))<< endl;
    }
}
int main()
{
    ifstream my_text("17.3example");
    run_queries(my_text);
    return 0;
}
