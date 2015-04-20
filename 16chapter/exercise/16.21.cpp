#include <memory>
#include <iostream>
#include <string>
class debug_delete{
    private:
        std::ostream &os;
    public:
        debug_delete(std::ostream & os = std::cerr):os(os){}
        template<typename T>
        void operator()(T *p)const
        {
            os << "deleting unique_ptr" << std::endl;
            delete p;
        }
};
int main()
{
    std::unique_ptr<int,debug_delete> p(new int(3),debug_delete());
    debug_delete del(std::cout);
    std::unique_ptr<std::string,debug_delete> q(new std::string("aaa"),del);
    int *p1 = new int(10);
    del(p1);
    return 0;
}
