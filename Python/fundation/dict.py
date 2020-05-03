"""
    字典: 类似于C++中的unordered_map
    元素是键值对, key-value形式, 与C++不同的是, 他的键值对的类型可以不同
    这说明字典底层数据对象中不仅存储了数据, 还存储了数据的类型
"""

# 遍历字典
def showDict(map):
    for key, val in map.items():
        print('%s = %s'%(key, val))


map = {}

# 增
map['name'] = 'sock'
map['age'] = 19
map['favourite'] = 'football'
print(map)

# 删
del(map['favourite'])
print(map)

# 改
if map.get('age'):
    map['age'] = 20
print(map)

# 查
if map.get('age'):
    print('age = ', map['age'])
else:
    print('age不存在')

print(map.keys())  # 所有key值
print(map.values())  # 所有value值
print(map.items())  # 键值对为元组, 返回列表

showDict(map)
