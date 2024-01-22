#include <mcp_can.h>
#include <mcp_can_dfs.h>

#include <mcp_can.h>
#include <avr/io.h>
#include <util/delay.h>
#include <SPI.h>

const int SPI_CS_PIN = 10;

volatile byte shiftState = 0; // 0xAA: Drive, 0x55: Neutral, 0xFF: Reverse
volatile byte turnState = 0xAA; // 0x55 = Left 0xAA = No Turn, 0xFF = Right
volatile byte highState = 0x00; // 0x00 = off, 0xFF = on
volatile byte lightState = 0x00; // 0x00 = off, 0xFF = on
volatile byte wiperState = 0x00; //0x00 = off, 0xFF = on
volatile byte defrostState = 0x00; //0x00 = off, 0xFF = on
volatile byte hazardState = 0x00; //0x00 = off, 0xFF = on
volatile byte brakeState = 0x00; //0x00 = off, 0xFF = on
volatile bool blinkState = false; 

const int output1 = 17; //Driver tail Low
const int output2 = 16; //Reverse Light
const int output3 = 15; //Passenger Marker
const int output4 = 14; //Driver Tail High
const int output5 = 26; //Passenger Tail High
const int output6 = 25; //Passenger Tail Low
const int output7 = 6;  //License Plate
const int output8 = 5;  //Driver Marker

volatile bool out1 = false;
volatile bool out2 = false;
volatile bool out3 = false;
volatile bool out4 = false;
volatile bool out5 = false;
volatile bool out6 = false;
volatile bool out7 = false;
volatile bool out8 = false;



long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];                   


#define CAN0_INT 2      //set int pin to 2
MCP_CAN CAN0(SPI_CS_PIN);//set CS pin to 10


void setup ()
{
  Serial.begin(9600);
  while(!Serial);

  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
  {
    Serial.println("CAN Bus init successful");
  }
  else
  {
    Serial.println("error init can bus");
  }

  CAN0.setMode(MCP_NORMAL); 
  pinMode(CAN0_INT, INPUT);

  // Setup pins as Outputs
  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output6, OUTPUT);
  pinMode(output7, OUTPUT);
  pinMode(output8, OUTPUT);

  digitalWrite(output1, LOW);
  digitalWrite(output2, LOW);
  digitalWrite(output3, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output5, LOW);
  digitalWrite(output6, LOW);
  digitalWrite(output7, LOW);
  digitalWrite(output8, LOW);
}

void loop() {

  processCAN();

  handleStates();

}

void handleStates()
{
  /*
volatile byte shiftState = 0; // 0xAA: Drive, 0x55: Neutral, 0xFF: Reverse
volatile byte turnState = 0xAA; // 0x55 = Left 0xAA = No Turn, 0xFF = Right
volatile byte highState = 0x00; // 0x00 = off, 0xFF = on
volatile byte lightState = 0x00; // 0x00 = off, 0xFF = on
volatile byte wiperState = 0x00; //0x00 = off, 0xFF = on
volatile byte defrostState = 0x00; //0x00 = off, 0xFF = on
volatile byte hazardState = 0x00; //0x00 = off, 0xFF = on
volatile byte brakeState = 0x00; //0x00 = off, 0xFF = on
volatile bool blinkState = false; 

const int output1 = 17; //Driver tail Low
const int output3 = 15; //Passenger Marker
const int output4 = 14; //Driver Tail High
const int output5 = 26; //Passenger Tail High
const int output6 = 25; //Passenger Tail Low
const int output8 = 5;  //Driver Marker
*/
  //first, collect into variables so they're only written once
  if(shiftState == 0xFF)
    out2 = true;
  else
    out2 = false;

  if(lightState == 0xFF)
  {
    out7 = true;
    out3 = true;
    out8 = true;
    out1 = true;
    out6 = true;
  }
  else
  {
    out7 = false;
    out3 = false;
    out8 = false;
    out1 = false;
    out6 = false;
  }

  if(brakeState == 0xFF)
  {
    out4 = true;
    out5 = true;
  }
  else
  {
    out4 = false;
    out5 = false;
  }

  if(hazardState == 0xFF)
  {
    if(blinkState)
    {
      if(lightState == 0xFF)
      {
        out4 = true;
        out5 = true;
      }
      if(lightState == 0x00)
      {
        out6 = true;
        out1 = true;
      }
    }
    if(!blinkState)
    {
      if(lightState == 0xFF)
      {
        out4 = false;
        out5 = false;
      }
      if(lightState == 0x00)
      {
        out6 = false;
        out1 = false;
      }
    }
  }
  
  if(hazardState == 0x00 && brakeState == 0x00 && turnState == 0xAA)
  {
    out4 = false;
    out5 = false;
  }

  //second, write the outputs
  if(out1)
    digitalWrite(output1, HIGH);
  else
    digitalWrite(output1, LOW);
  
  if(out2)
    digitalWrite(output2, HIGH);
  else
    digitalWrite(output2, LOW);

  if(out3)
    digitalWrite(output3, HIGH);
  else
    digitalWrite(output3, LOW);

  if(out4)
    digitalWrite(output4, HIGH);
  else
    digitalWrite(output4, LOW);

  if(out5)
    digitalWrite(output5, HIGH);
  else
    digitalWrite(output5, LOW);

  if(out6)
    digitalWrite(output6, HIGH);
  else
    digitalWrite(output6, LOW);

  if(out7)
    digitalWrite(output7, HIGH);
  else
    digitalWrite(output7, LOW);

  if(out8)
    digitalWrite(output8, HIGH);
  else
    digitalWrite(output8, LOW);

}

