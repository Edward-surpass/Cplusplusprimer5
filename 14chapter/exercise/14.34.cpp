#include <iostream>
#include <string>
using namespace std;
class if_then_else
{
public:
template<typename T,typename Q>
    Q operator()(const T &t,const Q &qf, const Q &qb){
        if(t)
            return qf;
        else 
            return qb;
    }
};
int main()
{
    if_then_else ite;
    cout << ite(0,string("true"),string("world")) << endl;
}
