import service
import menu

service_obj = service.FRService()
menu_obj = menu.Menu()
while True:
    choice = menu_obj.main_menu()
    if choice == '1':
        try:
            service_obj.prepare_dataset()
            filename = menu_obj.image_recognition_menu()
            service_obj.image_recognition(filename)
        except TypeError as e:
            print('找不到该图片')
    elif choice == '2':
        try:
            service_obj.prepare_dataset()
            filename = menu_obj.video_recognition_menu()
            service_obj.video_recognition(filename)
        except Exception as e:
            print('...')
    elif choice == '3':
        try:
            filename, name = menu_obj.add_image_menu()
            service_obj.image_add(filename, name)
        except FileNotFoundError as e:
            print('没有找到该图片')
    elif choice == '0':
        break
    else:
        continue
