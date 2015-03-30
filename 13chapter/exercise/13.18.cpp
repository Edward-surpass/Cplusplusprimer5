#include <iostream>
#include <string>
using namespace std;
class employee{
private:
    string name;
    int card;
    static int cnt;
public:
    employee():name(" "),card(++cnt){}
    employee(const string &s):name(s),card(++cnt){}
    employee(const employee &em):name(em.name),card(++cnt){}
    employee &operator=(const employee &em){
        name = em.name;
        card = ++cnt;
        return *this;
    }
};
int employee::cnt = 0;
int main()
{

    return 0;
}
