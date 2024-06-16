#ifndef GROUP_H
#define GROUP_H
#include <string>
#include <vector>
#include"groupuser.hpp"
using namespace std;

//匹配allgroup表的ORM的类
class Group{
public:
    Group(int id = -1, string name = "", string groupdesc="");
    void setId(int id);
    void setGroupName(string name);
    void setGroupdesc(string password);

    int getId();
    string getGroupName();
    string getGroupdesc();

    vector<GroupUser>&getUsers();
private:
    int id;
    string name;
    string desc;
    //存放的是该用户群聊中的所有的用户，避免多次查询
    vector<GroupUser> users;
};
#endif