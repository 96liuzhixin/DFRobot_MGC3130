/*!
 * @file position.ino
 * @brief 位置识别,x,y,z轴上数据(零点在触板的西南位置,丝印Down处)
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
   * @brief 使能接近检测功能
   * @return 返回-1代表设置失败，0代表设置成功
   */
  while (myGesture.enableApproachDetection() != 0){
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
    Serial.print(myGesture.getPositionX());
    Serial.print("   Y: ");
    Serial.print(myGesture.getPositionY());
    Serial.print("   Z: ");
    Serial.println(myGesture.getPositionZ());
  }
}
