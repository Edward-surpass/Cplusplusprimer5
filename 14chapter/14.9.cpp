#include <iostream>
#include <stdexcept>
using namespace std;
class small_int
{
public:
    small_int(int i =0):val(i)
    {
        cout << "small_int()" << endl;
        if(i < 0||i>255)
            throw std::out_of_range("Bad small_int value");
    }
     explicit operator int()const
    {
        cout << "operator() is going" << endl;
        return val;
    }        
private:
    size_t val;
};
int main()
{
    small_int si = 3.14;
    si.operator int() + 5;
    static_cast<int>(si) + 4;
    return 0;
}
