#include <string>
#include <vector>
#include <initializer_list>
#include <utility>
#include <iostream>
#include <memory>
class str_vec{
    friend std::ostream &operator<<(std::ostream &o,const str_vec &vc)
    {
        for(auto p = vc.elements;p < vc.first_free;++p)
            o << *p << " ";
        return o;
    }
    friend bool operator==(const str_vec &,const str_vec &);
    friend bool operator<(const str_vec &,const str_vec &);
    friend bool operator!=(const str_vec &,const str_vec &);
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
    std::string &operator[](const std::size_t n )
    {
        if(n >= static_cast<std::size_t>(first_free - elements)) 
            throw "out of range";
        return elements[n];
    }
    const std::string &operator[](const std::size_t n)const{return elements[n];}
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
    auto new_capacity = size()>1?size()*2:1;
    auto new_data = alloc.allocate(new_capacity);
    auto dest = new_data;
    auto elem = elements;
    for(std::size_t i = 0;i<size();++i)
        alloc.construct(dest++,std::move(*elem++));
    free();
    elements = new_data;
    first_free = dest;
    std::cout << cap - elements << std::endl;
    cap = new_data+new_capacity;
}
bool operator==(const str_vec &lhs,const str_vec &rhs)
{
    return lhs.first_free == rhs.first_free && lhs.elements == rhs.elements;
}
bool operator!=(const str_vec &lhs,const str_vec &rhs)
{
    return !(lhs == rhs);
}
bool operator<(const str_vec &lhs,const str_vec &rhs)
{
    return std::vector<std::string>(lhs.elements,lhs.first_free) < std::vector<std::string>(rhs.elements,rhs.first_free);
}
int main()
{
    str_vec p;
    str_vec q({"a","b"});
    str_vec sv = q;
    p.push_back("hello");
    std::cout << p[2] << std::endl;
    return 0;
}
