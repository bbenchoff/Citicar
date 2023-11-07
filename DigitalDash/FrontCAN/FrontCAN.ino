#include <mcp_can.h>
#include <mcp_can_dfs.h>

#include <mcp_can.h>
#include <avr/io.h>
#include <util/delay.h>
#include <SPI.h>


const int SPI_CS_PIN = 10;


const int output1 = 17;
const int output2 = 16;
const int output3 = 15;
const int output4 = 14;
const int output5 = 26;
const int output6 = 25;
const int output7 = 6;
const int output8 = 5;
const int output9 = 4;
const int output10 = 3;

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
  }
}