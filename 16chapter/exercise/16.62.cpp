/*********************************************************************************
*     File Name           :     16.62.cpp
*     Created By          :     edward
*     Creation Date       :     [2015-04-26 19:38]
*     Last Modified       :     [2015-04-26 20:20]
*     Description         :      
**********************************************************************************/
#include <unordered_set>
#include <string>
#include <iostream>
#include <sstream>
#include <hash_map>
#include "Sales_data.h"
size_t std::hash<Sales_data>::operator()(const Sales_data &sd)const{
    return std::hash<string>()(sd.isbn()) ^ std::hash<unsigned>()(sd.units_sold) ^ std::hash<double>()(sd.revenue);
}
int main(){
    std::unordered_multiset<Sales_data> SDset; 
    SDset.insert(Sales_data());
    SDset.insert(Sales_data("ss"));
    SDset.insert(Sales_data("ss",3,2.5));
    for(auto p = SDset.begin();p != SDset.end();++p)
        std::cout << *p << " ";
    std::cout << std::endl;
    return 0;
}
