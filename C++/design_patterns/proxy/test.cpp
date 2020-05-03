#include "proxy.h"
#include <memory>

// 代理模式: 通过代理来控制用户的一些操作权限
//
// 将委托类以组合的方式交给代理类来管理, 
// 也就是说代理类中有一个委托类对象, 进行代理
//
// 将用户的一些操作交给代理类进行管理, 而不是直接交给委托类,
// 代理类通过管理用户的操作权限, 来指定委托类的操作
// 比如说视频网站的访问, 用户的访问不直接交给视频委托, 而是交给视频代理
// 视频代理根据用户的等级来判定用户的操作权限是否合理
//
// 这样可以很好的控制对象的操作权限

void watchMovie(std::unique_ptr<Video>& user) {
  user->freeVideo();
  user->vipVideo();
}

int main() {
  std::unique_ptr<Video> user1(new FreeProxy);
  std::unique_ptr<Video> user2(new VipProxy);
  watchMovie(user1);
  cout << "--------------" << endl;
  watchMovie(user2);
  return 0;
}
