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
 *  DPin         D                Transfer Status Line
 *  MCLRPin      MCLR             reset
 */
#include <DFRobot_MGC3130.h>

//建议使用以下引脚，但用户可自定义（要求引脚具有输入和输出功能）
#if defined(ESP32) || defined(ESP8266)
  uint8_t DPin= D9;
  uint8_t MCLRPin= D3;
#elif defined(ARDUINO_SAM_ZERO)
  uint8_t DPin= 6;
  uint8_t MCLRPin= 7;
#else
  uint8_t DPin= 8;
  uint8_t MCLRPin= 9;
#endif

DFRobot_MGC3130 myGesture(DPin,MCLRPin);

void setup()
{
  Serial.begin(115200);
  /**
   * @brief 初始化函数
   * @return 返回true 表示初始化成功，返回false初始化失败
   */
  while(!myGesture.begin()){
    Serial.println("begin error! Please check whether the connection is correct");
    delay(100);
  };
  Serial.println("begin success!!!");

  /**
   * @brief 开启接触检测功能
   * @return 返回-1代表设置失败，0代表设置成功
   */
  while(myGesture.enableTouchDetection()!=0){
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
   *         eDoubleTapCenter/eDoubleTapRight/eDoubleTapUp/eDoubleTapLeft/eDoubleTapDown/eTapCenter/
   *         eTapRight/eTapUp/eTapLeft/eTapDown/eTouchCenter/eTouchRight/eTouchUp/eTouchLeft/eTouchDown
   */
  uint16_t info = myGesture.getTouchInfo();
  if(info & myGesture.eDoubleTapCenter){
    Serial.println("Double Tap Center electrode");
  } 
  if(info & myGesture.eDoubleTapRight){
    Serial.println("Double Tap Right electrode");
  } 
  if(info & myGesture.eDoubleTapUp){
    Serial.println("Double Tap Up electrode");
  } 
  if(info & myGesture.eDoubleTapLeft){
    Serial.println("Double Tap Left electrode");
  } 
  if(info & myGesture.eDoubleTapDown){
    Serial.println("Double Tap Down electrode");
  } 
  if(info & myGesture.eTapCenter){
    Serial.println("Tap Center electrode");
  } 
  if(info & myGesture.eTapRight){
    Serial.println("Tap Right electrode");
  } 
  if(info & myGesture.eTapUp){
    Serial.println("Tap Up electrode");
  } 
  if(info & myGesture.eTapLeft){
    Serial.println("Tap Left electrode");
  } 
  if(info & myGesture.eTapDown){
    Serial.println("Tap Down electrode");
  } 
  if(info & myGesture.eTouchCenter){
    Serial.println("Touch Center electrode");
  } 
  if(info & myGesture.eTouchRight){
    Serial.println("Touch Right electrode");
  } 
  if(info & myGesture.eTouchUp){
    Serial.println("Touch Up electrode");
  } 
  if(info & myGesture.eTouchLeft){
    Serial.println("Touch Left electrode");
  } 
  if(info & myGesture.eTouchDown){
    Serial.println("Touch Down electrode");
  }
}
