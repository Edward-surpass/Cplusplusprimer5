#include <string>
#include <iostream>
#include <memory>
#include <vector>
template<typename T>
class Blob;
template<typename T>
std::ostream &operator<<(std::ostream &os,const Blob<T> &rhs);
template<typename T>
class Blob{
    friend std::ostream &operator<<<T>(std::ostream &os,const Blob<T> &rhs);
    public:
        template<typename It>
            Blob(It b,It e);
        ~Blob(){
            for(T *p = end;p != data;)
                alloc.destroy(--p);
            alloc.deallocate(data,end-data);
        }
    private:
        static std::allocator<T> alloc; //静态成员变量的声明 
        T *data;
        T *end;
};
template<typename T>
std::allocator<T> Blob<T>::alloc = std::allocator<T>();
template<typename T>
template<typename It>
Blob<T>::Blob(It b,It e){
    data = alloc.allocate(e-b);
    end = uninitialized_copy(b,e,data);
}
template<typename T>
std::ostream &operator<<(std::ostream &os,const Blob<T> &rhs)
{
    for(auto p = rhs.data;p != rhs.end; ++p)
        os << *p << " ";
    return os;
}
int main()
{
    std::vector<std::string> vs({"sss","bbb"});
    Blob<std::string> bs(vs.begin(),vs.end());
    std::cout << bs << std::endl;
}
