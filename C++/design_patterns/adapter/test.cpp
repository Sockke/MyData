#include "adapter.h"

// 适配器模式, 即通过适配器来使得不兼容的部分能一起工作
//
// 将需要适配的对象交给适配器类,
// 即适配器类中有需要适配的对象, 通过适配器类将不兼容的对象转换成兼容的对象
//
// 这样如果第三方接口与项目设计的接口不兼容,
// 可以添加一个适配器, 适配器继承兼容的接口, 然后添加不兼容的对象, 
// 通过转换使得不兼容的部分能够一起工作

int main() {
  Computer cmp(new TV01);
  cmp.play();
  Computer cmp2(new VGA2HDMIAdapter(new TV02));
  cmp2.play();
  return 0;
}
