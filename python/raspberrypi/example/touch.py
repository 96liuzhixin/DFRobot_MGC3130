# -*- coding:utf-8 -*-
""" file DFRobot_Sensor.py
  # @file touch.ino
  # @brief 检测5个电场（上、下、左、右、中）的touch情况，可以是：触摸、点击、双击
  # @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  # @licence The MIT License (MIT)
  # @author [yangfeng]<feng.yang@dfrobot.com>
  # @version V1.0
  # @date 2021-09-18
  # @url  https://github.com/DFRobot/DFRobot_Gesture
"""
import sys
sys.path.append("../") # set system path to top
import time
from DFRobot_Gesture import *
import RPi.GPIO as GPIO

# IO编号采用BCM格式
myGesture = DFRobot_Gesture(ts_pin=20,reset_pin = 21,bus = 1)

def setup():
  '''
    @brief 初始化函数
    @return 返回0表示初始化成功，返回其他值表示初始化失败
  '''
  while(myGesture.begin()!= True):
    print("begin err")
  print("begin success")

  '''
    @brief 开启接触检测功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  while(myGesture.enable_touch_detection()!=0):
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
    @brief 获取接触信息
    @return 接触信息:
              DOUBLE_TAP_CENTER/DOUBLE_TAP_EAST/DOUBLE_TAP_NORTH/DOUBLE_TAP_WEST/DOUBLE_TAP_SOUTH
              TAP_CENTER/TAP_EAST/TAP_NORTH/TAP_WEST/TAP_SOUTH
              TPUCH_CENTER/TOUCH_EAST/TOUCH_NORTH/TOUCH_WEST/TOUCH_SOUTH
  '''
  info = myGesture.get_touch_info()
  if(info & myGesture.DOUBLE_TAP_CENTER):
    print("Double Tap Center electrode")
  elif(info & myGesture.DOUBLE_TAP_EAST):
    print("Double Tap East electrode")
  elif(info & myGesture.DOUBLE_TAP_NORTH):
    print("Double Tap North electrode")
  elif(info & myGesture.DOUBLE_TAP_WEST):
    print("Double Tap West electrode")
  elif(info & myGesture.DOUBLE_TAP_SOUTH):
    print("Double Tap South electrode")
  elif(info & myGesture.TAP_CENTER):
    print("Tap Center electrode")
  elif(info & myGesture.TAP_EAST):
    print("Tap East electrode")
  elif(info & myGesture.TAP_NORTH):
    print("Tap North electrode")
  elif(info & myGesture.TAP_WEST):
    print("Tap West electrode")
  elif(info & myGesture.TAP_SOUTH):
    print("Tap South electrode")
  elif(info & myGesture.TPUCH_CENTER):
    print("Touch Center electrode")
  elif(info & myGesture.TOUCH_EAST):
    print("Touch East electrode")
  elif(info & myGesture.TOUCH_NORTH):
    print("Touch North electrode")
  elif(info & myGesture.TOUCH_WEST):
    print("Touch West electrode")
  elif(info & myGesture.TOUCH_SOUTH):
    print("Touch South electrode")


if __name__ == "__main__":
  setup()
  while True:
    loop()
