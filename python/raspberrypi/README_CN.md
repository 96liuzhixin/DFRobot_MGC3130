# DFRobot_MGC3130
- [English Version](./README.md)

3D手势识别传感器是一款集成3D手势识别和运动跟踪为一体的交互式传感器，传感器可以在有效范围内识别手指的顺时针/逆时针转动方向和手指的运动方向等。传感器基于Microchip专利的GestIC®技术，采用电近场传感技术，包括了开发3D手势输入传感系统所有的块图，具有先进的3D信号处理单元，有效检测距离为0~10 cm。



![正反面svg效果图](../../resources/images/SEN0202.jpg)


## 产品链接(https://www.dfrobot.com.cn/goods-1342.html)

    SKU：SEN0202

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性y)
* [历史](#历史)
* [创作者](#创作者)

## 概述

库中提供了手势识别、接触识别、接近位置监测三个示例。

手势识别：左-->右、右-->左、上-->下、下-->上

接触识别：上下左右中的单击、上下左右中的双击、上下左右中的触摸

接近位置识别：X、Y、Z三轴方向上的位置数据

## 库安装

使用此库前，请首先下载库文件，将其粘贴到树莓派的自定义目录中，然后打开examples文件夹并在该文件夹中运行演示。

## 方法

```python
  '''
    @brief 初始化函数
    @return 返回True表示初始化成功，返回False表示初始化失败
  '''
  def begin(self)

  '''
    @brief 复位传感器
  '''
  def reset(self)

  '''
    @brief 开启接触检测功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def enable_touch_detection(self)

  '''
    @brief 关闭接触检测功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def disable_touch_detection(self)

  '''
    @brief 使能接近检测功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def enable_approach_detection(self)

  '''
    @brief 关闭接近检测功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def disable_approach_detection(self)

  '''
    @brief 使能AirWheel功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def enable_air_wheel(self)

  '''
    @brief 关闭手势识别功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def disable_air_wheel(self)

  '''
    @brief 使能手势识别功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def enable_gestures(self)

  '''
    @brief 关闭手势识别功能
    @return 返回-1代表设置失败，0代表设置成功
  '''
  def disable_gestures(self)

  '''
    @brief 获取X轴位置
    @return X轴位置
  '''
  def get_x_position(self)

  '''
    @brief 获取Y轴位置
    @return Y轴位置
  '''
  def get_y_position(self)

  '''
    @brief 获取Z轴位置
    @return Z轴位置
  '''
  def get_z_position(self)

  '''
    @brief 获取接触信息
    @return 接触信息:
              DOUBLE_TAP_CENTER/DOUBLE_TAP_RIGHT/DOUBLE_TAP_UP/DOUBLE_TAP_LEFT/DOUBLE_TAP_DOWN
              TAP_CENTER/TAP_RIGHT/TAP_UP/TAP_LEFT/TAP_DOWN
              TPUCH_CENTER/TOUCH_RIGHT/TOUCH_UP/TOUCH_LEFT/TOUCH_DOWN
  '''
  def get_touch_info(self)

  '''
    @brief 获取手势信息
    @return 手势信息
  '''
  def get_gesture_info(self)

  '''
    @brief 监测是否有位置信息
    @return 返回true，代表有位置信息，false代表没有
  '''
  def have_position_info(self)

  '''
    @brief 获取传感器数据
  '''
  def sensor_data_recv(self)
```

## 兼容性

* RaspberryPi 版本

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |           |            |    √     |         |
| RaspberryPi4 |     √     |            |          |         |

* Python 版本

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## 历史

- 日期 2021-9-22
- 版本 V1.0.0


## 创作者

Written by yangfeng(feng.yang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))

