/*********************************************************************************
*     File Name           :     new-handler.cpp
*     Created By          :     edward
*     Creation Date       :     [2015-11-23 10:30]
*     Last Modified       :     [2015-11-23 15:45]
*     Description         :      
**********************************************************************************/
#include <iostream>
#include <new>
class NewHandlerHolder{
    public:
        NewHandlerHolder(std::new_handler p);
        NewHandlerHolder(const NewHandlerHolder &) = delete;
        NewHandlerHolder &operator=(const NewHandlerHolder &) = delete;
        ~NewHandlerHolder();
    private:
        std::new_handler currentHandler;
};
NewHandlerHolder::NewHandlerHolder(std::new_handler p):currentHandler(p)
{
}
NewHandlerHolder::~NewHandlerHolder(){
    std::set_new_handler(currentHandler);
}
template <typename T>
class NewHandlerSupport{
    public:
        static std::new_handler set_new_handler(std::new_handler)throw();
        static void* operator new(size_t size)throw (std::bad_alloc);
    private:
        static std::new_handler currentHandler;
};
template<typename T>
std::new_handler NewHandlerSupport<T>::currentHandler = 0;
template <typename T>
std::new_handler NewHandlerSupport<T>::set_new_handler(std::new_handler p)throw()
{
    std::new_handler old_handler = currentHandler;
    currentHandler = p;
    return old_handler;
}
template <typename T>
void* NewHandlerSupport<T>::operator new(size_t size)throw(std::bad_alloc)
{
    NewHandlerHolder(std::set_new_handler(currentHandler));
    return ::operator new(size);
}
class Bmm : public NewHandlerSupport<Bmm>{
    public:
        Bmm(){
            std::cout << "Bmm" << std::endl;
        }
        ~Bmm(){
            std::cout << "~Bmm" << std::endl;
        }
    private:
        int b;
};
void outOfMem(){
    std::cerr << "Unable to satisfy request for memory" << std::endl;
    std::abort();
}
int main(int argc, char *argv[])
{
    Bmm::set_new_handler(outOfMem);
    int size = sizeof(Bmm);
    Bmm *bmm = new Bmm[100000000000];
    return 0;
}
