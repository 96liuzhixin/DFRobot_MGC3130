/*!
 * @file DFRobot_MGC3130.h
 * @brief DFRobot_MGC3130 类的基础结构
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [yangfeng](feng.yang@dfrobot.com)
 * @version  V1.0
 * @date  2021-09-18
 * @url https://github.com/DFRobot/DFRobot_MGC3130
 */
#ifndef __DFRobot_MGC3130_H
#define __DFRobot_MGC3130_H

#include <Arduino.h>
#include <Wire.h>

//打开这个宏，可以看到程序的详细运行过程
 #define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...)  {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define DFRobot_MGC3130_IIC_ADDR 0x42
class DFRobot_MGC3130{
public:
  typedef struct {
    uint32_t gestureInfo;
    uint32_t touchInfo;
    uint32_t airWheelInfo;
    uint16_t xPosition;
    uint16_t yPosition;
    uint16_t zPosition;
  }__attribute__ ((packed)) sInfo_t;

  typedef enum{
    eNoError = 0x0000,             /**< OK */
    eUnknownCommand = 0x0001,      /**< Message ID is unknown */
    eWrongParameterValue = 0x0014, /**< The value of the Argument/Parameter of a RuntimeParameter command is out of the valid range */
    eUnknownParameterID = 0x0015,  /**< The MessageID or RuntimeParameterID is unknown or out of the valid range */
    eWakeupHappend = 0x001A,       /**< A wake-up by Host was detected */
  }eErrorCode_t;

  //Gesture Info
  typedef enum{
    eNoGesture = 0,           /**< No gesture */
    eGarbageModel,            /**< Garbage model */
    eFilckR,                  /**< Flick West to East */
    eFilckL,                  /**< Flick East to West */
    eFilckU,                  /**< Flick South to North */
    eFilckD,                  /**< Flick North to South */
    eCircleClockwise,         /**< Circle clockwise (only active if AirWheel disabled) */
    eCircleCounterclockwise,  /**< Circle counterclockwise (only active if AirWheel disabled) */
  }eGestureInfo_t;
  
  //Touch Info
  typedef enum{
    eTouchSouth       = 1,           /**< Touch South electrode */
    eTouchWest        = 2,           /**< Touch West electrode */
    eTouchNorth       = 4,           /**< Touch North electrode */
    eTouchEast        = 8,           /**< Touch East electrode */
    eTouchCenter      = 16,          /**< Touch Center electrode */
    eTapSouth         = 32,          /**< Tap South electrode*/
    eTapWest          = 64,          /**< Tap West electrode */
    eTapNorth         = 128,         /**< Tap North electrode */
    eTapEast          = 256,         /**< Tap East electrode */
    eTapCenter        = 512,         /**< Tap Center electrode */
    eDoubleTapSouth   = 1024,        /**< Double Tap South electrode*/
    eDoubleTapWest    = 2048,        /**< Double Tap West electrode */
    eDoubleTapNorth   = 4096,        /**< Double Tap North electrode */
    eDoubleTapEast    = 8192,        /**< Double Tap East electrode */
    eDoubleTapCenter  = 16384,       /**< Double Tap Center electrode */
  }eTouchInfo_t;

  DFRobot_MGC3130(uint8_t DPin,uint8_t MCLRPin ,TwoWire *pWire=&Wire);
  /**
   * @brief 初始化函数
   * @return 返回true 表示初始化成功，返回false初始化失败
   */
  int begin(void);

  /**
   * @brief 复位传感器
   */
  void reset(void);

  /**
   * @brief 获取传感器数据
   */
  void sensorDataRecv(void);

  /**
   * @brief 使能手势识别功能
   * @return 返回-1代表设置失败，0代表设置成功
   */
  int8_t enableGestures(void);

  /**
   * @brief 关闭手势识别功能
   * @return 返回-1代表设置失败，0代表设置成功
   */
  int8_t disableGestures(void);

