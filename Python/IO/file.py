"""
    有关文件的基本操作
"""

'''
# 文件的复制
filename1 = './demo.txt'
filename2 = './demo2.txt'
fp1 = open(filename1, 'r')
fp2 = open(filename2, 'w')
while True:
    line = fp1.readline()
    if len(line) > 0:
        fp2.write(line)
    else:
        break
fp1.close()
fp2.close()
print('复制完毕')
'''

# 文件的随机读取
filename = './demo.txt'
fp = open(filename, 'r')
fp.seek(0, 2)  # 0:beg 1:cur 2:end
fsize = fp.tell()
print('文件大小为:', fsize)
fp.seek(0, 0)
lines = fp.readlines()
for line in lines:
    print(line, end='')

"""
    对目录的操作
"""
'''
import os
# 展示当前目录下的文件
filelist = os.listdir()
for filename in filelist:
    print(filename)

# 添加目录
os.mkdir('./demo')
# 删除文件
os.remove('./demo')
# 修改文件名
os.rename('./demo.txt', 'tmp.txt')
'''
