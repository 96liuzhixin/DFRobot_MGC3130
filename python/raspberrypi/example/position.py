# -*- coding:utf-8 -*-
""" file DFRobot_Sensor.py
  # @file position.ino
  # @brief 位置识别，x,y,z轴上数据
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
    @brief 关闭接近检测功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  while(myGesture.enable_approach_detection()!=0):
    print("enable approach detection err")
  print("enable approach detection success")

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
    @brief 监测是否有位置信息
    @return 返回true，代表有位置信息，false代表没有
  '''
  if(myGesture.have_position_info()==True):
    print('X: =%d '%(myGesture.get_x_position()),' Y: =%d '%(myGesture.get_y_position()),'  Z: =%d '%(myGesture.get_z_position()))

if __name__ == "__main__":
  setup()
  while True:
    loop()
