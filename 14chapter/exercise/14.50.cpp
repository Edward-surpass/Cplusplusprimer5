#include<iostream>
using namespace std;
class long_double
{
public:
    long_double (double = 0.0){}
    operator double(){ cout << "double" << endl;return 0.1;}
    operator float(){cout << "float"<< endl;return 0.2;}
};
int main()
{
    long_double ld_obj;
    int ex1 = ld_obj;
    float ex2 = ld_obj;
}

