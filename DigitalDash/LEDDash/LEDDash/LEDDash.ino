#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  // Required for Serial on Zero based boards
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif

#ifndef ARDUINO_FEATHER_M4_CAN
  #error "This sketch should be compiled for Arduino Feather M4 CAN (SAME51)"
#endif

#include <CANSAME5x.h>
#include <Arduino.h>
#include <Wire.h>
#include "IS31FL3741.h"
#include "Globals.h"
#include "LEDdisplay.h"


Display display;
CANSAME5x CAN;

// the setup function runs once when you press reset or power the board
void setup() {

  //set up the CAN transceiver
  pinMode(PIN_CAN_STANDBY, OUTPUT);
  digitalWrite(PIN_CAN_STANDBY, false); // turn off STANDBY
  pinMode(PIN_CAN_BOOSTEN, OUTPUT);
  digitalWrite(PIN_CAN_BOOSTEN, true); // turn on booster

  Wire.begin();
  Wire.setClock(2000000);

  display.begin();
  display.setBrightness(0x40);

  Serial.begin(115200);
  //pause for serial to init
  //can't do while(!serial.begin()) because
  //it won't be attached to a computer in the car
  delay(1000);

  if (!CAN.begin(500000)) {
    Serial.println("Starting CAN failed!");
    while (1) delay(10);
  }
  Serial.println("Started CAN");

  CAN.onReceive(onReceive);

  delay(100);

  Serial.println("\n\nBegin LED Dash");

  display.clearScreen();
  display.introGraphic();
}

// the loop function runs over and over again forever
void loop() {

  display.clearScreen();

  for(int i = 0; i < 100 ; i++)
  {
    //Serial.print("Sending data ");
    //Serial.println(i);
    //CAN.beginExtendedPacket(420011);
    //CAN.write(i);
    //CAN.endPacket();
    display.printSpeed(i);
    display.printGears();
    delay(100);
  }
}

void onReceive(int packetSize)
{

  uint8_t receivedData;

  /* received a packet
  Serial.print("Received ");

  if (CAN.packetExtended()) {
    Serial.print("extended ");
  }

  if (CAN.packetRtr()) {
    // Remote transmission request, packet contains no data
    Serial.print("RTR ");
  }

  Serial.print("packet with id 0x");
  Serial.print(CAN.packetId(), HEX);

  if (CAN.packetRtr()) {
    Serial.print(" and requested length ");
    Serial.println(CAN.packetDlc());
  } else {
    Serial.print(" and length ");
    Serial.println(packetSize);

  }

  Serial.println();
  */
  if(CAN.packetId() == 0x420010)
  {
    while(CAN.available()){
      receivedData = CAN.read();
      //Serial.println("received good data");
      //Serial.print(receivedData, HEX);
    }
    switch (receivedData) {
        case 0xAA:
          // Drive gear is selected
          //Serial.println("Drive Gear selected");
          gearDrive = true;
          gearNeutral = false;
          gearReverse = false;
          break;
        case 0x55:
          //Serial.println("Neutral Gear selected");
          // Neutral gear is selected
          gearDrive = false;
          gearNeutral = true;
          gearReverse = false;
          break;
        case 0xFF:
          //Serial.println("Reverse Gear selected");
          // Reverse gear is selected
          gearDrive = false;
          gearNeutral = false;
          gearReverse = true;
          break;
        default:
          // Handle other data values, if needed
          break;
      }
    }
}