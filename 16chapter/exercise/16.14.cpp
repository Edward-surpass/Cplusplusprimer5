#include <iostream>
template<typename T> class screen;
template<typename T>
std::ostream &operator<<(std::ostream &out,const screen<T> &);
template<typename T>
std::istream &operator>>(std::istream &in,screen<T> &);
template<typename T>
class screen{
    friend std::ostream &operator<<<T>(std::ostream &,const screen &);
    friend std::istream &operator>><T>(std::istream &,screen &);
    public:
        screen();
        screen(const T &,const T &);
    private:
        T height;
        T width;
};
template<typename T>
screen<T>::screen():height(0),width(0){}
template<typename T>
screen<T>::screen(const T &lhs,const T &rhs):height(lhs),width(rhs){}
template<typename T>
std::ostream &operator<<(std::ostream &out,const screen<T> &rhs){
    return out << "height:" << rhs.height << "widthi:" << rhs.width;
}
template<typename T>
std::istream &operator>>(std::istream &in,screen<T> &rhs){
    return in >> rhs.height >> rhs.width;
}
int main(){
    screen<int> sc;
    std::cin >> sc;
    std::cout << sc << std::endl;
}
