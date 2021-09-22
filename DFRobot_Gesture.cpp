/*!
 * @file DFRobot_Gesture.cpp
 * @brief 定义DFRobot_Sensor 类的基础结构，基础方法的实现
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [yangfeng](feng.yang@dfrobot.com)
 * @version  V1.0
 * @date  2021-09-18
 * @url https://github.com/DFRobot/DFRobot_Gesture
 */
#include <DFRobot_Gesture.h>


DFRobot_Gesture::DFRobot_Gesture(uint8_t TSPin,uint8_t restPin,TwoWire *pWire)
{
  _deviceAddr = DFRobot_Gesture_IIC_ADDR;
  _pWire = pWire;
  _tsPin = TSPin;
  _resPin = restPin;
  position = false;
  lastTimeStamp=0 ;
}

int DFRobot_Gesture::begin(void)
{
  _pWire->begin();
  tsInput();
  reset();
  uint32_t time = millis();
  while(disableTouchDetection()!=0){
    if(millis() - time > 2000){
      return false;
    }
  }
  time = millis();
  while(disableApproachDetection()!=0){
    if(millis() - time > 2000){
      return false;
    }
  }
  time = millis();
  while(disableAirWheel()!=0){
    if(millis() - time > 2000){
      return false;
    }
  }
  time = millis();
  while(disableGestures()!=0){
    if(millis() - time > 2000){
      return false;
    }
  }
  return true;
}
void DFRobot_Gesture:: reset()
{
  pinMode(_resPin,OUTPUT);
  digitalWrite(_resPin,LOW);
  delay(250);
  digitalWrite(_resPin,HIGH);
  delay(2000);
}
void DFRobot_Gesture::tsInput(void)
{
  pinMode(_tsPin,INPUT);//INPUT_PULLUP
}
void DFRobot_Gesture::tsOutput(void)
{
  pinMode(_tsPin,OUTPUT);
}
void DFRobot_Gesture::tsWrite(uint8_t mode)
{
  digitalWrite(_tsPin,mode);
}
uint8_t DFRobot_Gesture::tsRead()
{
  return digitalRead(_tsPin);
}
int8_t DFRobot_Gesture::enableTouchDetection()
{
  uint8_t pBuf[]={0x97,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x00};
  uint8_t recvBuf[16];
  int8_t ret = -1;
  setRuntimeparameter(pBuf,12);
  if(read(recvBuf,16)!=0){
    if(recvBuf[4] == 0xA2){
      uint16_t errorCode = (uint16_t)recvBuf[7]>>8 | recvBuf[6];
      if(errorCode==0){
        ret = 0;
      }
    }
  }
  return ret;
}
int8_t DFRobot_Gesture::disableTouchDetection()
{
  uint8_t pBuf[]={0x97,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00};
  uint8_t recvBuf[16];
  int8_t ret =-1;
  setRuntimeparameter(pBuf,12);
  if(read(recvBuf,16)!=0){
    if(recvBuf[4] == 0xA2){
      uint16_t errorCode = (uint16_t)recvBuf[7]>>8 | recvBuf[6];
      if(errorCode==0){
        ret = 0;
      }
    }
  }
  return ret;
}
int8_t DFRobot_Gesture::enableApproachDetection()
{
  uint8_t pBuf[]={0x97,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00};
  uint8_t recvBuf[16];
  int8_t ret = -1;
  setRuntimeparameter(pBuf,12);
  if(read(recvBuf,16)!=0){
    if(recvBuf[4] == 0xA2){
      uint16_t errorCode = (uint16_t)recvBuf[7]>>8 | recvBuf[6];
      if(errorCode==0){
        ret = 0;
      }
    }
  }
  return ret;
}
int8_t DFRobot_Gesture::disableApproachDetection()
{
  uint8_t pBuf[]={0x97,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00};
  uint8_t recvBuf[16];
  int8_t ret = -1;
  setRuntimeparameter(pBuf,12);
  if(read(recvBuf,16)!=0){
    if(recvBuf[4] == 0xA2){
      uint16_t errorCode = (uint16_t)recvBuf[7]>>8 | recvBuf[6];
      if(errorCode==0){
        ret = 0;
      }
    }
  }
  return ret;
}

