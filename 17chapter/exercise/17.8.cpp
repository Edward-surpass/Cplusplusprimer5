/*********************************************************************************
*     File Name           :     17.1.2.cpp
*     Created By          :     edward
*     Creation Date       :     [2015-11-23 18:43]
*     Last Modified       :     [2015-12-21 15:50]
*     Description         :      
**********************************************************************************/
#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <algorithm>
#include "Sales_data.h"
typedef std::tuple<std::vector<Sales_data>::size_type, std::vector<Sales_data>::const_iterator, std::vector<Sales_data>::const_iterator> mathes;
std::vector<mathes> findBook(const std::vector<std::vector<Sales_data>> &files, const std::string &book)
{
    std::vector<mathes> ret = std::vector<mathes> ();
    for (std::vector<std::vector<Sales_data>>::const_iterator it = files.cbegin();it != files.cend(); ++it) {
        std::pair<std::vector<Sales_data>::const_iterator, std::vector<Sales_data>::const_iterator> found = std::equal_range(it->cbegin(), it->cend(), book, compareIsbn);
        if(found.first != found.second)
        {
            ret.push_back(make_tuple(it-files.cbegin(), found.first, found.second));
        }
    }
    return std::move(ret);
}
void reportResults(std::istream &in, std::ostream &os, const std::vector<std::vector<Sales_data>> &files)
{
    std::string s;
    while(in >> s)
    {
        std::vector<mathes> trans = findBook(files, s);
        if(trans.empty())
        {
            os << s << "not found in any store" << std::endl;
        }
        else
        {
            for(const auto &it: trans)
            {
                os << "store" << std::get<0>(it) << " sales: " << std::accumulate(std::get<1>(it), std::get<2>(it), Sales_data()) << std::endl;
            }
        }
    }
}
int main(int argc, char *argv[])
{
    std::vector<std::vector<Sales_data>> files = {{{"a", 1, 0.8},{"b", 2,0.5}}, {{"a",2,0.7}}};
    reportResults(std::cin, std::cout, files);
    return 0;
}
