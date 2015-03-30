#include <iostream>
using namespace std;
int main()
{
    plus<int> int_add;
    negate<int> int_negate;
    int sum = int_add(10,20);
    sum = int_negate(int_add(10,20));
    cout << sum << endl;
    sum = int_add(10,int_negate(10));
}
