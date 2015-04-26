#include <iostream>
#include <memory>
#include <functional>
class debug_delete{
    private:
        std::ostream &os;
    public:
        debug_delete(std::ostream & os = std::cerr):os(os){}
        template<typename T>
        void operator()(T *p)const
        {
            os << "delete unique_ptr:" << std::endl;
            delete p;
        }
};
class default_delete{
    public:
        default_delete(){}
        template<typename T>
        void operator()(T *p)const
        {
            delete p;
        }
};
template<typename T>
class SharedPtr
{
    private:
        T *p;
        std::function<void(T *)> dev;
        std::size_t *use_cnt;
    public:
        SharedPtr();
        SharedPtr(T *pt,std::function<void(T *)> f);
        SharedPtr(T *pt);
        SharedPtr(const std::shared_ptr<T> &);
        SharedPtr(const SharedPtr &);
        SharedPtr &operator=(const SharedPtr &);
        SharedPtr &operator=(const std::shared_ptr<T> &);
        T &operator*(){
            return *p;
        }
        T *operator->()const{
            return &this->operator*();
        }
        ~SharedPtr();
};
template<typename T>
SharedPtr<T>::SharedPtr():p(nullptr),dev(nullptr),use_cnt(new size_t(0)){}
template<typename T>
SharedPtr<T>::SharedPtr(T *pt,std::function<void(T *)> f):p(pt),dev(f),use_cnt(new std::size_t(1)){}
template<typename T>
SharedPtr<T>::SharedPtr(T *pt):p(pt),dev(nullptr),use_cnt(new std::size_t(1)){}
template<typename T>
SharedPtr<T>::SharedPtr(const std::shared_ptr<T> &rhs):dev(nullptr),use_cnt(new std::size_t(1)){
    p = new T(*rhs);
}
template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr &rhs){
    use_cnt = rhs.use_cnt;
    ++*use_cnt;
    p = rhs.p;
    dev = rhs.dev;
}
template<typename T>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &rhs){
    SharedPtr<T> temp(rhs);
    if(!--*use_cnt)
    {
        dev?dev(p):(std::cout << "delete:" << std::endl, delete(p));
        delete use_cnt;
    }
    p = *temp.p;
    dev = temp.dev;
    use_cnt = temp.use_cnt;
    ++*use_cnt;
    return *this;
}
template<typename T>
SharedPtr<T> &SharedPtr<T>::operator=(const std::shared_ptr<T> &rhs)
{
    SharedPtr temp(rhs);
    return *this = temp;
}
template<typename T>
SharedPtr<T>::~SharedPtr(){
    std::cout << *p << " use_cnt:" << *use_cnt << std::endl;
    if(!--*use_cnt)
    {
        dev?dev(p):(std::cout << "delete:" << std::endl, delete(p));
        delete use_cnt;
    }
}
template <typename T,typename Q = default_delete>
class UniquePtr{
    private:
        T *p;
        Q dev = Q();
    public:
        UniquePtr():p(nullptr){}
        UniquePtr(Q q):p(nullptr),dev(q){}
        UniquePtr(T *pt):p(pt){}
        UniquePtr &operator=(const UniquePtr &);
        void reset(T *pt = nullptr);
        T *release(){
            std::cout << "release" << std::endl;
            T *pt = p;
            p = nullptr;
            return pt;
        }
        ~UniquePtr(){
            if(p)
                std::cout << "delete:" << *p << std::endl;
            else
                std::cout << "delete" << std::endl;
            dev(p);
        }
};
template<typename T>
void my_delete(T *p){
    std::cout << "my_deletle" << std::endl;
    delete p;
}
int main()
{
    auto q =std::function<void(int *)>(my_delete<int>);
    int *ps = new int(6);
    q(ps);
    return 0;
}
