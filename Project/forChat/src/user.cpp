#include "user.hpp"

User::User(int id, const std::string& name, const std::string& passwd, const std::string& state)
    : _id(id)
    , _name(name)
    , _passwd(passwd)
    , _state(state)
{}

void User::setId(int id) {_id = id;}
void User::setName(const std::string &name) {_name = name;}
void User::setPasswd(const std::string &passwd) {_passwd = passwd;}
void User::setState(const std::string &state) {_state = state;}

int User::getId() const {return _id;}
std::string User::getName() const {return _name;}
std::string User::getPasswd() const {return _passwd;}
std::string User::getState() const {return _state;}