# -*- coding:utf-8 -*-
""" file DFRobot_MGC3130.py
  # DFRobot_MGC3130 类的基础结构，基础方法的实现
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @licence     The MIT License (MIT)
  @author     [yangfeng](feng.yang@dfrobot.com)
  @version  V1.0
  @date  2021-09-18
  @get from https://www.dfrobot.com
  @url https://github.com/DFRobot/DFRobot_MGC3130
"""
import sys
import smbus
import logging
import numpy as np
from ctypes import *
import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

logger = logging.getLogger()
logger.setLevel(logging.INFO)  #显示所有的打印信息
#logger.setLevel(logging.FATAL)#如果不想显示过多打印，只打印错误，请使用这个选项
ph = logging.StreamHandler()
formatter = logging.Formatter("%(asctime)s - [%(filename)s %(funcName)s]:%(lineno)d - %(levelname)s: %(message)s")
ph.setFormatter(formatter) 
logger.addHandler(ph)

DFRobot_MGC3130_IIC_ADDR = 0x42

class DFRobot_MGC3130(object):
  def __init__(self,ts_pin,reset_pin,bus = 1):
    self.now_touch                    = 0
    self.last_touch                   = 0
    self.gesture_info                 = 0
    self.touch_info                   = 0
    self.air_wheel_info               = 0
    self.x_position                   = 0
    self.y_position                   = 0
    self.z_position                   = 0
    self.NOERROR                      = 0x0000
    self.UNKONWN_COMMAND              = 0x0001
    self.WRONG_PARAMETER_VALUE        = 0x0014
    self.UNKNOWN_PARAMETER_ID         = 0x0015
    self.WAKEUP_HAPPEND               = 0x001A
    self.NO_GESTURE                   = 0
    self.GARBAGE_MODEL                = 1
    self.FILCK_R                      = 2
    self.FILCK_L                      = 3
    self.FILCK_U                      = 4
    self.FILCK_D                      = 5
    self.CIRCLE_CLOCKWISE             = 6
    self.CIRCLE_COUNTERCLOCKWISE      = 7
    self.TOUCH_SOUTH                  = 1
    self.TOUCH_WEST                   = 2
    self.TOUCH_NORTH                  = 4
    self.TOUCH_EAST                   = 8
    self.TPUCH_CENTER                 = 16
    self.TAP_SOUTH                    = 32
    self.TAP_WEST                     = 64
    self.TAP_NORTH                    = 128
    self.TAP_EAST                     = 256
    self.TAP_CENTER                   = 512
    self.DOUBLE_TAP_SOUTH             = 1024
    self.DOUBLE_TAP_WEST              = 2048
    self.DOUBLE_TAP_NORTH             = 4096
    self.DOUBLE_TAP_EAST              = 8192
    self.DOUBLE_TAP_CENTER            = 16384
    self._ts_pin = ts_pin
    self._reset_pin = reset_pin
    self.position = False
    self.last_time_stamp = 0
    self.now_time_stamp = 0
    self.i2cbus=smbus.SMBus(bus)
    self.i2c_addr = DFRobot_MGC3130_IIC_ADDR

  '''
    @brief 初始化函数
    @return 返回0表示初始化成功，返回其他值表示初始化失败
  '''
  def begin(self):
    ret = False
    self._ts_input()
    self.reset()
    while(self.disable_touch_detection()!=0):
      ret = True
    while(self.disable_approach_detection()!=0):
      ret = True
    while(self.disable_air_wheel()!=0):
      ret = True
    while(self.disable_gestures()!=0):
      ret = True
    return ret

  '''
    @brief 复位传感器
  '''
  def reset(self):
    GPIO.setup(self._reset_pin, GPIO.OUT)
    GPIO.output(self._reset_pin, GPIO.LOW)
    time.sleep(0.25)
    GPIO.output(self._reset_pin, GPIO.HIGH)
    time.sleep(2)



  '''
    @brief 开启接触检测功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def enable_touch_detection(self):
    ret = -1
    buf=[0x00,0x00,0xA2,0x97,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00]
    recv_buf=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    self._set_runtime_parameter(buf,16)
    recv_buf = self._read(16)
    if(recv_buf != 0):
      if(recv_buf[4] == 0xA2):
        ret = recv_buf[7]>>8 | recv_buf[6]
    return ret

  '''
    @brief 关闭接触检测功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def disable_touch_detection(self):
    ret = -1
    buf=[0x00,0x00,0xA2,0x97,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00]
    recv_buf=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    self._set_runtime_parameter(buf,16)
    recv_buf = self._read(16)
    if(recv_buf != 0):
      if(recv_buf[4] == 0xA2):
        ret = recv_buf[7]>>8 | recv_buf[6]
    return ret

  '''
    @brief 使能接近检测功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def enable_approach_detection(self):
    ret = -1
    buf=[0x00,0x00,0xA2,0x97,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00]
    recv_buf=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    self._set_runtime_parameter(buf,16)
    recv_buf = self._read(16)
    if(recv_buf != 0):
      if(recv_buf[4] == 0xA2):
        ret = recv_buf[7]>>8 | recv_buf[6]
    return ret

  '''
    @brief 关闭接近检测功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def disable_approach_detection(self):
    ret = -1
    buf=[0x00,0x00,0xA2,0x97,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00]
    recv_buf=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    self._set_runtime_parameter(buf,16)
    recv_buf = self._read(16)
    if(recv_buf != 0):
      if(recv_buf[4] == 0xA2):
        ret = recv_buf[7]>>8 | recv_buf[6]
    return ret

  '''
    @brief 使能AirWheel功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def enable_air_wheel(self):
    ret = -1
    buf=[0x00,0x00,0xA2,0x90,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00]
    recv_buf=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    self._set_runtime_parameter(buf,16)
    recv_buf = self._read(16)
    if(recv_buf != 0):
      if(recv_buf[4] == 0xA2):
        ret = recv_buf[7]>>8 | recv_buf[6]
    return ret

  '''
    @brief 关闭手势识别功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def disable_air_wheel(self):
    ret = -1
    buf=[0x00,0x00,0xA2,0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00]
    recv_buf=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    self._set_runtime_parameter(buf,16)
    recv_buf = self._read(16)
    if(recv_buf != 0):
      if(recv_buf[4] == 0xA2):
        ret = recv_buf[7]>>8 | recv_buf[6]
    return ret

  '''
    @brief 使能手势识别功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def enable_gestures(self):
    ret = -1
    buf=[0x00,0x00,0xA2,0x85,0x00, 0x00,0x00, 0x7F,0x00,0x00,0x00, 0x7F,0x00,0x00,0x00]
    recv_buf=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    self._set_runtime_parameter(buf,16)
    recv_buf = self._read(16)
    if(recv_buf != 0):
      if(recv_buf[4] == 0xA2):
        ret = recv_buf[7]>>8 | recv_buf[6]
    return ret

  '''
    @brief 关闭手势识别功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def disable_gestures(self):
    ret = -1
    buf=[0x00,0x00,0xA2,0x85,0x00, 0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00]
    recv_buf=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    self._set_runtime_parameter(buf,16)
    recv_buf = self._read(16)
    if(recv_buf != 0):
      if(recv_buf[4] == 0xA2):
        ret = recv_buf[7]>>8 | recv_buf[6]
    return ret

  '''
    @brief 设置传感器的输出数据格式
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def enable_data_output(self):
    ret = -1
    buf=[0x00,0x00,0xA2,0xA0,0x00, 0x00,0x00, 0x1E,0x00,0x00,0x00, 0xFF,0xFF,0xFF,0xFF]
    recv_buf=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    self._set_runtime_parameter(buf,16)
    recv_buf = self._read(16)
    if(recv_buf != 0):
      if(recv_buf[4] == 0xA2):
        ret = recv_buf[7]>>8 | recv_buf[6]
    return ret

  '''
    @brief 锁定传感器的输出数据格式
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def lock_data_output(self):
    ret = -1
    buf=[0x00,0x00,0xA2,0xA1,0x00, 0x00,0x00, 0x1E,0x00,0x00,0x00, 0xFF,0xFF,0xFF,0xFF]
    recv_buf=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    self._set_runtime_parameter(buf,16)
    recv_buf = self._read(16)
    if(recv_buf != 0):
      if(recv_buf[4] == 0xA2):
        ret = recv_buf[7]>>8 | recv_buf[6]
    return ret

  '''
    @brief 获取X轴位置
    @return X轴位置
  '''
  def get_x_position(self):
    return self.x_position

  '''
    @brief 获取Y轴位置
    @return Y轴位置
  '''
  def get_y_position(self):
    return self.y_position

  '''
    @brief 获取Z轴位置
    @return Z轴位置
  '''
  def get_z_position(self):
    return self.z_position

  '''
    @brief 获取接触信息
    @return 接触信息:
              DOUBLE_TAP_CENTER/DOUBLE_TAP_EAST/DOUBLE_TAP_NORTH/DOUBLE_TAP_WEST/DOUBLE_TAP_SOUTH
              TAP_CENTER/TAP_EAST/TAP_NORTH/TAP_WEST/TAP_SOUTH
              TPUCH_CENTER/TOUCH_EAST/TOUCH_NORTH/TOUCH_WEST/TOUCH_SOUTH
  '''
  def get_touch_info(self):
    data = self.touch_info & 0xFFFF
    if(self.touch_info & 0x3E0):
      if((self.now_touch == self.last_touch) and (self.now_time_stamp == self.last_time_stamp)):
        data = self.touch_info & 0xFC1F
    if(self.touch_info & 0x7C00):
      if((self.now_touch == self.last_touch) and (self.now_time_stamp == self.last_time_stamp)):
        data = self.touch_info & 0x83FF
    self.last_touch  = self.now_touch
    self.last_time_stamp  = self.now_time_stamp
    return data

  '''
    @brief 获取手势信息
    @return 手势信息
  '''
  def get_gesture_info(self):
    return self.gesture_info & 0xFF

  '''
    @brief 监测是否有位置信息
    @return 返回true，代表有位置信息，false代表没有
  '''
  def have_position_info(self):
    return self.position

  '''
    @brief 获取传感器数据
  '''
  def sensor_data_recv(self):
    buf=self._read(24)
    if(buf!=0):
      if((buf[3] == 0x91) and (buf[4] == 0x1E)):
        self.gesture_info = buf[8] | buf[9]<<8 | buf[10]<<16 | buf[11]<<24
        self.touch_info = buf[12] | buf[13]<<8 | buf[14]<<16 | buf[15]<<24
        self.now_time_stamp = buf[14] | buf[15]<<8
        self.now_touch = buf[12] | buf[13]<<8
        if(buf[7] & 0x02):
          self.air_wheel_info = buf[16] | buf[17]<<8
        else:
          self.air_wheel_info = 0
        if(buf[7] & 0x01):
          self.position = True
          self.x_position = buf[18] | buf[19]<<8
          self.y_position = buf[20] | buf[21]<<8
          self.z_position = buf[22] | buf[23]<<8
        else:
          self.position = False
          self.x_position = 0
          self.y_position = 0
          self.z_position = 0
      else:
          self.position = False
          self.x_position = 0
          self.y_position = 0
          self.z_position = 0
          self.air_wheel_info = 0
          self.gesture_info = 0
          self.touch_info = 0
    else:
      self.position = False
      self.x_position = 0
      self.y_position = 0
      self.z_position = 0
      self.air_wheel_info = 0
      self.gesture_info = 0
      self.touch_info = 0

  '''
    @brief 设置主机的ts_pin为输入模式(TS:transfer status line)
  '''
  def _ts_input(self):
    GPIO.setup(self._ts_pin, GPIO.IN)

  '''
    @brief 设置主机的ts_pin为输出模式(TS:transfer status line)
  '''
  def _ts_output(self):
    GPIO.setup(self._ts_pin, GPIO.OUT)

  '''
    @brief 设置主机的ts_pin为输出状态(TS:transfer status line)
    @param mode 输出状态，HIGH/LOW
  '''
  def _ts_write(self,mode):
    if(mode):
      GPIO.output(self._ts_pin, GPIO.HIGH)
    else:
      GPIO.output(self._ts_pin, GPIO.LOW)

  '''
    @brief 获取的transfer status line的状态
    @param return HIGH/LOW
  '''
  def _ts_read(self):
    return GPIO.input(self._ts_pin)

  '''
    @brief 写入传感器IIC数据
    @param pBuf 要写入数据的存放缓存
    @param size 要写入数据的长度
    @return 返回实际写入的长度
  '''
  def _set_runtime_parameter(self,buf,len):
    self.i2cbus.write_i2c_block_data(self.i2c_addr, 0x10, buf)
  '''
    @brief 获取传感器IIC数据
    @param pBuf 要写入数据的存放缓存
    @param size 要写入数据的长度
    @return 返回实际读取的长度，返回0表示读取失败
  '''
  def _read(self,len):
    #self._ts_input()
    if(self._ts_read() != 0):
      return 0
    self._ts_output()
    self._ts_write(0)
    data = self.i2cbus.read_i2c_block_data(self.i2c_addr, 0x00, len)
    self._ts_write(1)
    self._ts_input()
    return data