  /**
   * @brief 关闭AirWheel功能
   * @return 返回-1代表设置失败，0代表设置成功
   */
  int8_t disableAirWheel(void);

  /**
   * @brief 使能AirWheel功能
   * @return 返回-1代表设置失败，0代表设置成功
   */
  int8_t enableAirWheel(void);

  /**
   * @brief 关闭接近检测功能
   * @return 返回-1代表设置失败，0代表设置成功
   */
  int8_t disableApproachDetection(void);

  /**
   * @brief 使能接近检测功能
   * @return 返回-1代表设置失败，0代表设置成功
   */
  int8_t enableApproachDetection(void);

  /**
   * @brief 关闭接触检测功能
   * @return 返回-1代表设置失败，0代表设置成功
   */
  int8_t disableTouchDetection(void);

  /**
   * @brief 开启接触检测功能
   * @return 返回-1代表设置失败，0代表设置成功
   */
  int8_t enableTouchDetection(void);

  /**
   * @brief 获取X轴位置
   * @return X轴位置
   */
  uint16_t getPositionX(void);

  /**
   * @brief 获取Y轴位置
   * @return Y轴位置
   */
  uint16_t getPositionY(void);

  /**
   * @brief 获取Z轴位置
   * @return Z轴位置
   */
  uint16_t getPositionZ(void);

  /**
   * @brief 获取接触信息
   * @return 接触信息:
   *         eDoubleTapCenter/eDoubleTapEast/eDoubleTapNorth/eDoubleTapWest/eDoubleTapSouth/eTapCenter/
   *         eTapEast/eTapNorth/eTapWest/eTapSouth/eTouchCenter/eTouchEast/eTouchNorth/eTouchWest/eTouchSouth
   */
  uint16_t getTouchInfo(void);

  /**
   * @brief 获取手势信息
   * @return 手势信息:eFilckR/eFilckL/eFilckU/eFilckD/eCircleClockwise/eCircleCounterclockwise
   */
  uint8_t getGestureInfo(void);

  /**
   * @brief 监测是否有位置信息
   * @return 返回true，代表有位置信息，false代表没有
   */
  bool havePositionInfo(void);

private:

  /**
   * @brief 锁定传感器的输出数据格式
   * @return 返回-1代表设置失败，0代表设置成功
   */
  int8_t lockDataOutput(void);

  /**
   * @brief 设置传感器的输出数据格式
   * @return 返回-1代表设置失败，0代表设置成功
   */
  int8_t enableDataOutput(void);

  /**
   * @brief 设置主机的ts_pin为输入模式(TS:transfer status line)
   */
  void tsInput(void);

  /**
   * @brief 设置主机的ts_pin为输出模式(TS:transfer status line)
   */
  void tsOutput(void);

  /**
   * @brief 设置主机的ts_pin为输出状态(TS:transfer status line)
   * @param mode 输出状态，HIGH/LOW
   */
  void tsWrite(uint8_t mode);

  /**
   * @brief 获取的transfer status line的状态
   * @param return HIGH/LOW
   */
  uint8_t tsRead(void);

  /**
   * @brief 获取传感器IIC数据
   * @param pBuf 要写入数据的存放缓存
   * @param size 要写入数据的长度
   * @return 返回实际读取的长度，返回0表示读取失败
   */
  uint8_t read(void* pBuf, size_t size);

  /**
   * @brief 写入传感器IIC数据
   * @param pBuf 要写入数据的存放缓存
   * @param size 要写入数据的长度
   * @return 返回实际写入的长度
   */
  uint8_t setRuntimeparameter(void* pBuf,size_t size);

private:
  TwoWire *_pWire;
  uint8_t _deviceAddr;
  uint8_t _tsPin;
  sInfo_t info;
  bool position;
  uint16_t lastTimeStamp,nowTimeStamp;
  uint16_t lastTouch,nowTouch;
  uint8_t _resPin;
};



#endif
