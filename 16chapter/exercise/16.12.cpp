#include "blob_ptr.h"
int main()
{
    Blob<int> bi({2,3,4,5,6,6});
    blob_ptr<int> p(bi,3);
    std::cout << *p << std::endl;
    return 0;
}
