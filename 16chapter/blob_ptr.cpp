#include "blob_ptr.h"
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
    ++*this;
    return temp;
}
template<typename T>
blob_ptr<T> blob_ptr<T>::operator--(int)
{
    blob_ptr<T> temp(*this);
    --*this;
    return temp;
}
