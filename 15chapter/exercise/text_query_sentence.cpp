#include "text_query_sentence.h"
text_query::text_query(ifstream &is):file(new vector<string>)
{
    string line,word,eassy = "",sen;
    int i = 0,pre = 0;
    file->push_back(" ");
    while(getline(is,line))
    {
        eassy += line;
        auto p = eassy.find('.',pre);
        if(p < eassy.size())
        {
            ++i;
            sen = eassy.substr(pre,p-pre+1);
            file->push_back(sen);
            istringstream sin(sen);
            while(sin>>word)
            {
                if(wm.find(word) == wm.end())
                    wm[word] = make_shared<set<vector<string>::size_type>>();
                wm[word]->insert(i);
            }
            pre = p+1;
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
        o << "(sentence" << e << ")" << (*qr.file)[e] << endl; 
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



