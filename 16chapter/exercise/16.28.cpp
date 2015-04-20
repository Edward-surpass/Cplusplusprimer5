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
            os << "deleting unique_ptr:"<< *p  << std::endl;
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
        dev?dev(p):(std::cout << "delete:" << *p << std::endl, delete(p));
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
        dev?dev(p):(std::cout << "delete:" << *p << std::endl, delete(p));
        delete use_cnt;
    }
}
int main()
{
    SharedPtr<int> spt1(new int(5),debug_delete());
    SharedPtr<std::string> spt2(std::make_shared<std::string>("sss"));
    SharedPtr<std::string> spt = spt2;
    SharedPtr<std::string> spt3(spt);
    std::cout << *spt << std::endl;
    return 0;
}
