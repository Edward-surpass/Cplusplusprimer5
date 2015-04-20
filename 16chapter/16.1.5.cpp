#include <vector>
#include "Blob16.1.5.h"
extern template class Blob<std::string>;
int main()
{
    std::vector<std::string> vs({"sss","bbb"});
    Blob<std::string> bs(vs.begin(),vs.end());
    std::cout << bs << std::endl;
}
