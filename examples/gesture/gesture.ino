/*!
 * @file gesture.ino
 * @brief 手势识别，可以是up-->down 、down-->up 、 left-->right 、right-->left、Circle clockwise、Circle counterclockwise.
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version V1.0
 * @date 2021-09-18
 * @url  https://github.com/DFRobot/DFRobot_Gesture
 * 
 * Hardware Connections:
 * HOST Pin    SENSOR PIN        Function
 *  GND          GND              Ground
 *  3.3V-5V      VCC              Power
 *  SCL          SCL              I2C Clock
 *  SDA          SDA              I2C Data
 *  7            D                Digital port
 */
#include <DFRobot_Gesture.h>

#if defined(ESP32) || defined(ESP8266)
uint8_t TSPin= D9;
uint8_t restPin= D3;
#elif defined(ARDUINO_SAM_ZERO)
uint8_t TSPin= 6;
uint8_t restPin= 7;
#else
uint8_t TSPin= 8;
uint8_t restPin= 9;

DFRobot_Gesture myGesture(TSPin,restPin);

void setup()
{

  Serial.begin(115200);
  /**
   * @brief 初始化函数
   * @return 返回0表示初始化成功，返回其他值表示初始化失败
   */
  while(!myGesture.begin()){
    delay(100);
  };
  Serial.println("begin success!!!");

  /**
   * @brief 关闭AirWheel功能
   * @return 返回-1代表设置失败，0代表设置成功
   */
  while(myGesture.disableAirWheel()!=0);

  /**
   * @brief 使能手势识别功能
   * @return 返回-1代表设置失败，0代表设置成功
   */
  while(myGesture.enableGestures()!=0);

  /**
   * @brief 设置传感器的输出数据格式
   * @return 返回-1代表设置失败，0代表设置成功
   */
  while(myGesture.enableDataOutput()!=0);

  /**
   * @brief 锁定传感器的输出数据格式
   * @return 返回-1代表设置失败，0代表设置成功
   */
  while(myGesture.lockDataOutput()!=0);
}


void loop()
{
  /**
   * @brief 获取传感器数据
   */
  myGesture.sensorDataRecv();

  /**
   * @brief 获取手势信息
   * @return 手势信息:eFilckR/eFilckL/eFilckU/eFilckD/eCircleClockwise/eCircleCounterclockwise
   */
  switch(myGesture.getGestureInfo()){
    case myGesture.eFilckR:
      Serial.println("Flick Left to Right");
      break;
    case myGesture.eFilckL:
      Serial.println("Flick Right to Left");
      break;
    case myGesture.eFilckU:
      Serial.println("Flick Down to Up");
      break;
    case myGesture.eFilckD:
      Serial.println("Flick Up to Down");
      break;
    case myGesture.eCircleClockwise:
      Serial.println("Circle clockwise");
      break;
    case myGesture.eCircleCounterclockwise:
      Serial.println("Circle counterclockwise");
      break;
    default:
      break;
  }
}