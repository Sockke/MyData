#include <iostream>
#include <string>
using std::cout;
using std::endl;

// 代理模式 --- 结构型模式

class Video {
  public:
    virtual void freeVideo() = 0;
    virtual void vipVideo() = 0;
    virtual ~Video() {}
};
class Commission : public Video {
  public:
    void freeVideo() {
      cout << "观看免费电影" << endl;
    }
    void vipVideo() {
      cout << "观看VIP电影" << endl;
    }
};

class FreeProxy : public Video {
  public:
    FreeProxy() {_video = new Commission;}
    ~FreeProxy() {delete _video;}
    void freeVideo() {
      _video->freeVideo();
    }
    void vipVideo() {
      cout << "您不是会员, 无法观看" << endl;
    }
  private:
    Video* _video;
};
class VipProxy : public Video {
  public:
    VipProxy() {_video = new Commission;}
    ~VipProxy() {delete _video;}
    void freeVideo() {
      _video->freeVideo();
    }
    void vipVideo() {
      _video->vipVideo();
    }
  private:
    Video* _video;
};
