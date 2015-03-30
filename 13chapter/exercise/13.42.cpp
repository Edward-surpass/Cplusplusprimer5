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
class str_vec{
    friend std::ostream &operator<<(std::ostream &o,const str_vec &vc)
    {
        for(auto p = vc.elements;p < vc.first_free;++p)
            o << *p << " ";
        return o;
    }
private:
    static std::allocator<std::string> alloc;
    std::string *elements;
    std::string *first_free;
    std::string *cap;
    std::pair<std::string*,std::string*> alloc_n_copy(std::string *,std::string*);
    void free();
    void reallocate();
    void chk_n_alloc(){if(size() == capacity()) reallocate();}
public:
    str_vec():elements(nullptr),first_free(nullptr),cap(nullptr){}
    str_vec(const str_vec &);
    str_vec(const std::initializer_list<std::string> &);
    str_vec &operator=(const str_vec &);
    std::string &operator[](const size_t &i){return elements[i];}
    void push_back(const std::string &);
    std::string *begin(){return elements;}
    std::string *end(){return first_free;}
    std::size_t size(){return first_free-elements;} 
    std::size_t capacity(){return cap-elements;}
};
std::allocator<std::string> str_vec::alloc = std::allocator<std::string>();
str_vec::str_vec(const std::initializer_list<std::string> &s)
{
    auto r = alloc_n_copy((std::string *)s.begin(),(std::string *)s.end());
    elements = r.first;
    cap = first_free = r.second;
}
std::pair<std::string*,std::string*> str_vec::alloc_n_copy(std::string *b,std::string *e)
{
    std::string *p= alloc.allocate(e-b);
    return make_pair(p,uninitialized_copy(b,e,p));
}
void str_vec::free()
{
    for(std::string *p = first_free;p > elements;)
        alloc.destroy(--p);
    alloc.deallocate(elements,cap-elements);
}
void str_vec::push_back(const std::string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++,s);
}
str_vec::str_vec(const str_vec &vc)
{
    auto p = alloc_n_copy(vc.elements,vc.first_free);
    elements = p.first;
    cap = first_free = p.second;
}
str_vec &str_vec::operator=(const str_vec &vc)
{
    auto p = alloc_n_copy(vc.elements,vc.first_free);
    free();
    elements = p.first;
    first_free = cap = p.second;
    return *this;
}
void str_vec::reallocate()
{
    auto new_capacity = size()?size()*2:1;
    auto new_data = alloc.allocate(new_capacity);
    auto dest = new_data;
    auto elem = elements;
    for(std::size_t i = 0;i<size();++i)
        alloc.construct(dest++,std::move(*elem++));
    free();
    elements = new_data;
    first_free = dest;
    cap = new_data+new_capacity;
    std::cout << cap - elements << std::endl;
}
using namespace std;
class query_result;
class text_query{
private:
    shared_ptr<str_vec> file;
    map<string,shared_ptr<set<size_t>>> wm;
public:
    text_query() = default;
    text_query(ifstream &);
    query_result query(const string &s)const;
};
text_query::text_query(ifstream &is):file(new str_vec)
{
    /*string line,word;
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
                wm[word] = make_shared<set<size_t>>();
            wm[word]->insert(i);
        }
    }*/
    string text;
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
                lines.reset(new set<size_t>);
            lines->insert(n);
            cout << "word:" << word << "line:" << n << endl;
        }
    }
}
class query_result{
    friend ostream &print(ostream &o,const query_result &qr);
private:
    string sought;
    shared_ptr<set<size_t>> lines;
    shared_ptr<str_vec> file;
public:
    query_result()=default;
    query_result(const string &s,const shared_ptr<set<size_t>> l,const shared_ptr<str_vec> f):sought(s),lines(l),file(f){}
};
query_result text_query::query(const string &s)const
{
    auto p = wm.find(s);
    if(p == wm.end())
    {
        static shared_ptr<set<size_t>> nodata= make_shared<set<size_t>>();
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
    ifstream my_text("13.42example");
    run_queries(my_text);
    return 0;
}
