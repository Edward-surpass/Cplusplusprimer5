#ifndef _TEXT_QUERY_H
#define _TEXT_QUERY_H
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <sstream>
using namespace std;
class debug_delete{
    private:
        std::ostream &os;
    public:
        debug_delete(std::ostream & os = std::cerr):os(os){}
        template<typename T>
        void operator()(T *p)const
        {
            os << "deleting unique_ptr" << std::endl;
            delete p;
        }
};
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
class query_result{
    friend ostream &print(ostream &o,const query_result &qr);
private:
    string sought;
    shared_ptr<set<vector<string>::size_type>> lines;
    shared_ptr<vector<string>> file;
public:
    query_result()=default;
    query_result(const string &s,const shared_ptr<set<vector<string>::size_type>> l,const shared_ptr<vector<string>> f);
    set<vector<string>::size_type>::iterator begin();
    set<vector<string>::size_type>::iterator end();
    shared_ptr<vector<string>> get_file();
};
#endif
