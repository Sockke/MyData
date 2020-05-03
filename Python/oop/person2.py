"""
    oop编程, python封装, 继承与多态
    封装: 通过命名来表示访问权限, 前置是'__'的为私有成员, 其他的为公有成员
    继承: class Derive(Base), python支持多继承, 但不推荐使用
    多态: 鸭子类型的多态, 同Go一样, 只要你这个对象实现了这个接口, 就可以像多态那样使用这个函数

    类属性类似于C++中的静态变量, 但是有一定的差别, 类属性必须在类方法中进行修改
    因为python是动态语言, 如果通过对象进行修改, 会在该对象中生成一个同名的实例属性
    类方法类似与C++中的静态方法, 通过类方法可以访问或修改类属性

    python中还有一个静态方法, 不常用, 一般是类属性与类方法进行搭配使用
    有时候将一些普通的方法放置在类中, 考虑使用@staticmethod
"""

class Person:
    # 类属性
    __num = 0

    def __init__(self, name, age):
        self.__name = name
        self.__age = age
        self.__addNum()

    def __del__(self):
        self.__subNum()

    def __str__(self):
        return 'name:{}, age:{}'.format(self.__name, self.__age)

    # 类方法
    @classmethod
    def __addNum(cls):
        cls.__num += 1

    @classmethod
    def __subNum(cls):
        cls.__num -= 1

    @classmethod
    def showNum(cls):
        return cls.__num

    def run(self):
        print('人在跑')


class Student(Person):
    # 重写Person中的run方法
    def run(self):
        print('学生在跑')


class Teacher(Person):
    def run(self):
        print('老师在跑')


def whoRun(p):
    p.run()


'''
# 继承
s1 = Student('sock', 19)
print(s1)
s2 = Student('laoma', 20)
print(s2)
print('总共有{}个学生'.format(Student.showNum()))
del s2
print('总共有{}个学生'.format(Student.showNum()))
'''
# 多态
s = Student('sock', 19)
s.getNum()
t = Teacher('Amy', 28)
whoRun(s)
whoRun(t)