'''
    界面
'''

class Menu(object):
    def main_menu(self):
        print('=' * 32)
        print('1. 图片人脸识别')
        print('2. 视频人脸识别')
        print('3. 添加人脸资源')
        print('0. 退出')
        print('=' * 32)
        choice = input('请选择: ')
        return choice

    def image_recognition_menu(self):
        filename = input('请输入图片路径: ')
        return filename

    def video_recognition_menu(self):
        filename = input('请输入视频路径: ')
        return filename

    def add_image_menu(self):
        filename = input('请输入图片路径(单人正脸照): ')
        name = input('姓名: ')
        return filename, name