"""
    元组, 不能改变的列表
    除了修改操作, 其他的操作与列表类似
    由于python是动态类型的语言, 没有所有的常量, 仅仅是在命名上来区分,
    如果必须要定义一个不能修改的值, 那么可以考虑使用元组
"""

# 遍历元组
def show_tuple(const_v):
    for e in const_v:
        print(e, end=' ')
    print()


const_v = (9, 5, 2, 7)

# 查
if 5 in const_v:
    print('找到了')
else:
    print('没找到')

print(const_v.count(5))  # 查看5有多少个

show_tuple(const_v)

del const_v  # 删除这个元组

# 用tuple定义一个常量
const_int = (5,)  # r如果tuple中只有一个元素, 需要加','
