#include <iostream>
using namespace std;
class numbered{
private:
public:
    int mysn = 0;
    numbered():mysn(0){}
    numbered(const numbered &nm):mysn(nm.mysn+1){cout << "拷贝构造函数执行" << endl;}

};
void f(numbered s)
{
    cout << s.mysn << endl;
}
int main()
{
    numbered a,b=a,c=b;
    f(a);
    f(b);
    f(c);
    return 0;
}
