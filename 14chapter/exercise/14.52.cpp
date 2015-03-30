#include <iostream>
#include <stdexcept>
using namespace std;
class small_int
{
    friend class long_double;
friend small_int operator+(const small_int &,const small_int &);
public:
    small_int(int i =0):val(i)
    {
        cout << "small_int()" << endl;
        if(i < 0||i>255)
            throw std::out_of_range("Bad small_int value");
    }
    operator int()const
    {
        cout << "small_int operator() is going" << endl;
        return val;
    }        
private:
    size_t val;
};
class long_double
{
public:
    long_double operator+(const small_int &rhs)
    {
        cout << "成员函数long_double operator+" << endl;
        return std::move(long_double(dval + rhs.val));
    }
    long_double (double dval = 0.0):dval(dval){cout << "long_double()" << endl;}
    operator double(){ cout << "double" << endl;return 0.1;}
    operator float(){cout << "float"<< endl;return 0.2;}
private:
    double dval;
};
long_double operator+(long_double &lhs,double rhs)
{
    cout << "long_double operator+" << endl;
}
small_int operator+(const small_int &lhs,const small_int &rhs)
{
    cout << "small_int operator+ " << endl;
    return std::move(small_int(lhs.val+rhs.val));
}
int main()
{
    small_int s1;
    double d = s1 +3.14;
    return 0;
}
