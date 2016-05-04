/*********************************************************************************
*     File Name           :     17.3.1.cpp
*     Created By          :     edward
*     Creation Date       :     [2016-03-23 19:47]
*     Last Modified       :     [2016-03-26 21:03]
*     Description         :      
**********************************************************************************/
#include <iostream>
#include <regex>
#include <string>
int main(int argc, char *argv[])
try{

    std::string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    std::regex r(pattern);
    std::smatch result;
    std::string test_str("receipt freind theif receive");
    if(std::regex_search(test_str, result, r))
    {
        std::cout << result.str() << std::endl;
    }
    pattern = "[[:alnum:]]+\\.(cpp|cc|cxx)";
    std::regex re(pattern, std::regex::icase);
    std::string filename;
    while(std::cin >> filename)
    {
        if(std::regex_search(filename, result, re));
        {
            std::cout << result.str() << std::endl;
        }
    }

    return 0;
}catch (std::regex_error e){
    std::cout << e.what() << "\n"<< e.code() << std::endl;
}


