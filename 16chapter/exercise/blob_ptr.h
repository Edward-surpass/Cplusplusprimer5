#ifndef _BLOB_PTR_H
#define _BLOB_PTR_H 
#include <iostream>
#include <vector>
#include <memory>
template<typename>
class Blob;
template<typename >
class blob_ptr;
template<typename T>
bool operator==(const Blob<T> &,const Blob<T> &);
template <typename T>
class Blob
{
    friend class blob_ptr<T>;
    friend bool operator==<T>(const Blob<T>&,const Blob<T>&);
    typedef typename std::vector<T>::size_type size_type;
    private:
        std::shared_ptr<std::vector<T>> data;
        void check(const typename std::vector<T>::size_type &i, const std::string &msg)const;
    public:
        Blob():data(std::make_shared<std::vector<T>>() ) {}
        Blob(std::initializer_list<T> il):data(std::make_shared<std::vector<T>>(il)){}
        size_type size()const{return data -> size();}
        bool empty()const {return data -> empty();}
        void push_back(const T &t){data->push_back(t);}
        void push_back(T &&t){data->push_back(std::move(t));}
        void pop_back();
        T &back();
        T &operator[](const size_type &);
};
template<typename T>
class blob_ptr{
    private:
        std::shared_ptr<std::vector<T>> check(const typename std::vector<T>::size_type &i,const std::string &)const;
        std::weak_ptr<std::vector<T>> wptr;
        typename std::vector<T>::size_type curr;
    public:
        blob_ptr();
        blob_ptr(Blob<T> &a, const typename std::vector<T>::size_type &i):wptr(a.data),curr(i){}
        T &operator*()const
        {
            std::shared_ptr<std::vector<T>> p = blob_ptr<T>::check(curr,"dereference past end");
            return (*p)[curr];
        }    
        blob_ptr &operator++();
        blob_ptr &operator--();
        blob_ptr operator++(int);
        blob_ptr operator--(int);
};
#endif
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
    retrun (*data)[i];
}
template<typename T>
bool operator==(const Blob<T> &lhs,const Blob<T> &rhs)
{
    return *lhs.data == *rhs.data;
}
template<typename T>
blob_ptr<T>::blob_ptr():wptr(nullptr),curr(0){}
template<typename T>
std::shared_ptr<std::vector<T>> blob_ptr<T>::check(const typename std::vector<T>::size_type &i,const std::string &msg)const
{
    std::shared_ptr<std::vector<T>> p = wptr.lock();
    if(!p)
        throw std::runtime_error("unbound blob_ptr");
    if(i > p->size())
        throw std::out_of_range(msg);
    else
        return p;
}
template<typename T>
blob_ptr<T> &blob_ptr<T>::operator++()
{
    blob_ptr<T>::check(curr,"increment past end of blob_ptr");
    ++curr;
    return *this;
}
template<typename T>
blob_ptr<T> &blob_ptr<T>::operator--()
{
    check(0,"decrement past begin of blob_ptr");
    --curr;
    return *this;
}
template<typename T>
blob_ptr<T> blob_ptr<T>::operator++(int)
{
    blob_ptr<T> temp(*this);
}
