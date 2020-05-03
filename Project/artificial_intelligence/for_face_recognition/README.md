## 人脸识别

#### OpenCV

```python
'''
OpenCV是一个开源的跨平台的视觉库, 底层用C++编写, 支持Python, Java等
'''
```

* OpenCV的安装

```python
# pip3 install opencv-python
```

* 图片的展示

```python
imread(filename, flags=None)  # 读取图片
'''
filename: 图片路径
flags: 打开方式
'''
imgshow(winname, img)  # 展示图片
'''
winname: 窗口名称
img: 图片对象
'''
waitKey(delay=None)  # 阻塞窗口
'''
delay: 阻塞时间, 单位毫秒, 0表示一直等待
返回值: 超过阻塞时间返回-1, 当有键盘录入时返回非负数
'''
destroyAllWindows()  # 销毁窗口
```

```python
import cv2
# 读取图片, 
img = cv2.imread('/images/rm.jpg')
# 展示图片
cv2.imgshow('running man', img)
# 阻塞窗口
cv2.waitKey(0)
# 销毁窗口
cv2.destroyAllWindows()
```

* 视频的捕获

```python
VideoCapture(num)  # 创建视频捕获对象
'''
num: 摄像头编号, 0表示使用默认内置摄像头
'''
read()  # 捕获视频帧图片
'''
返回值: ret(是否捕获成功), img(图片对象)
'''
release()  # 销毁视频捕获对象, 关闭摄像头
```

```python
import cv2
# 创建视频捕获对象
video_obj = cv2.VideoCapture(0)
# 循环捕获视频帧图片
while True:
    ret, img = video_obj.read();
    if not ret:
        # 视频捕获失败
        break
	# 展示图片
    cv2.imgshow('myself', img)
	# 阻塞窗口
    if cv2.waitKey(1) != -1:
        # 销毁对象, 关闭摄像头
        video_obj.release()
        # 销毁窗口
        cv2.destroyAllWindows()
        break
```

* 绘制方框和添加文本

```python
# OpenCV中, 图形坐标是相对左上角来衡量的
0--------------
|
|
|
|
# 自左上角0处, 向右, 向下递增

rectangle(img, pt1, pt2, color, thickness=None)
'''
img: 图片对象
pt1: 矩形坐上角坐标
pt2: 矩形右下角坐标
color: BGR矩形颜色
thickness: 矩形线条厚度
'''
putText(img, text, org, fontFace, fontScale, color, thickness=None)
'''
img: 图片对象
text: 文本内容
org: 文本左下角的坐标
fontFace: 字体类型
fontScale: 字体缩放倍数
color: 字体颜色
thickness: 字体厚度
'''
```

```python
import cv2
# 读取图片
img = cv2.imread('/images/rm.jpg')

# 绘制方框
cv2.rectangle(img, (200, 200), (400, 500), (0, 0, 255), 1)
# 添加文本
cv2.putText(img, 'gary', (200, 200-10), cv2.FONT_HERSHEY_COMPLEX, 1, (0, 0, 255), 1)

# 展示图片
cv2.imgshow('running man', img)
# 阻塞窗口
cv2.waitKey(0)
# 销毁窗口
cv2.destroyAllWindows()
```

#### face_recognition

* face_recognition的安装

```python
'''
人脸识别与装饰库, 支持python3.3+或python2.7, 对windos支持的不是很友好
需要使用C++15编译环境
安装CMake并更新

pip3 install face_recognition
'''
```

* 获取人脸的位置

```python
face_locations(img)
'''
img: 图片对象
返回值: 人脸位置的列表, [(top,right,bottom,left), ...]
'''
```

![](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20200501165154905.png)

```python
import cv2
import face_recognition
# 读取图片
img = cv2.imread('/images/rm.jpg')

# 捕获人脸位置
f_locations = face_recognition.face_locations(img)
for top,right,buttom,left in f_locations:
    # 将人脸圈起来
    cv2.rectangle(img, (left, top), (right, buttom), (0, 0, 255), 1)

# 展示图片
cv2.imgshow('running man', img)
# 阻塞窗口
cv2.waitKey(0)
# 销毁窗口
cv2.destroyAllWindows()
```

* 人脸识别

```python
face_encodings(face_img, know_face_locations=None, num_jitters=1)  # 人脸编码
'''
face_img: 带有人脸的图片对象
know_face_locations: 人脸位置, 传入的话内部不用再获取人脸的位置
num_jstters: 重新采样的次数, 值越高越精确, 也越慢
返回值: 人脸向量列表, 每个元素是每张人脸的128维向量
'''
compare_faces(know_face_encodings, face_encoding_to_check, tolerance=0.6)
'''
know_face_encodings: 已知的人脸编码向量列表
face_encoding_to_check: 需要识别的人脸编码向量
tolerance: 匹配精度, 越小越严格
返回值: 人脸识别是否成功(True/False)的列表
'''
```

```python
import cv2
import face_recognition
# 读取图片
img = cv2.imread('/images/gary.jpg')
unknown_img = cv2.imread('/images/rm.jpg')

# 捕获人脸
f_locations = face_recognition.face_locations(unknown_img)

# 人脸编码
gary_face_encoding = face_recognition.face_encodings(img)[0]  # 单人图片
# 构建人脸库
known_face_encodings = [gary_face_encoding,]
known_face_names = ['gary',]
unknown_face_encodings = face_recognition.face_encodings(unknown_img, f_locations)

for (top,right,bottom,left), unknown_face_encoding in zip(f_locations, unknown_face_encodings):
    # 将人脸圈起来
    cv2.rectangle(img, (left, top), (right, bottom), (0, 0, 255), 1)
    # 人脸识别
    ismatches = face_recognition.compare_faces(known_face_encodings, unknown_face_encoding)
    name = 'unknown'
    for ismatch, known_face_name in zip(ismatches, known_face_names):
        if ismatch:
            # 人脸匹配成功
            name = known_face_name
            break
	# 标记人脸
	cv2.putText(img, name, (left, top-10), cv2.FONT_HERSHEY_COMPLEX, 1, (0, 0, 255), 1)

# 展示图片
cv2.imgshow('running man', img)
# 阻塞窗口
cv2.waitKey(0)
# 销毁窗口
cv2.destroyAllWindows()
```