int8_t DFRobot_Gesture::enableAirWheel()
{
  uint8_t pBuf[]={0x90,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00};
  uint8_t recvBuf[16];
  int8_t ret = -1;
  setRuntimeparameter(pBuf,12);
  if(read(recvBuf,16)!=0){
    if(recvBuf[4] == 0xA2){
      uint16_t errorCode = (uint16_t)recvBuf[7]>>8 | recvBuf[6];
      if(errorCode==0){
        ret = 0;
      }
    }
  }
  return ret;
}
int8_t DFRobot_Gesture::disableAirWheel()
{
  uint8_t pBuf[]={0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00};
  uint8_t recvBuf[16];
  int8_t ret = -1;
  setRuntimeparameter(pBuf,12);
  if(read(recvBuf,16)!=0){
    if(recvBuf[4] == 0xA2){
      uint16_t errorCode = (uint16_t)recvBuf[7]>>8 | recvBuf[6];
      if(errorCode==0){
        ret = 0;
      }
    }
  }
  return ret;
}


int8_t DFRobot_Gesture::enableGestures()
{
  uint8_t pBuf[]={0x85,0x00, 0x00,0x00, 0x7F,0x00,0x00,0x00, 0x7F,0x00,0x00,0x00};
  uint8_t recvBuf[16];
  int8_t ret = -1;
  setRuntimeparameter(pBuf,12);
  if(read(recvBuf,16)!=0){
    if(recvBuf[4] == 0xA2){
      uint16_t errorCode = (uint16_t)recvBuf[7]>>8 | recvBuf[6];
      if(errorCode==0){
        ret = 0;
      }
    }
  }
  return ret;
}

int8_t DFRobot_Gesture::disableGestures()
{
  uint8_t pBuf[]={0x85,0x00, 0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00};
  uint8_t recvBuf[16];
  int8_t ret = -1;
  setRuntimeparameter(pBuf,12);
  if(read(recvBuf,16)!=0){
    if(recvBuf[4] == 0xA2){
      uint16_t errorCode = (uint16_t)recvBuf[7]>>8 | recvBuf[6];
      if(errorCode==0){
        ret = 0;
      }
    }
  }
  return ret;
}
int8_t DFRobot_Gesture::enableDataOutput()
{
  uint8_t pBuf[]={0xA0,0x00, 0x00,0x00, 0x1E,0x00,0x00,0x00, 0xFF,0xFF,0xFF,0xFF};
  uint8_t recvBuf[16];
  int8_t ret = -1;
  setRuntimeparameter(pBuf,12);
  if(read(recvBuf,16)!=0){
    if(recvBuf[4] == 0xA2){
      uint16_t errorCode = (uint16_t)recvBuf[7]>>8 | recvBuf[6];
      if(errorCode==0){
        ret = 0;
      }
    }
  }
  return ret;
}
int8_t DFRobot_Gesture::lockDataOutput()
{
  uint8_t pBuf[]={0xA1,0x00, 0x00,0x00, 0x1E,0x00,0x00,0x00, 0xFF,0xFF,0xFF,0xFF};
  uint8_t recvBuf[16];
  int8_t ret = -1;
  setRuntimeparameter(pBuf,12);
  if(read(recvBuf,16)!=0){
    if(recvBuf[4] == 0xA2){
      uint16_t errorCode = (uint16_t)recvBuf[7]>>8 | recvBuf[6];
      if(errorCode==0){
        ret = 0;
      }
    }
  }
  return ret;
}
uint16_t DFRobot_Gesture:: getXposition()
{
  return info.xPosition;
}
uint16_t DFRobot_Gesture:: getYposition()
{
  return info.yPosition;
}
uint16_t DFRobot_Gesture:: getZposition()
{
  return info.zPosition;
}
uint16_t DFRobot_Gesture:: getTouchInfo()
{
  uint16_t data = 0;
  data = info.touchInfo & 0xFFFF;
  if(info.touchInfo & 0x3E0){
    if((nowTouch == lastTouch) && (nowTimeStamp == lastTimeStamp)){
      data = info.touchInfo & 0xFC1F;
    }
  }
  if(info.touchInfo & 0x7C00){
    if((nowTouch == lastTouch) && (nowTimeStamp == lastTimeStamp)){
      data = info.touchInfo & 0x83FF;
    }
  }
  lastTouch = nowTouch;
  lastTimeStamp = nowTimeStamp;
  return data;
}

