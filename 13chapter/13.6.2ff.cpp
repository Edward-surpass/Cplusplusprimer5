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
    void push_back(const std::string &);
    void push_back(std::string &&);
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
void str_vec::push_back(std::string &&s)
{
    chk_n_alloc();
    alloc.construct(first_free++,std::move(s));
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
    /*for(std::size_t i = 0;i<size();++i)
        alloc.construct(dest++,std::move(*elem++));*/
    std::string *last = uninitialized_copy(make_move_iterator(elements),make_move_iterator(first_free),dest);
    free();
    elements = new_data;
    first_free = last;
    cap = new_data+new_capacity;
}
int main()
{
    str_vec p;
    str_vec q({"a","b"});
    str_vec sv = q;
    p = sv;
    p.push_back("hello");
    p.push_back("world");
    p.push_back("std");
    std::cout << p << std::endl; 
    return 0;
}
