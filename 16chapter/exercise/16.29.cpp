#include "SharedPtr.h"
#include <iostream>
#include <vector>
#include <memory>
template<typename>
class Blob;
template<typename T>
bool operator==(const Blob<T> &,const Blob<T> &);
template <typename T>
class Blob
{
    friend bool operator==<T>(const Blob<T>&,const Blob<T>&);
    typedef typename std::vector<T>::size_type size_type;
    private:
        SharedPtr<std::vector<T>> data;
        void check(const typename std::vector<T>::size_type &i, const std::string &msg)const;
    public:
        Blob():data(std::make_shared<std::vector<T>>() ) {}
        Blob(std::initializer_list<T> il):data(std::make_shared<std::vector<T>>(il),debug_delete()){}
        size_type size()const{return data -> size();}
        bool empty()const {return data -> empty();}
        void push_back(const T &t){data->push_back(t);}
        void push_back(T &&t){data->push_back(std::move(t));}
        void pop_back();
        T &back();
        T &operator[](const size_type &);
};
template<typename T>
void Blob<T>::check(const typename std::vector<T>::size_type &i,const std::string &msg)const
{
    if(i >= data-> size())
        throw std::out_of_range(msg);
}
template<typename T>
void Blob<T>::pop_back()
{
    check(0,"pop_back on empty Blob");
    data->pop_back();
}
template<typename T>
T &Blob<T>::back()
{
    check(0,"back on empty Blob");
    return data->back();
}
template<typename T>
T &Blob<T>::operator[](const size_type &i)
{
    check(i,"subscript out of range");
    return (*data)[i];
}
template<typename T>
bool operator==(const Blob<T> &lhs,const Blob<T> &rhs)
{
    return *lhs.data == *rhs.data;
}
int main()
{
    Blob<int> bi({1,2,3,34,7});
    bi.push_back(8);
    for(std::size_t i = 0;i<bi.size();++i)
        std::cout << bi[i] << " ";
    Blob<std::string> bs({"asdf","sdakjg"});
    for(std::size_t i = 0;i<bs.size();++i)
        std::cout << bs[i] << " ";
    std::cout << std::endl;
    std::cout << bs.back() << std::endl;
    Blob<std::string> bsc(bs);
    for(std::size_t i = 0;i<bs.size();++i)
        std::cout << bs[i] << " ";
    std::cout << std::endl;
    return 0;
}
