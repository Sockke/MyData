"""
    列表: 类似于C++中的动态数组
    与普通的动态数组不同的是, 列表中可以存放不同类型的数据
    这说明列表底层的数据对象不仅存储了数据, 而且还有数据类型
"""

# 遍历列表
def show_list(v):
    for e in v:
        print(e, end=' ')
    print()


def show_list2(v):
    """
        enumerate将数据元素与索引组合,
        用范围for时可以遍历索引 + 元素
        这个内置函数一般用于str, list, tuple
    """
    for i, e in enumerate(v):
        print(i, ':', e)



v = [9, 5, 2, 7]
# 增
v.append(100)  # push_back
v.insert(1, 100)  # insert
v.extend([-1, -2])  # 两个列表相连
print(v)

# 删
v.pop()  # pop_back
print(v)
del(v[1])  # erase
v.remove(100)
print(v)
# v.clear() 清除列表

# 改
v[0] = 100
print(v)

# 查
if 9 in v:
    print('找到了')
else:
    print('没找到')

# 排序与逆置
# v.sort()  # 从小到大
v.sort(reverse=True)  # 从大到小
print(v)
v.reverse()  # 逆置
print(v)

show_list(v)

