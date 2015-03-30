#include <set>
#include <iostream>
#include <string>
using namespace std;
class folder;
class message{
    friend class folder;
    friend ostream &operator<<(ostream &o, const message &me);
private:
    string conntents;
    set<folder*> folders;
    void add_to_folders(const message &me);
    void remove_from_folders();
public:
    message(const string s = ""):conntents(s),folders(set<folder*>()){}
    message(const message &);
    ~message();
    message &operator=(const message &me);
    void save(folder &fo);
    void remove(folder &fo);
    void add_folder(folder *fo);
    void rem_folder(folder *fo);
    void swap(message &lh,message &rh);
};
class folder{
    friend class message;
    friend ostream &operator<<(ostream &o,const folder &fo)
    {
        for(auto &e:fo.messages)
            o << e << " ";
        return o;
    }
private:
    set<message*> messages;
public:
    folder():messages(set<message*>()){}
    ~folder(){cout << "~folder" << endl;}
    void add_msg(message *me);
    void rem_msg(message *me);
};
void message::add_to_folders(const message &me)
{
    for(auto &e:me.folders)
    {
        e->add_msg(this);
    }
}
void message::remove_from_folders(){
    for(auto &e:folders)
        e->rem_msg(this);
}
void message::save(folder &fo)
{
    folders.insert(&fo);
    fo.add_msg(this);
}
void message::remove(folder &fo)
{
    folders.erase(&fo);
    fo.rem_msg(this);
}
message::message(const message &me):conntents(me.conntents),folders(me.folders)
{
    this->add_to_folders(me);
}
message &message::operator=(const message &me)
{
    this->remove_from_folders();
    this->conntents = me.conntents;
    this->folders = me.folders;
    this->add_to_folders(me);
    return *this;
}
void message::add_folder(folder *fo){
    folders.insert(fo);
}
void message::rem_folder(folder *fo){
    folders.erase(fo);
}
void message::swap(message &lh, message &rh)
{
    lh.remove_from_folders();
    rh.remove_from_folders();
    lh.add_to_folders(rh);
    rh.add_to_folders(lh);
    std::swap(lh.conntents,rh.conntents);
    std::swap(lh.folders,rh.folders);
}
message::~message()
{
    cout << "~messageb" << endl;
    this->remove_from_folders();
    cout << "~messagee" << endl;
}
void folder::add_msg(message *me){
    messages.insert(me);
}
void folder::rem_msg(message *me){
    cout << "rem_msgb" << endl;
    cout << me << " count:" << messages.count(me) << endl;
    for(auto e:messages)
        cout << e << " ";
    cout << endl;
    messages.erase(messages.find(me));
    cout << "rem_msge" << endl;
}
ostream &operator<<(ostream &o,const message &me)
{
    return o << "contents:" << me.conntents;
}
int main()
{
    folder g1;
    folder g2;
    message s1("hello");
    message s2("world");
    s1.save(g1);
    s1.save(g2);
    s2.save(g1);
    cout << s1 << ":::::::::" << s2 << endl;
    cout <<"==============" << endl;
    cout << g1 << ":::::::::::::::" << g2 << endl;
    return 0;
}
