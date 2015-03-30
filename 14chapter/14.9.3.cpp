#include <iostream>
#include <stdexcept>
using namespace std;
class small_int
{
friend small_int operator+(const small_int &,const small_int &);
public:
    explicit small_int(int i =0):val(i)
    {
        cout << "small_int()" << endl;
        if(i < 0||i>255)
            throw std::out_of_range("Bad small_int value");
    }
    operator int()const
    {
        cout << "operator() is going" << endl;
        return val;
    }        
private:
    size_t val;
};
small_int operator+(const small_int &lhs,const small_int &rhs)
{
    return std::move(small_int(lhs.val+rhs.val));
}
int main()
{
    small_int s1,s2;
    small_int s3 = s1 + s2;
    int i = s3 + 0;
    return 0;
}
