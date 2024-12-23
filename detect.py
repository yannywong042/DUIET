import cv2
import serial
import time
import numpy as np
import json  # Import json library for reading camera calibration data from a JSON file
import argparse  # Import argparse for command line argument parsing

# 设置串口通信
ser = serial.Serial('COM3', 115200)  # 修改为你Arduino的串口
time.sleep(2)  # 等待Arduino初始化

# 加载ArUco字典和检测参数
aruco_dict = cv2.aruco.Dictionary_get(cv2.aruco.DICT_6X6_250)
parameters = cv2.aruco.DetectorParameters_create()

# 启动摄像头
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # 检测ArUco标记
    corners, ids, _ = cv2.aruco.detectMarkers(frame, aruco_dict, parameters=parameters)

    # 如果找到了标记
    if ids is not None:
        for i in range(len(ids)):
            # 如果标记ID为1，发送'a'字符
            if ids[i] == 1:
                ser.write(b'a')  # 向Arduino发送字符 'a'
                print("Detected marker 1, sending 'a' to Arduino")
            # 如果标记ID为2，发送'b'字符
            elif ids[i] == 2:
                ser.write(b'b')  # 向Arduino发送字符 'b'
                print("Detected marker 2, sending 'b' to Arduino")

    # 显示实时画面
    cv2.aruco.drawDetectedMarkers(frame, corners, ids)
    cv2.imshow("Frame", frame)

    # 按下'q'退出
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
