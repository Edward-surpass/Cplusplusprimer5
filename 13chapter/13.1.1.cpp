#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <memory>
#include <utility>
#include <initializer_list>
#include <map>
#include <set>
#include <vector>
using namespace std;
class sales_data{
private:
    string book_no;
    int units_sold = 0;
    double revenue = 0.0;
public:
    sales_data()=default;
    sales_data(const string &bn,const int &us,const double &re):book_no(bn),units_sold(us),revenue(re){}
    sales_data(const sales_data &orig);
};
sales_data::sales_data(const sales_data &orig):book_no(orig.book_no),units_sold(orig.units_sold),revenue(orig.revenue){}
int main()
{
    return 0;
}