void processCAN()
{
  if(!digitalRead(CAN0_INT))
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);

    if((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
      sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    else
      sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);

    if((rxId & 0x40000000) == 0x40000000){    // Determine if message is a remote request frame.
      sprintf(msgString, " REMOTE REQUEST FRAME");
      Serial.print(msgString);
    } 
    if((rxId & 0x1FFFFFFF) == 0x420201)
    {
      if(rxBuf[0] == 0x00) {      
        digitalWrite(output1, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output1, HIGH);
      }
    }
    if((rxId & 0x1FFFFFFF) == 0x420202)
    {
      if(rxBuf[0] == 0x00) {     
        digitalWrite(output2, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output2, HIGH);
      }
    }
    if((rxId & 0x1FFFFFFF) == 0x420203)
    {
      if(rxBuf[0] == 0x00) {      
        digitalWrite(output3, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output3, HIGH);
      }
    }
    if((rxId & 0x1FFFFFFF) == 0x420204)
    {
      if(rxBuf[0] == 0x00) {     
        digitalWrite(output4, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output4, HIGH);
      }
    }
    if((rxId & 0x1FFFFFFF) == 0x420205)
    {
      if(rxBuf[0] == 0x00) {     
        digitalWrite(output5, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output5, HIGH);
      }
    }
    if((rxId & 0x1FFFFFFF) == 0x420206)
    {
      if(rxBuf[0] == 0x00) {      
        digitalWrite(output6, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output6, HIGH);
      }
    }
    if((rxId & 0x1FFFFFFF) == 0x420207)
    {
      if(rxBuf[0] == 0x00) {      
        digitalWrite(output7, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output7, HIGH);
      }
    }
    if((rxId & 0x1FFFFFFF) == 0x420208)
    {
      if(rxBuf[0] == 0x00) {      
        digitalWrite(output8, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output8, HIGH);
      }
    }
    if ((rxId & 0x1FFFFFFF) == 0x420010) {
      // Check the state of the shift knob
      if (rxBuf[0] == 0xAA) { // 0xAA is Drive
        shiftState = 0xAA;
      }
      else if (rxBuf[0] == 0x55) {
        // 0x55 is Neutral
        shiftState = 0x55;
      } 
      else if (rxBuf[0] == 0xFF) {
        // 0xFF is Reverse
        shiftState = 0xFF;
      }
    }

    if ((rxId & 0x1FFFFFFF) == 0x420300) {
      // Check the state of the turn stalk
      if (rxBuf[0] == 0xAA) { // 0xAA is No Turn
        turnState = 0xAA;
      }
      else if (rxBuf[0] == 0x55) {
        // 0x55 is Left
        turnState = 0x55;
      } 
      else if (rxBuf[0] == 0xFF) {
        // 0xFF is Right
        turnState = 0xFF;
      }
    }

    if((rxId & 0x1FFFFFFF) == 0x420301) {  //state of the high beam
      if(rxBuf[0] == 0x00)
        highState = 0x00;
      else if(rxBuf[0] == 0xFF)
        highState = 0xFF;
    }

    if((rxId & 0x1FFFFFFF) == 0x420302) {  //state of the lights
      if(rxBuf[0] == 0x00)
        lightState = 0x00;
      else if(rxBuf[0] == 0xFF)
        lightState = 0xFF;
    }

    if((rxId & 0x1FFFFFFF) == 0x420303) {  //state of the wipers
      if(rxBuf[0] == 0x00)
        wiperState = 0x00;
      else if(rxBuf[0] == 0xFF)
        wiperState = 0xFF;
    }

    if((rxId & 0x1FFFFFFF) == 0x420304) {  //state of the wipers
      if(rxBuf[0] == 0x00)
        defrostState = 0x00;
      else if(rxBuf[0] == 0xFF)
        defrostState = 0xFF;
    }

    if((rxId & 0x1FFFFFFF) == 0x420305) {  //state of the hazard
      if(rxBuf[0] == 0x00)
        hazardState = 0x00;
      else if(rxBuf[0] == 0xFF)
        hazardState = 0xFF;
    }


    if((rxId & 0x1FFFFFFF) == 0x420306) {  //state of the brakes
      if(rxBuf[0] == 0x00)
        brakeState = 0x00;
      else if(rxBuf[0] == 0xFF)
        brakeState = 0xFF;
    }

    if((rxId & 0x1FFFFFFF) == 0x420312) {  //state of the blinker
      if(rxBuf[0] == 0x00)
        blinkState = false;
      else if(rxBuf[0] == 0xFF)
        blinkState = true;
    }
  }
}