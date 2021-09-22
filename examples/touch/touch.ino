/*!
 * @file touch.ino
 * @brief 检测5个电场（上、下、左、右、中）的touch情况，可以是：触摸、点击、双击
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence The MIT License (MIT)
 * @author [yangfeng]<feng.yang@dfrobot.com>
 * @version V1.0
 * @date 2021-09-18
 * @url  https://github.com/DFRobot/DFRobot_MGC3130
 * 
 * Hardware Connections:
 * HOST Pin    SENSOR PIN        Function
 *  GND          GND              Ground
 *  3.3V-5V      VCC              Power
 *  SCL          SCL              I2C Clock
 *  SDA          SDA              I2C Data
 *  7            D                Digital port
 */
#include <DFRobot_MGC3130.h>

#if defined(ESP32) || defined(ESP8266)
  uint8_t TSPin= D9;
  uint8_t restPin= D3;
#elif defined(ARDUINO_SAM_ZERO)
  uint8_t TSPin= 6;
  uint8_t restPin= 7;
#else
  uint8_t TSPin= 8;
  uint8_t restPin= 9;
#endif

DFRobot_MGC3130 myGesture(TSPin,restPin);

void setup()
{
  Serial.begin(115200);
  /**
   * @brief 初始化函数
   * @return 返回0表示初始化成功，返回其他值表示初始化失败
   */
  while(!myGesture.begin()){
    delay(100);
  }
  Serial.println("begin success!!!");

  /**
   * @brief 开启接触检测功能
   * @return 返回-1代表设置失败，0代表设置成功
   */
  while(myGesture.enableTouchDetection()!=0){
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
   * @brief 获取接触信息
   * @return 接触信息:
   *         eDoubleTapCenter/eDoubleTapEast/eDoubleTapNorth/eDoubleTapWest/eDoubleTapSouth/eTapCenter/
   *         eTapEast/eTapNorth/eTapWest/eTapSouth/eTouchCenter/eTouchEast/eTouchNorth/eTouchWest/eTouchSouth
   */
  uint16_t info = myGesture.getTouchInfo();
  if(info & myGesture.eDoubleTapCenter){
    Serial.println("Double Tap Center electrode");
  } 
  if(info & myGesture.eDoubleTapEast){
    Serial.println("Double Tap East electrode");
  } 
  if(info & myGesture.eDoubleTapNorth){
    Serial.println("Double Tap North electrode");
  } 
  if(info & myGesture.eDoubleTapWest){
    Serial.println("Double Tap West electrode");
  } 
  if(info & myGesture.eDoubleTapSouth){
    Serial.println("Double Tap South electrode");
  } 
  if(info & myGesture.eTapCenter){
    Serial.println("Tap Center electrode");
  } 
  if(info & myGesture.eTapEast){
    Serial.println("Tap East electrode");
  } 
  if(info & myGesture.eTapNorth){
    Serial.println("Tap North electrode");
  } 
  if(info & myGesture.eTapWest){
    Serial.println("Tap West electrode");
  } 
  if(info & myGesture.eTapSouth){
    Serial.println("Tap South electrode");
  } 
  if(info & myGesture.eTouchCenter){
    Serial.println("Touch Center electrode");
  } 
  if(info & myGesture.eTouchEast){
    Serial.println("Touch East electrode");
  } 
  if(info & myGesture.eTouchNorth){
    Serial.println("Touch North electrode");
  } 
  if(info & myGesture.eTouchWest){
    Serial.println("Touch West electrode");
  } 
  if(info & myGesture.eTouchSouth){
    Serial.println("Touch South electrode");
  }
}