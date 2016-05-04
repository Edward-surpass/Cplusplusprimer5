#include <memory>
#include <iostream>
#include <string>
template<typename T>
class vec{
    public:
        vec();
        vec(const vec &);
        vec &operator=(const vec &);
        ~vec();
        void push_back(const T &);
        template <typename ...Args>
        void emplace_back(Args &&...);
        std::size_t size()const{return first_free-elements;}
        std::size_t capacity()const{return cap - elements;}
        T *begin()const{return elements;}
        T *end()const{return first_free;}
    private:
        static std::allocator<T> alloc;
        void chk_n_alloc(){if(first_free == cap) reallocate();}
        std::pair<T *,T *> alloc_n_copy(const T*,const T*);
        void free();
        void reallocate();
        T *elements;
        T *first_free;
        T *cap;
};
template<typename T> 
std::allocator<T> vec<T>::alloc = std::allocator<T>();
template<typename T>
vec<T>::vec():elements(nullptr),first_free(nullptr),cap(nullptr){}
template<typename T>
vec<T>::vec(const vec &rhs){
    std::pair<T*,T*> paT = alloc_n_copy(rhs.elements,rhs.first_free);
    elements = paT.first;
    first_free = cap = paT.second;
}
template<typename T>
vec<T> &vec<T>::operator=(const vec &rhs){
    std::pair<T*,T*> paT = alloc_n_copy(rhs.elements,rhs.first_free);
    free();
    elements = paT.first;
    first_free = cap = paT.second;
    return *this;
}
template<typename T>
vec<T>::~vec(){
    free();
    first_free = cap = elements = nullptr;
}
template<typename T>
void vec<T>::push_back(const T &t){
    chk_n_alloc();
    alloc.construct(first_free++,t);
}
template<typename T>
template <typename ...Args>
void vec<T>::emplace_back(Args &&...rest){
    chk_n_alloc();
    alloc.construct(first_free++,std::forward<Args>(rest)...);
}
template<typename T>
std::pair<T *,T *> vec<T>::alloc_n_copy(const T *b,const T*e)
{
    T *p = alloc.allocate(e-b);
    return std::make_pair(p,uninitialized_copy(b,e,p));
}
template<typename T>
void vec<T>::free(){
    if(elements)
    {
        for(auto p = first_free;p != elements;)
        {
            alloc.destroy(--p);
        }
        alloc.deallocate(elements,cap-elements);
    }
}
template<typename T>
void vec<T>::reallocate()
{
    auto newcap = size()?2*size():1;
    auto newele = alloc.allocate(newcap);
    auto p = newele;
    for(auto q = elements;q != first_free; ++q)
        alloc.construct(p++,std::move(*q));
    free();
    elements = newele;
    first_free = p;
    cap = elements + newcap;
}
int main()
{
    vec<std::string> vi;
    vi.push_back("s");
    vi.push_back("e");
    vi.push_back("f");
    vi.push_back("w");
    vi.emplace_back(std::string("ppp"));
    vi.emplace_back(("safrp"));
    vi.emplace_back(10,'s');
    vec<std::string> vs(vi);
    vs = vs;
    for(auto p = vs.begin(); p != vs.end();++p)
        std::cout << *p << std::endl;
}
