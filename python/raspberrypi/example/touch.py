# -*- coding:utf-8 -*-
""" file DFRobot_Sensor.py
  # @file touch.ino
  # @brief 检测5个电场（上、下、左、右、中）的touch情况，可以是：触摸、点击、双击
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
myGesture = DFRobot_MGC3130(d_pin=20,mclr_pin = 21,bus = 1)

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

def loop():
  '''
    @brief 获取传感器数据
  '''
  myGesture.sensor_data_recv()

  '''
    @brief 获取接触信息
    @return 接触信息:
              DOUBLE_TAP_CENTER/DOUBLE_TAP_RIGHT/DOUBLE_TAP_UP/DOUBLE_TAP_LEFT/DOUBLE_TAP_DOWN
              TAP_CENTER/TAP_RIGHT/TAP_UP/TAP_LEFT/TAP_DOWN
              TPUCH_CENTER/TOUCH_RIGHT/TOUCH_UP/TOUCH_LEFT/TOUCH_DOWN
  '''
  info = myGesture.get_touch_info()
  if(info & myGesture.DOUBLE_TAP_CENTER):
    print("Double Tap Center electrode")
  elif(info & myGesture.DOUBLE_TAP_RIGHT):
    print("Double Tap Right electrode")
  elif(info & myGesture.DOUBLE_TAP_UP):
    print("Double Tap Up electrode")
  elif(info & myGesture.DOUBLE_TAP_LEFT):
    print("Double Tap Left electrode")
  elif(info & myGesture.DOUBLE_TAP_DOWN):
    print("Double Tap Down electrode")
  elif(info & myGesture.TAP_CENTER):
    print("Tap Center electrode")
  elif(info & myGesture.TAP_RIGHT):
    print("Tap Right electrode")
  elif(info & myGesture.TAP_UP):
    print("Tap Up electrode")
  elif(info & myGesture.TAP_LEFT):
    print("Tap Left electrode")
  elif(info & myGesture.TAP_DOWN):
    print("Tap Down electrode")
  elif(info & myGesture.TPUCH_CENTER):
    print("Touch Center electrode")
  elif(info & myGesture.TOUCH_RIGHT):
    print("Touch Right electrode")
  elif(info & myGesture.TOUCH_UP):
    print("Touch Up electrode")
  elif(info & myGesture.TOUCH_LEFT):
    print("Touch Left electrode")
  elif(info & myGesture.TOUCH_DOWN):
    print("Touch Down electrode")


if __name__ == "__main__":
  setup()
  while True:
    loop()
