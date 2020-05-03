"""
    有关字符串的相关操作
    字符串是常量
"""
s = 'sock is a good man and he is running'
# 字符串查询
index = s.find('good')
if index != -1:
    print('index = ', index)
else:
    print('没有找到')

# 字符串分割
strs = s.split(' ')
for e in strs:
    print(e, end=' ')
print()

# 子串的数量
str_count = s.count('is')
print('str_count = ', str_count)

# 字符串的大小写转换操作
title = s.title()
str_lower = s.lower()
str_upper = s.upper()
print('title:', title)
print('lower:', str_lower)
print('upper:', str_upper)

# 字符串判断以什么内容开头或结尾
if s.startswith('sock'):
    print(s.endswith('man'))
else:
    print('没有以sock开头')

# 判断字符串的内容
if s.isalpha() == True:
    print('全是字符')
elif s.isnumeric() == True:
    print('全是数字')
elif s.isalnum() == True:
    print('只有字符或数字')
else:
    print('其他')

# 去掉字符串两边的空白字符
ss = ' sock\tis '
print(ss.strip())

# 连接字符串
strs = s.split(' ')
print(strs)
ss = ''
print(ss.join(strs))
ss = ' '
print(ss.join(strs))
