#include <iostream>
#include <memory>
using namespace std;
class String{
    friend ostream &operator<<(ostream &o,const String &str)
    {
        for(size_t i = 0;i < str.sz;++i)
            o << str.s[i];
        return o;
    }
    friend bool operator==(const String &,const String &);
    friend bool operator!=(const String &,const String &);
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
bool operator==(const String &lhs,const String &rhs)
{
    return lhs.s == rhs.s && lhs.sz == rhs.sz;
}
bool operator!=(const String &lhs,const String &rhs)
{
    return !(lhs == rhs);
}
int main()
{
    const char *cha = "hello";
    String s1(cha);
    String s2 = s1;
    cout << s2+s1 << endl;
}
