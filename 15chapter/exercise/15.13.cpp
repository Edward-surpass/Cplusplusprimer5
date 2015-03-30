#include <iostream>
#include <string>
using namespace std;
class base
{
private:
    string basename = "hello";
public:
    string name(){return basename;}
    virtual void print(ostream &os){os << basename;}
};
class derived : public base
{
private:
    int i = 0;
public:
    virtual void print(ostream &os)override{base::print(os);os << " " << i;}
};
int main()
{
    derived dobj;
    base &br2 = dobj;
    br2.print(std::cout);
    br2.name();
    return 0;
}
