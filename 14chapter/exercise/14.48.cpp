#include<iostream>
#include<deque>
#include<stack>
using namespace std;
using T = int;
class tree
{
private:
    struct Node
    {
        T data;
        Node *left;
        Node *right;
        Node(const T t):data(t),left(nullptr),right(nullptr){}
    };
    Node *head;
public:
    tree():head(nullptr){}
    tree(const Node &nd)
    {
       head = new Node(nd);
    }
    explicit operator bool()const
    {
        if(head)
            return true;
        else
            return false;
    }
};
int main()
{
    tree tr;
    cout << static_cast<bool>(tr) << endl;
    return 0;
}
