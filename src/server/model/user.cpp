#include "user.hpp"

User::User(int id, string name, string password, string state)
{
    this->id = id;
    this->name = name;
    this->password = password;
    this->state = state;
}
void User::setId(int id)
{
    this->id = id;
}
void User::setName(string name)
{
    this->name = name;
}
void User::setPwd(string password)
{
    this->password = password;
}
void User::setState(string state)
{
    this->state = state;
}

int User::getId()
{
    return id;
}
string User::getName()
{
    return name;
}
string User::getPwd()
{
    return password;
}
string User::getState()
{
    return state;
}