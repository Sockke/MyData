'''
    业务模块
'''
import imageModel
import cv2
import face_recognition
import numpy

class FRService(object):
    def __init__(self):
        self.imgModel = imageModel.ImageModel() 
        # 已知的人脸数据
        self.known_encodings = []  # 人脸编码
        self.known_names = []  # 人脸名称

    def prepare_dataset(self):
        '''从数据库获取人脸资料'''
        dataset = self.imgModel.fetch_image()
        # 人脸数据初始化
        for id, encoding, name in dataset:
            # 将字符串类型转换成numpy.ndarray类型
            # encoding_array = numpy.fromstring(encoding, dtype=numpy.float)
            list1 = encoding.split(',')
            list2 = []
            for i in list1:
                list2.append(float(i))
            encoding_array = numpy.array(list2)
            # 放到列表中
            self.known_encodings.append(encoding_array)
            self.known_names.append(name)

    def image_recognition(self, filename):
        '''
            图片人脸识别
        '''
        # 读取图片
        unknown_img = cv2.imread(filename)
        # 捕获人脸
        locations = face_recognition.face_locations(unknown_img)
        # 人脸编码
        unknown_encodings = face_recognition.face_encodings(unknown_img, locations)

        for (top, right, bottom, left), unknown_encoding in zip(locations, unknown_encodings):
            # 将人脸圈出来
            cv2.rectangle(unknown_img, (left, top), (right, bottom), (0, 0, 255), 2)
            # 人脸识别
            ismatches = face_recognition.compare_faces(self.known_encodings, unknown_encoding)
            name = 'unknown'
            for ismatch, known_name in zip(ismatches, self.known_names):
                if ismatch:
                    name = known_name
                    break
            # 标记人脸
            cv2.rectangle(unknown_img, (left, bottom - 35), (right, bottom), (0, 0, 255), cv2.FILLED)
            cv2.putText(unknown_img, name, (left+6, bottom-6), cv2.FONT_HERSHEY_DUPLEX, 1, (255, 255, 255), 2)

        # 展示图片
        cv2.namedWindow('image', 0)
        cv2.resizeWindow('image', 640, 480)
        cv2.imshow('image', unknown_img)
        # 阻塞窗口
        cv2.waitKey(0)
        # 销毁窗口
        cv2.destroyAllWindows()

    def video_recognition(self, filename):
        '''
            摄像头人脸识别
        '''
        # 创建视频捕获对象
        video = cv2.VideoCapture(filename)
        while video.isOpened():
            ret, img = video.read()
            if not ret:
                # 视频捕获失败
                break
            
            # Resize frame of video to 1/4 size for faster face recognition processing
            small_frame = cv2.resize(img, (0, 0), fx=0.25, fy=0.25)
            # Convert the image from BGR color (which OpenCV uses) to RGB color (which face_recognition uses)
            # rgb_small_frame = small_frame[:, :, ::-1]

            # 人脸位置
            locations = face_recognition.face_locations(small_frame)
            # 人脸编码
            unknown_encodings = face_recognition.face_encodings(small_frame, locations)
            # 找出每个位置对应的人脸名称
            face_names = []
            for unknown_encoding in unknown_encodings:
                # See if the face is a match for the known face(s)
                ismatches = face_recognition.compare_faces(self.known_encodings, unknown_encoding, 0.5)
                name = "Unknown"

                # # If a match was found in known_face_encodings, just use the first one.
                # if True in matches:
                #     first_match_index = matches.index(True)
                #     name = known_face_names[first_match_index]

                # Or instead, use the known face with the smallest distance to the new face
                
                face_distances = face_recognition.face_distance(self.known_encodings, unknown_encoding)
                best_match_index = numpy.argmin(face_distances)
                if ismatches[best_match_index]:
                    name = self.known_names[best_match_index]
                '''
                for ismatch, known_name in zip(ismatches, self.known_names):
                    if ismatch:
                        name = known_name
                        break
                '''
                face_names.append(name)

            # 将人脸标记出来
            for (top, right, bottom, left), name in zip(locations, face_names):
                # Scale back up face locations since the frame we detected in was scaled to 1/4 size
                top *= 4
                right *= 4
                bottom *= 4
                left *= 4

                # 圈出人脸
                cv2.rectangle(img, (left, top), (right, bottom), (0, 0, 255), 2)

                # Draw a label with a name below the face
                cv2.rectangle(img, (left, bottom - 35), (right, bottom), (0, 0, 255), cv2.FILLED)
                #font = cv2.FONT_HERSHEY_DUPLEX
                #cv2.putText(frame, name, (left + 6, bottom - 6), font, 1.0, (255, 255, 255), 1)
                cv2.putText(img, name, (left+6, bottom-6), cv2.FONT_HERSHEY_DUPLEX, 1, (255, 255, 255), 2)
            '''
            # 人脸识别
            for (top, right, bottom, left), unknown_encoding in zip(locations, unknown_encodings):
                # 圈出人脸
                cv2.rectangle(img, (left, top), (right, bottom), (0, 255, 0), 2)
                # 人脸匹配
                ismatches = face_recognition.compare_faces(self.known_encodings, unknown_encoding)
                name = 'unknown'
                for ismatch, known_name in zip(ismatches, self.known_names):
                    if ismatch:
                        name = known_name
                        break
                # 人脸标识
                cv2.putText(img, name, (left, top-10), cv2.FONT_HERSHEY_COMPLEX, 1, (0, 0, 255), 1)
            '''
            # 展示图片
            cv2.namedWindow('video', 0)
            cv2.resizeWindow('video', 640, 480) 
            cv2.imshow('video', img)
            
            # 阻塞窗口
            if cv2.waitKey(1) & 0xFF == ord('q'):
                # 录入键盘
                break
        # 销毁video对象, 关闭摄像头
        video.release()
        # 销毁窗口
        cv2.destroyAllWindows()
       
    def image_add(self, filename, name):
        '''添加人脸资料'''
        # img = cv2.imread(filename)
        img = face_recognition.load_image_file(filename)
        locations = face_recognition.face_locations(img)
        known_encoding = face_recognition.face_encodings(img, locations)[0]
        # 将numpy.ndarry转换成字符串类型
        # known_encoding_str = known_encoding.tostring()
        known_encoding_str = ','.join(str(i) for i in known_encoding)
        self.imgModel.add_image(known_encoding_str, name)

