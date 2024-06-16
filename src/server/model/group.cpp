#include "group.hpp"

Group::Group(int id, string name, string groupdesc)
{
    this->id=id;
    this->name =name;
    this->desc=groupdesc;
}
void Group::setId(int id){
    this->id=id;
}
void Group::setGroupName(string name)
{

    this->name =name;
}
void Group::setGroupdesc(string groupdesc)
{
    this->desc=groupdesc;
}

int Group::getId()
{
    return id;
}
string Group::getGroupName()
{
    return name;
}
string Group::getGroupdesc()
{
    return desc;
}

vector<GroupUser>&Group::getUsers()
{
    return this->users;
}