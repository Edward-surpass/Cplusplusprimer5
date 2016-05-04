/*********************************************************************************
*     File Name           :     17.3.1.cpp
*     Created By          :     edward
*     Creation Date       :     [2016-03-23 19:47]
*     Last Modified       :     [2016-03-26 21:12]
*     Description         :      
**********************************************************************************/
#include <iostream>
#include <regex>
#include <string>
int main(int argc, char *argv[])
try{

    std::string pattern("eic");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    std::regex r(pattern);
    std::smatch result;
    std::string test_str;
    while(std::cin >> test_str)
    {
        if(!std::regex_search(test_str, result, r))
        {
            std::cout << test_str << std::endl;
        }
        else{
            std::cout << "word err" << std::endl;
        }
    }

    return 0;
}catch (std::regex_error e){
    std::cout << e.what() << "\n"<< e.code() << std::endl;
}


