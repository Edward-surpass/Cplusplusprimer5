/*********************************************************************************
*     File Name           :     17.1.1.cpp
*     Created By          :     edward
*     Creation Date       :     [2015-10-20 13:43]
*     Last Modified       :     [2015-10-20 13:45]
*     Description         :      
**********************************************************************************/
#include <tuple>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    std::tuple<int,int,std::string>tiis(2,3,"maomaochong");
    std::cout << std::get<2>(tiis) << std::endl;
    return 0;
}

