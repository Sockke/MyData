#include <iostream>
#include <string>
using std::cout;
using std::endl;

#include "login.pb.h"
using namespace login_proto;

int main() {
  // 序列化
  FriendsResponse req;
  ResultInfo* info = req.mutable_info();
  info->set_errcode(0);
  info->set_errmsg("");

  User* user1 = req.add_friend_list();
  user1->set_name("Gehry");
  user1->set_age(18);
  user1->set_gender(User::MALE);

  User* user2 = req.add_friend_list();
  user2->set_name("liuchen");
  user2->set_age(22);
  user2->set_gender(User::FEMALE);

  std::string send_str;
  if (req.SerializeToString(&send_str)) {
    cout << send_str << endl;
  }

  // 反序列化
  FriendsResponse resp; 
  resp.ParseFromString(send_str);
  if (!resp.info().errcode()) {
    for (int i = 0; i < resp.friend_list_size(); ++i) {
      User user = resp.friend_list(i);
      cout << user.name() << "-" << user.age() << "-" << user.gender() << endl;
    }
  } else {
    cout << "errmsg: " << resp.info().errmsg() << endl;
  }


  return 0;
}

