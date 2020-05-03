"""
    lambda表达式
    lambda args : expression
"""

my_sum = lambda x, y : x + y
print(my_sum(5, 10))

arr = []
arr.append({'name': 'sock', 'age': 21})
arr.append({'name': 'laoma', 'age': 22})
arr.append({'name': 'liuchen', 'age': 21})
arr.append({'name': 'xiaoqian', 'age': 20})
arr.sort(key=lambda e: e['age'])  # 按e['age']进行排序
for e in arr:
    print(e['name'], e['age'])
