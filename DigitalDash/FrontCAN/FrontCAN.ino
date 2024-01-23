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

const int output1 = 17; //Front Passenger Marker
const int output2 = 16; //Passenger High Beam
const int output3 = 15; //Passenger Low Beam
const int output4 = 14; //Passenger Turn High
const int output5 = 26; //Passenger Turn Low
const int output6 = 25; //Driver Marker
const int output7 = 6;  //Driver High Beam
const int output8 = 5;  //Driver Low Beam
const int output9 = 4;  //Driver Turn High
const int output10 = 3; //Driver Turn Low

volatile bool out1 = false; //Pass Marker
volatile bool out2 = false; //Pass High Beam
volatile bool out3 = false; //Pass Low Beam
volatile bool out4 = false; //Pass Turn High
volatile bool out5 = false; //Pass Turn Low
volatile bool out6 = false; //Driver Marker
volatile bool out7 = false; //Driver High Beam
volatile bool out8 = false; //Driver Low Beam
volatile bool out9 = false; //Driver Turn High
volatile bool out10 = false; //Driver Turn Low

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
    pinMode(output1, OUTPUT);
    digitalWrite(output1, HIGH);
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
  pinMode(output9, OUTPUT);
  pinMode(output10, OUTPUT);

  digitalWrite(output1, LOW);
  digitalWrite(output2, LOW);
  digitalWrite(output3, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output5, LOW);
  digitalWrite(output6, LOW);
  digitalWrite(output7, LOW);
  digitalWrite(output8, LOW);
  digitalWrite(output9, LOW);
  digitalWrite(output10, LOW);



}

void loop() {

  processCAN();

  handleStates();
}

void handleStates()
{
  //first collect everything

  if(lightState == 0xFF) //the lights
  {
    if(highState == 0xFF)
    {
      out3 = false;
      out8 = false;
      out2 = true;
      out7 = true;
    }
    if(highState == 0x00)
    {
      out3 = true;
      out8 = true;
      out2 = false;
      out7 = false;
    }
    out1 = true;
    out6 = true;
    out5 = true;
    out10 = true;
  }
  else if(lightState == 0x00)
  {
    out2 = false;
    out3 = false;
    out7 = false;
    out8 = false;
    out1 = false;
    out6 = false;
    out5 = false;
    out10 = false;
  }

  //do the turn signals here
  if(turnState == 0x55)
  { //left turn
    if(blinkState)
    {
      out9 = true;
    }
    if(!blinkState)
    {
      out9 = false;
    }
  }

  if(turnState == 0xFF)
  { //right turn
    if(blinkState)
    {
      out4 = true;
    }
    if(!blinkState)
    {
      out4 = false;
    }
  }

  if(hazardState == 0xFF)
  {
    if(blinkState)
    {
      out4 = true;
      out9 = true;
      out6 = true;
    }
    if(!blinkState)
    {
      out4 = false;
      out9 = false;
      out6 = false;
    }
  }
  if((hazardState == 0x00) && (turnState == 0xAA))
  {
    out4 = false;
    out9 = false;
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

  if(out9)
    digitalWrite(output9, HIGH);
  else
    digitalWrite(output9, LOW);

  if(out10)
    digitalWrite(output10, HIGH);
  else
    digitalWrite(output10, LOW);
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
    if((rxId & 0x1FFFFFFF) == 0x420101)
    {
      if(rxBuf[0] == 0x00) {      // Check the first byte of the received message
        digitalWrite(output1, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output1, HIGH);
      }
    }
    if((rxId & 0x1FFFFFFF) == 0x420102)
    {
      if(rxBuf[0] == 0x00) {      // Check the first byte of the received message
        digitalWrite(output2, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output2, HIGH);
      }
    }
    if((rxId & 0x1FFFFFFF) == 0x420103)
    {
      if(rxBuf[0] == 0x00) {      // Check the first byte of the received message
        digitalWrite(output3, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output3, HIGH);
      }
    }
    if((rxId & 0x1FFFFFFF) == 0x420104)
    {
      if(rxBuf[0] == 0x00) {      // Check the first byte of the received message
        digitalWrite(output4, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output4, HIGH);
      }
    }
    if((rxId & 0x1FFFFFFF) == 0x420105)
    {
      if(rxBuf[0] == 0x00) {      // Check the first byte of the received message
        digitalWrite(output5, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output5, HIGH);
      }
    }
    if((rxId & 0x1FFFFFFF) == 0x420106)
    {
      if(rxBuf[0] == 0x00) {      // Check the first byte of the received message
        digitalWrite(output6, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output6, HIGH);
      }
    }
    if((rxId & 0x1FFFFFFF) == 0x420107)
    {
      if(rxBuf[0] == 0x00) {      // Check the first byte of the received message
        digitalWrite(output7, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output7, HIGH);
      }
    }
    if((rxId & 0x1FFFFFFF) == 0x420108)
    {
      if(rxBuf[0] == 0x00) {      // Check the first byte of the received message
        digitalWrite(output8, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output8, HIGH);
      }
    }
    if((rxId & 0x1FFFFFFF) == 0x420109)
    {
      if(rxBuf[0] == 0x00) {      // Check the first byte of the received message
        digitalWrite(output9, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output9, HIGH);
      }
    }
    if((rxId & 0x1FFFFFFF) == 0x420110)
    {
      if(rxBuf[0] == 0x00) {      // Check the first byte of the received message
        digitalWrite(output10, LOW);
      }
      else if(rxBuf[0] == 0xFF) {
        digitalWrite(output10, HIGH);
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