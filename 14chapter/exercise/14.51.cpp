#include<iostream>
using namespace std;
class long_double
{
public:
    long_double (double = 0.0){}
    operator double(){ cout << "double" << endl;return 0.1;}
    operator float(){cout << "float"<< endl;return 0.2;}
    
};
void calc(int)
{
    cout << "int" << endl;
}
void calc(long_double)
{
    cout << "long_double" << endl;
}
int main()
{
    double dval;
    calc(dval);
    return 0;
}

