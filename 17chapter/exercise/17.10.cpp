/*********************************************************************************
*     Last Modified       :     [2015-12-26 14:15]
*     Description         :      
**********************************************************************************/
#include <bitset>
#include <iostream>
int main(int argc, char *argv[])
{
    std::bitset<32> bitvec(0x20212e);
    std::bitset<32> bitvec1(010020456);
    std::cout << bitvec << "\n" << bitvec1 << std::endl;
    std::cout << 0ULL << std::endl;
    bitvec.reset();
    unsigned i;
    while(std::cin >> i)
    {
        bitvec.set(i);
    }
    std::cout << bitvec << std::endl;
    return 0;
}

