g_data = 10


def show():
    """
        在python中, 如果在函数中试图修改全局变量,
        需要在函数中通过global声明一下
        否则会产生未定义行为
    """
    global g_data
    print('data = ', g_data)
    g_data += 10


def division(a, b):
    """
        函数的多值返回, 返回的多值会打包成元组
        接收方通过多值来解包接收
        多值返回的方式有多种, 还可以通过列表, 字典
    """
    if b == 0:
        return 0, True
    else:
        return a / b, False


def default_args(a, b, c=10, d=20):
    """
        更加灵活的默认参数
        在函数传参的时候, 可以指定参数变量进行赋值
    """
    print('a = ', a)
    print('b = ', b)
    print('c = ', c)
    print('d = ', d)


def multi_args(a, b, *args, **kvargs):
    """
        不定参数, *args接收单值并打包成元组
        kvargs接收键值对并打包成字典
    """
    print('a = ', a)
    print('b = ', b)
    print('args = ', args)
    print('kvargs = ', kvargs)


# 全局变量
show()
print('data = ', g_data)

# 多值返回
a = 10
b = 0
result, err = division(a, b)
if err:
    print('除数为0')
else:
    print('result = ', result)

# 默认参数
default_args(-10, -20, d=100)

# 不定参数
v = [11, 22, 33]
m = {'name': 'sock', 'age': 19}
multi_args(a, b, v, m)
multi_args(a, b, *v, **m)  # 解包
