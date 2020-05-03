#include "decorator.h"
#include <memory>

// 装饰器模式, 即对不同类型的对象添加相同的功能
// 将需要装饰的对象交给装饰器类, 
// 也就是说装饰器类中, 有需要装饰的对象, 在构造函数中对对象进行装饰
//
// 通过装饰器类将不同类型的对象添加相同的功能, 只需要将需要装饰的对象
// 交给指定的装饰器进行装饰即可

int main() {
  // 动态绑定
  Car* bmwCar =  new Decorator1(new Bmw("x6"));
  bmwCar->show();
  bmwCar = new Decorator2(bmwCar);
  bmwCar->show();
  cout << endl;

  Car* benzCar =  new Decorator1(new Benz("e300"));
  benzCar->show();
  cout << endl;
  return 0;
}
