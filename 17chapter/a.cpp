/*********************************************************************************
*     File Name           :     a.cpp
*     Created By          :     edward
*     Creation Date       :     [2016-03-26 20:14]
*     Last Modified       :     [2016-03-26 20:28]
*     Description         :      
**********************************************************************************/

#include <iostream>

struct size_m{
    int * c;
    int a;
    char i;
};
int main(int argc, char *argv[])
{
    char b[5];
    char *a;
    std::cout << sizeof(size_m) << std::endl;
    return 0;
}
