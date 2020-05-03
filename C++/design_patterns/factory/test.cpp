// 简单工厂: 即一个工厂负责生产所有的产品
// 将所有对象的创建封装在一个类的接口中, 用户不需要关心创建的过程,
// 只需要知道自己想要的东西即可
// 但是简单工程不符合软件设计的"开-闭原则", 其对修改是开放的, 
// 对任意产品的添加, 需要在工厂类中进行修改, 因此简单工厂模式在23设计模式中
//
// 工厂方法: 即指定工厂生产指定产品
// 为每一种对象的创建封装在不同的类的接口中, 用户仍然不需要关心创建的过程,
// 只需要知道自己想要的东西即可
// 工厂方法符合软件设计的"开-闭原则", 对扩展开放, 对修改关闭
// 对任意产品的添加, 只需要为其添加指定的工厂类即可, 不需要修改其他的工厂
//
// 抽象工厂: 即指定工厂生产一组相关联的产品
// 为一组相关联的对象的创建封装在不同的类的接口中, 一个工厂生产一组产品只需要在工厂中
// 提供相应的工厂方法即可, 不需要再创建新的工厂
// 抽象工厂是工厂方法的扩展与抽象, 依然符合"开-闭原则"
// 对任意产品的添加, 只需要在指定的关联的工厂类中为其添加工厂方法即可, 不需要修改其他工厂
#include "abstract_factory.h"
#include <memory>

int main() {
  std::unique_ptr<AbstractFactory> bmwFac(new BmwFactory);
  std::unique_ptr<AbstractFactory> benzFac(new BenzFactory);
  std::unique_ptr<Car> bmwCar(bmwFac->createCar("x6"));
  std::unique_ptr<Car> benzCar(benzFac->createCar("e300"));
  std::unique_ptr<Light> bmwLight(bmwFac->createLight("x6-a"));
  std::unique_ptr<Light> benzLight(benzFac->createLight("e300-a"));
  bmwCar->show();
  bmwLight->show();
  benzCar->show();
  benzLight->show();
  return 0;
}
#if 0
#include "simple_factory.h"
#include <memory>

int main() {
  std::unique_ptr<Factory> fac(new Factory);
  std::unique_ptr<Car> bmwCar(fac->createCar(BMW));
  std::unique_ptr<Car> benzCar(fac->createCar(BENZ));
  bmwCar->show();
  benzCar->show();
  return 0;
}

#include "factory_method.h"
#include <memory>

int main() {
  std::unique_ptr<Factory> bmwFac(new BMWFactory);
  std::unique_ptr<Factory> benzFac(new BENZFactory);
  std::unique_ptr<Car> bmwCar(bmwFac->createCar("x6"));
  std::unique_ptr<Car> benzCar(benzFac->createCar("e300"));
  bmwCar->show();
  benzCar->show();
  return 0;
}
#endif
