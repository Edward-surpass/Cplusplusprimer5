/*********************************************************************************
*     File Name           :     17.1.2.cpp
*     Created By          :     edward
*     Creation Date       :     [2015-11-23 18:43]
*     Last Modified       :     [2015-12-21 15:49]
*     Description         :      
**********************************************************************************/
#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <algorithm>
#include "Sales_data.h"
typedef std::vector<Sales_data>::const_iterator vec_const_iter;
void findBook(const std::vector<std::vector<Sales_data>> &files, const std::string &book, std::vector<std::vector<Sales_data>::size_type> &sa, std::vector<vec_const_iter> &beg_iter, std::vector<vec_const_iter> &end_iter)
{
    for (std::vector<std::vector<Sales_data>>::const_iterator it = files.cbegin();it != files.cend(); ++it) {
        std::pair<std::vector<Sales_data>::const_iterator, std::vector<Sales_data>::const_iterator> found = std::equal_range(it->cbegin(), it->cend(), book, compareIsbn);
        if(found.first != found.second)
        {
            sa.push_back(it - files.cbegin());
            beg_iter.push_back(found.first);
            end_iter.push_back(found.second);
        }
    }
    return ;
}
void reportResults(std::istream &in, std::ostream &os, const std::vector<std::vector<Sales_data>> &files)
{
    std::string s;
    while(in >> s)
    {
        std::vector<std::vector<Sales_data>::size_type> sa;
        std::vector<vec_const_iter> beg_iter;
        std::vector<vec_const_iter> end_iter;
        findBook(files, s, sa, beg_iter, end_iter);
        if(sa.empty())
        {
            os << s << "not found in any store" << std::endl;
        }
        else
        {
            for (int i = 0; i < sa.size(); ++i) {
                
                os << "store" << sa[i] << " sales: " << std::accumulate(beg_iter[i], end_iter[i],Sales_data(s)) << std::endl;
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
