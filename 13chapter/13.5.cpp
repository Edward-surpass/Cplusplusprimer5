#include <string>
#include <memory>
#include <iostream>
class str_vec{
private:
    std::string *elements;
    std::string *first_free;
    std::string *cap;
    std::allocator<std::string> alloc;
    std::pair<std::string*,std::string*> alloc_n_copy(const std::string *,const std::string *);
    void free();
    void chk_n_alloc(){if(size() == capacity()) reallocate();}
    void reallocate();
public:
    str_vec():elements(nullptr),first_free(nullptr),cap(nullptr){}
    str_vec(const str_vec &);
    str_vec &operator=(const str_vec &);
    ~str_vec();
    std::string *begin(){return elements;}
    std::string *end(){return first_free;}
    std::size_t size(){return first_free-elements;}
    std::size_t capacity(){return cap-elements;}
    void push_back(const std::string &);
};
void str_vec::push_back(const std::string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++,s);
}
std::pair<std::string*,std::string*> str_vec::alloc_n_copy(const std::string *b,const std::string *e)
{
    std::string *p = alloc.allocate(e-b);
    return make_pair(p,uninitialized_copy(b,e,p));
}
void str_vec::free()
{
    if(elements)
    {
        for(auto *p = first_free;p > first_free;)
            alloc.destroy(--p);
        alloc.deallocate(elements,cap-elements);

    }
}
str_vec::str_vec(const str_vec &s)
{
    std::pair<std::string*,std::string*> p = alloc_n_copy(s.elements,s.first_free);
    elements = p.first;
    cap = first_free = p.second;
}
str_vec &str_vec::operator=(const str_vec &s)
{
    auto newdata = alloc_n_copy(s.elements,s.first_free);
    free();
    elements = newdata.first;
    cap = first_free = newdata.second;
    return *this;
}
str_vec::~str_vec()
{
    free();
}
void str_vec::reallocate()
{
    size_t newcapacity = size()>1?2*size():1;
    std::string *newdata = alloc.allocate(newcapacity);
    std::string *elem = elements;
    std::string *dest = newdata;
    for(size_t i = 0; i  < this->size();++i)
        alloc.construct(dest++,std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}
int main()
{
    return 0;
}
