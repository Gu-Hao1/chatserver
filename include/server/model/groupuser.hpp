#ifndef GROUPUSER_H
#define GROUPUSER_H
#include"user.hpp"
#include <string>
#include <vector>
using namespace std;

//群组用户，多了一个role角色信息，从User类直接进行继承，复用User的其他信息
class GroupUser:public User
{
public:

   void setRole(string role);

   string getRole();
private:
    string role;
};
#endif