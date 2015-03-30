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
class tree_node{
    friend class binstr_tree;
private:
    string value;
    int count;
    tree_node *left;
    tree_node *right;
public:
    tree_node(const string &s):value(s),count(1),left(nullptr),right(nullptr){}
    tree_node(const tree_node &tn):value(tn.value),count(tn.count),left(tn.left),right(tn.right){}

};
class binstr_tree{
private:
    tree_node *root;
public:
    binstr_tree(const string &s):root(new tree_node(s)){}
    binstr_tree(const binstr_tree &bt):root(new tree_node(*bt.root)){}
    binstr_tree &operator=(const binstr_tree &bt){
        tree_node *p = new tree_node(*bt.root);
        delete root;
        root = p;
        return *this;
    }
    void my_delete(tree_node *p)
    {
        if(p->left)
            my_delete(p->left);
        if(p->right)
            my_delete(p->right);
        if(p)
            delete p;
    }
    ~binstr_tree()
    {
        my_delete(root);
    }
};
int main()
{
}
