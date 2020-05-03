"""
    python实现抽象工厂
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


class Light:
    def __init__(self, car_type):
        self.car_type = car_type

    def show(self):
        print('create a new light of {}'.format(self.car_type))


class Factory:
    def __init__(self, car_type):
        self.car_type = car_type

    def createCar(self):
        pass

    def createLight(self):
        pass


class AudiFactory(Factory):
    def createCar(self, name):
        return Audi(name)

    def createLight(self):
        return Light(self.car_type)


class BenzFactory(Factory):
    def createCar(self, name):
        return Benz(name)

    def createLight(self):
        return Light(self.car_type)


af = AudiFactory(CarType.AUDI)
bf = BenzFactory(CarType.BENZ)
audi_car = af.createCar('A6')
audi_light = af.createLight()
audi_car.show()
audi_light.show()
benz_car = bf.createCar('G')
benz_light = bf.createLight()
benz_car.show()
benz_light.show()
