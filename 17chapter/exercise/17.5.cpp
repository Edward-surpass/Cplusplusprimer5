/*********************************************************************************
*     File Name           :     17.1.2.cpp
*     Created By          :     edward
*     Creation Date       :     [2015-11-23 18:43]
*     Last Modified       :     [2015-12-21 15:36]
*     Description         :      
**********************************************************************************/
#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <algorithm>
#include "Sales_data.h"
typedef std::pair<std::vector<Sales_data>::const_iterator, std::vector<Sales_data>::const_iterator> pair_iter;
typedef std::pair<std::vector<Sales_data>::size_type, pair_iter> pair_num_piter;
std::vector<pair_num_piter> findBook(const std::vector<std::vector<Sales_data>> &files, const std::string &book)
{
    std::pair<std::vector<Sales_data>::size_type, pair_iter> res_temp;
    std::vector<pair_num_piter> ret;
    for (std::vector<std::vector<Sales_data>>::const_iterator it = files.cbegin();it != files.cend(); ++it) {
        std::pair<std::vector<Sales_data>::const_iterator, std::vector<Sales_data>::const_iterator> found = std::equal_range(it->cbegin(), it->cend(), book, compareIsbn);
        if(found.first != found.second)
        {
            res_temp=make_pair(it - files.cbegin(), make_pair(found.first, found.second));
            ret.push_back(res_temp);
        }
    }
    return std::move(ret);
}
void reportResults(std::istream &in, std::ostream &os, const std::vector<std::vector<Sales_data>> &files)
{
    std::string s;
    while(in >> s)
    {
        std::vector<pair_num_piter> trans = findBook(files,s);
        if(trans.empty())
        {
            os << s << "not found in any store" << std::endl;
        }
        else
        {
            for( auto &it :trans)
            {
                os << "store" << it.first << " sales: " << std::accumulate(it.second.first, it.second.second,Sales_data(s)) << std::endl;
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
