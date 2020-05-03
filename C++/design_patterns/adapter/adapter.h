#include <iostream>
#include <string>
using std::cout;
using std::endl;

// 适配器模式 --- 结构型设计模式

class VGA {
  public:
    virtual void play() = 0;
};
class TV01 : public VGA {
  public:
    void play() {
      cout << "通过VGA接口来播放" << endl;
    }
};

class HDMI {
  public:
    virtual void play() = 0;
};
class TV02 : public HDMI {
  public:
    void play() {
      cout << "通过HDMI接口来播放" << endl;
    }
};

class Computer {
  public:
    // 只支持VGA接口
    Computer(VGA* interface) : _interface(interface) {}
    void play() {
      _interface->play();
    }
  private:
    VGA* _interface;
};

// 接口转换, 将VGA转换为HDMI
class VGA2HDMIAdapter : public VGA {
  public:
    VGA2HDMIAdapter(HDMI* interface) : _interface(interface) {}
    void play() {
      _interface->play();
    }
  private:
    HDMI* _interface;
};
