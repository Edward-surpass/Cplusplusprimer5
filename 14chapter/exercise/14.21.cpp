#include "Sales_data.h"
int main()
{
    Sales_data sd1("001",22,10.2),sd2("001",12,10.8);
    std::cout << (sd1+=sd2) << std::endl;
    return 0;
}
