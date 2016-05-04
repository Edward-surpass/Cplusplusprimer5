/*********************************************************************************
*     File Name           :     17.2.2.cpp
*     Created By          :     edward
*     Creation Date       :     [2016-03-23 18:38]
*     Last Modified       :     [2016-03-23 18:53]
*     Description         :      
**********************************************************************************/
#include <bitset>
#include <iostream>
int main(int argc, char *argv[])
{
    std::bitset<40> bitvec(3U);
    //std::cout << bitvec.any() << std::endl;
    //std::cout << bitvec.none() << std::endl;
    //std::cout << bitvec.all() << std::endl;
    //std::cout << bitvec.count() << std::endl;
    //std::cout << bitvec.size() << std::endl;
    //std::cout << bitvec.flip() << std::endl;
    //std::cout << bitvec.reset() << std::endl;
    //std::cout << bitvec.set() << std::endl;
    std::cout << bitvec.flip().to_ullong() << std::endl;
    return 0;
}

