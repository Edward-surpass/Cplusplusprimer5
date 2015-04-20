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
