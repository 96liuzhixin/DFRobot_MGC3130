/*!
 * @file position.ino
 * @brief 位置识别，x,y,z轴上数据
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
   * @brief 使能接近检测功能
   * @return 返回-1代表设置失败，0代表设置成功
   */
  while (myGesture.enableApproachDetection() != 0){
    delay(100);
  }
  
  /**
   * @brief 设置传感器的输出数据格式
   * @return 返回-1代表设置失败，0代表设置成功
   */
  while(myGesture.enableDataOutput()!=0){
    delay(100);
  }

  /**
   * @brief 锁定传感器的输出数据格式
   * @return 返回-1代表设置失败，0代表设置成功
   */
  while(myGesture.lockDataOutput()!=0){
    delay(100);
  }
  Serial.println("config success!!!");
}
void loop()
{
  /**
   * @brief 获取传感器数据
   */
  myGesture.sensorDataRecv();

  /**
   * @brief 监测是否有位置信息
   * @return 返回true，代表有位置信息，false代表没有
   */
  if(myGesture.havePositionInfo()){
    Serial.print("X: ");
    Serial.print(myGesture.getXposition());
    Serial.print("   Y: ");
    Serial.print(myGesture.getYposition());
    Serial.print("   Z: ");
    Serial.println(myGesture.getZposition());
  }
}