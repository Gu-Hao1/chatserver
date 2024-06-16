#ifndef USER_H
#define USER_H
#include <string>

using namespace std;

//匹配User表的ORM的类
class User{
public:
    User(int id = -1, string name = "", string password = "", string state = "offline");
    void setId(int id);
    void setName(string name);
    void setPwd(string password);
    void setState(string state);

    int getId();
    string getName();
    string getPwd();
    string getState();
protected:
    int id;
    string name;
    string password;
    string state;
};
#endif