#ifndef USER_H
#define USER_H

/*
user类
*/

#include <iostream>
#include <string>

class User {
public:
    User(int id=-1, const std::string& name="", const std::string& passwd="", const std::string& state="offline");

    void setId(int id);
    void setName(const std::string& name);
    void setPasswd(const std::string& passwd);
    void setState(const std::string& state);

    int getId() const;
    std::string getName() const;
    std::string getPasswd() const;
    std::string getState() const;
private:
    int _id;
    std::string _name;
    std::string _passwd;
    std::string _state;
};

#endif