#include <iostream>
#include <memory>
#include <vector>
using namespace std;
class String{
    friend ostream &operator<<(ostream &o,const String &str)
    {
        for(size_t i = 0;i < str.sz;++i)
            o << str.s[i];
        return o;
    }
private:
    char *s;
    size_t sz;
    void free();
public:
    allocator<char> alloc;
    String():s(nullptr),sz(0){}
    String(const char *);
    String(const String &);
    String &operator=(const String &);
    String &operator+(const String &);
    ~String();
};
String::String(const char *ch)
{
    size_t i = 0;
    for(;ch[i] != '\0';++i);
    sz = i;
    s = alloc.allocate(sz);
    i = 0;
    for(const char *p = s;i<sz;++i,++p)
    {
        alloc.construct(p,ch[i]);
    }
}
void String::free()
{
    for(char *p = s;p < s+sz;++p)
        alloc.destroy(p);
    alloc.deallocate(s,sz);
}
String::String(const String &str):sz(str.sz)
{
    s = alloc.allocate(sz);
    for(char *p = s,*q = str.s;p < s+sz;++p,++q)
        alloc.construct(p,*q);
    cout << "String(const String &)"<< str <<" is going" << endl;
}
String &String::operator=(const String &str)
{
    char *p = alloc.allocate(str.sz);
    char *q = p;
    for(size_t i = 0;i < str.sz; ++i)
        alloc.construct(q++,str.s[i]);
    free();
    s = p;
    sz = str.sz;
    cout << "operator= is going" << endl;
    return *this;

}
String &String::operator+(const String &str)
{
    size_t sz_temp = sz + str.sz;
    char *p = alloc.allocate(sz_temp);
    char *q = p;
    for(size_t i = 0;i < sz_temp; ++i)
    {
        if(i < sz)
            alloc.construct(q++,s[i]);
        else
            alloc.construct(q++,str.s[i-sz]);
    }
    free();
    s = p;
    sz = sz_temp;
    return *this;
}
String::~String()
{
    free();
}
int main()
{
    vector<String> vstr(4);
    cout << vstr.capacity() << endl;
    vstr.push_back("world");
    vstr.push_back("kkk");
    vstr.push_back("lll");
    return 0;
}
