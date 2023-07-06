#include "IS31FL3741.h"
#include "Arduino.h"
#include <Wire.h>



IS41::IS41(int Address)
{
  _Address = Address;
}

void IS41::begin()
{
  writeByte(_Address,0xfe,0xc5); //unlock
  writeByte(_Address, 0xfd,0x02); //write page 2
  for(int i=0;i<0xB4;i++){
    writeByte(_Address, i,255);
  }

    Serial.println("Section1");

  writeByte(_Address,0xfe,0xc5);//unlock
  writeByte(_Address,0xfD,0x03);//write page 3
  for(int i=0;i<0xAB;i++){
    writeByte(_Address, i,255);
  }
      Serial.println("Section2");

  
  writeByte(_Address,0xfe,0xc5);//unlock
  writeByte(_Address,0xfD,0x00);//write page 0
  for(int i=0;i<0xB4;i++){
    writeByte(_Address,i,0x00);//write all PWM set 0x00
  }

    Serial.println("Section3");

  writeByte(_Address,0xfe,0xc5);//unlock
  writeByte(_Address,0xfD,0x01);//write page 1

  for(int i=0;i<0xAB;i++){
    writeByte(_Address,i,0x00);//write all PWM set 0x00
  } //init all the PWM data to 0

    Serial.println("Section4");


  writeByte(_Address,0xfe,0xc5);//unlock
  writeByte(_Address,0xfD,0x04);//write page 4
  writeByte(_Address,0x01,0x08);//global current
  writeByte(_Address,0x00,0x01);//normal operation

    Serial.println("Section5");

  //try to write a pixel here
  writeByte(_Address,0xfD,0x02);//write page 4
  writeByte(_Address,0x01,0xff);//global current
  writeByte(_Address,0x00,0xff);//normal operation
      Serial.println("Section6");

}

void writeByte(uint8_t Dev_Add, uint8_t Reg_Add, uint8_t Reg_Dat)
{
  Wire.beginTransmission(Dev_Add);
  Wire.write(Reg_Add);
  Wire.write(Reg_Dat);
  Wire.endTransmission();
}