uint8_t DFRobot_Gesture:: getGestureInfo()
{

  return (uint8_t) (info.gestureInfo & 0xFF);
}
bool DFRobot_Gesture:: havePositionInfo()
{
  return position;
}
void DFRobot_Gesture:: sensorDataRecv()
{
  uint8_t pbuf[24];
  if(read(pbuf,24)!=0){
    if((pbuf[3] == 0x91) && (pbuf[4] == 0x1E)){
      info.gestureInfo  = pbuf[8]  | (uint32_t)pbuf[9]<<8  | (uint32_t)pbuf[10]<<16 |  (uint32_t)pbuf[11]<<24;
      info.touchInfo    = pbuf[12] | (uint32_t)pbuf[13]<<8 | (uint32_t)pbuf[14]<<16 |  (uint32_t)pbuf[15]<<24;
      nowTimeStamp = (uint32_t)pbuf[14] |  (uint32_t)pbuf[15]<<8;
      nowTouch = pbuf[12] | (uint32_t)pbuf[13]<<8;
      if(pbuf[7] & 0x02){
        info.airWheelInfo = pbuf[16] | (uint32_t)pbuf[17]<<8;
      }else{
        info.airWheelInfo = 0;
      }
      if(pbuf[7] & 0x01){
        position = true;
        info.xPosition    = pbuf[18] | (uint32_t)pbuf[19]<<8;
        info.yPosition    = pbuf[20] | (uint32_t)pbuf[21]<<8;
        info.zPosition    = pbuf[22] | (uint32_t)pbuf[23]<<8;
      }else{
        position = false;
        info.xPosition = 0;
        info.yPosition = 0;
        info.zPosition = 0;
      }
    } else{
        position = false;
        info.gestureInfo = 0;
        info.touchInfo = 0;
        info.airWheelInfo = 0;
        info.xPosition = 0;
        info.yPosition = 0;
        info.zPosition = 0;
    }
  }else{
    position = false;
    info.gestureInfo = 0;
    info.touchInfo = 0;
    info.airWheelInfo = 0;
    info.xPosition = 0;
    info.yPosition = 0;
    info.zPosition = 0;
    delay(5);
  }
}

uint8_t DFRobot_Gesture::setRuntimeparameter(void* pBuf,size_t size)
{
  if(pBuf == NULL){
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write((uint8_t)0x10);
  _pWire->write((uint8_t)0x00);
  _pWire->write((uint8_t)0x00);
  _pWire->write((uint8_t)0xA2);
  for(uint16_t i = 0; i < size; i++){
    _pWire->write(_pBuf[i]);
  }
  _pWire->endTransmission();
  return size;
}
uint8_t DFRobot_Gesture::read(void* pBuf, size_t size)
{
  if(pBuf == NULL){
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  if(tsRead() != 0){
   return 0;
  }
  tsOutput();
  tsWrite(LOW);
  _pWire->requestFrom(_deviceAddr, (uint8_t) size);
  for(uint16_t i = 0; i < size; i++){
    _pBuf[i] = _pWire->read();
  }
  _pWire->endTransmission();
  tsWrite(HIGH);
  tsInput();
  return size;
}





