#include "text_query.h"
text_query::text_query(ifstream &is):file(new vector<string>,debug_delete(std::cout))
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
                wm[word] = shared_ptr<set<vector<string>::size_type>>(new set<vector<string>::size_type>,debug_delete());
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
query_result text_query::query(const string &s)const
{
    auto p = wm.find(s);
    if(p == wm.end())
    {
        static shared_ptr<set<vector<string>::size_type>> nodata(new set<vector<string>::size_type>,debug_delete());
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
query_result::query_result(const string &s,const shared_ptr<set<vector<string>::size_type>> l,const shared_ptr<vector<string>> f):sought(s),lines(l),file(f){}

set<vector<string>::size_type>::iterator query_result::begin()
{
    return lines->begin();
}
set<vector<string>::size_type>::iterator query_result::end()
{
    return lines->end();
}
shared_ptr<vector<string>> query_result::get_file()
{
    return file;
}



