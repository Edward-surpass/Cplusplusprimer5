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
using namespace std;
class query_result;
class text_query{
private:
    shared_ptr<vector<string>> file;
    map<string,shared_ptr<set<vector<string>::size_type>>> wm;
public:
    text_query() = default;
    text_query(ifstream &);
    query_result query(const string &s)const;
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
    /*string text;
    while(getline(is,text))
    {
        file->push_back(text);
        int n = file->size()-1;
        istringstream line(text);
        string word;
        while(line >> word)
        {
            auto &lines = wm[word];
            if(!lines)
                lines.reset(new set<vector<string>::size_type>);
            lines->insert(n);
        }
    }*/
}
class query_result{
    friend ostream &print(ostream &o,const query_result &qr);
private:
    string sought;
    shared_ptr<set<vector<string>::size_type>> lines;
    shared_ptr<vector<string>> file;
public:
    query_result()=default;
    query_result(const string &s,const shared_ptr<set<vector<string>::size_type>> l,const shared_ptr<vector<string>> f):sought(s),lines(l),file(f){}
};
query_result text_query::query(const string &s)const
{
    auto p = wm.find(s);
    if(p == wm.end())
    {
        static shared_ptr<set<vector<string>::size_type>> nodata= make_shared<set<vector<string>::size_type>>();
        cout << "no date" << endl;
        return query_result(s,nodata,file);
    }
    return query_result(s,p->second,file);
}
ostream &print(ostream &o,const query_result &qr)
{
    for(auto e:*(qr.lines))
    {
        o << "(line" << e << ")" << (*qr.file)[e] << endl; 
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
    ifstream my_text("textexample");
    run_queries(my_text);
    return 0;
}
