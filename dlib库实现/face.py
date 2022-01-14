# 1.导入库
import cv2
import dlib

# 2.主函数
def main():
    # 3.打开摄像头
    capture = cv2.VideoCapture(0)

    # 4.基于dlib库获取人脸检测器
    detecture = dlib.get_frontal_face_detector()

    # 5.基于dlib库实时跟踪
    tractor = dlib.correlation_tracker()

    # 6.跟踪状态
    tracking_state = False

    # 7.循环读取每一帧
    while True:
        ret, frame = capture.read()

        # 8.如果没有跟踪,启动跟踪器
        if tracking_state is False:
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            dets = detecture(gray, 1)
            # print(dets[0])
            if len(dets) > 0:
                tractor.start_track(frame, dets[0])
                tracking_state = True

        # 9.正在跟踪,实时获取人脸位置,显示
        if tracking_state is True:
            tractor.update(frame)  # 更新画面
            position = tractor.get_position()  # 获取人脸坐标
            cv2.rectangle(frame, (int(position.left()), int(position.top())),
                          (int(position.right()), int(position.bottom())), (0, 255, 0), 3)

        # 显示
        cv2.imshow('face tracking', frame)

        # 退出
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            break

    capture.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
