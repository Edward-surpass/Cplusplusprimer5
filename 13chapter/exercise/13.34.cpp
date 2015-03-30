#include <set>
#include <iostream>
#include <string>
using namespace std;
class folder;
class message{
    friend class folder;
private:
    string conntents;
    set<folder*> folders;
    void add_to_folders(const message&me);
    void remove_from_folders();
public:
    message(const string s = ""):conntents(s),folders(set<folder*>()){}
    message(const message &);
    ~message();
    message &operator=(const message &me);
    void save(folder &fo);
    void remove(folder &fo);
    void swap(message &lh,message &rh);
};
class folder{
private:
    set<message*> messages;
public:
    folder():messages(set<message*>()){}
    void add_msg(message *me);
    void rem_msg(message *me);
};
void message::add_to_folders(const message &me)
{
    for(folder  *const &e:me.folders)
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
    this->remove_from_folders();
    
}
void folder::add_msg(message *me){
    messages.insert(me);
}
void folder::rem_msg(message *me){
    messages.erase(me);
}
int main()
{
    return 0;
}
