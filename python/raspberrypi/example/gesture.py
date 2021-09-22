# -*- coding:utf-8 -*-
""" file DFRobot_Sensor.py
  # @file gesture.ino
  # @brief 手势识别，可以是up-->down 、down-->up 、 left-->right 、right-->left、Circle clockwise、Circle counterclockwise.
  # @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  # @licence The MIT License (MIT)
  # @author [yangfeng]<feng.yang@dfrobot.com>
  # @version V1.0
  # @date 2021-09-18
  # @url  https://github.com/DFRobot/DFRobot_MGC3130
"""
import sys
sys.path.append("../") # set system path to top
import time
from DFRobot_MGC3130 import *
import RPi.GPIO as GPIO

# IO编号采用BCM格式
myGesture = DFRobot_MGC3130(ts_pin=20,reset_pin = 21,bus = 1)

def setup():
  '''
    @brief 初始化函数
    @return 返回0表示初始化成功，返回其他值表示初始化失败
  '''
  while(myGesture.begin()!= True):
    print("begin err")
  print("begin success")

  '''
    @brief 关闭手势识别功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  while(myGesture.enable_gestures()!=0):
    print("enable gestures err")
  print("enable gestures success")

  '''
    @brief 设置传感器的输出数据格式
    @return 返回-1代表设置失败，0代表设置成功
  '''
  while(myGesture.enable_data_output()!=0):
    print("enable data output err")
  print("enable data output success")

  '''
    @brief 锁定传感器的输出数据格式
    @return 返回-1代表设置失败，0代表设置成功
  '''
  while(myGesture.lock_data_output()!=0):
    print("lock data output err")
  print("lock data output success")
  

def loop():

  '''
    @brief 获取传感器数据
  '''
  myGesture.sensor_data_recv()

  '''
    @brief 获取手势信息
    @return 手势信息: FILCK_R/FILCK_L/FILCK_U/FILCK_D/CIRCLE_CLOCKWISE/CIRCLE_COUNTERCLOCKWISE
  '''
  info = myGesture.get_gesture_info()
  if(info == myGesture.FILCK_R):
    print("Flick Left to Right")
  elif(info == myGesture.FILCK_L):
    print("Flick Right to Left")
  elif(info == myGesture.FILCK_U):
    print("Flick Down to Up")
  elif(info == myGesture.FILCK_D):
    print("Flick Up to Down")
  elif(info == myGesture.CIRCLE_CLOCKWISE):
    print("Circle clockwise")
  elif(info == myGesture.CIRCLE_COUNTERCLOCKWISE):
    print("Circle counterclockwise")

if __name__ == "__main__":
  setup()
  while True:
    loop()
