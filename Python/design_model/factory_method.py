"""
    python实现工厂方法
"""
from enum import Enum

class Car:
    def __init__(self, name):
        self.name = name

    def show(self):
        pass

class Audi(Car):
    def show(self):
        print('create a new car of Audi: {}'.format(self.name))

class Benz(Car):
    def show(self):
        print('create a new car of Benz: {}'.format(self.name))

class CarType(Enum):
    AUDI = 1
    BENZ = 2

class Factory:
    def __init__(self, car_type):
        self.car_type = car_type

    def createCar(self, name):
        pass

class AudiFactory(Factory):
    def createCar(self, name):
        return Audi(name)

class BenzFactory(Factory):
    def createCar(self, name):
        return Benz(name)


af = AudiFactory(CarType.AUDI)
bf = BenzFactory(CarType.BENZ)
audi = af.createCar('A6')
benz = bf.createCar('G')
audi.show()
benz.show()