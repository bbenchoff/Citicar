#include <mcp_can.h>
#include <mcp_can_dfs.h>

#include <mcp_can.h>
#include <avr/io.h>
#include <util/delay.h>
#include <SPI.h>


const int SPI_CS_PIN = 10;


const int output1 = 17; //Driver tail Low
const int output2 = 16; //Reverse Light
const int output3 = 15; //Passenger Marker
const int output4 = 14; //Driver Tail High
const int output5 = 26; //Passenger Tail High
const int output6 = 25; //Passenger Tail Low
const int output7 = 6;  //License Plate
const int output8 = 5;  //Driver Marker

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
    if((rxId & 0x1FFFFFFF) == 0x420011)
    {
      comutacar(); 
    }
  }

  //digitalWrite(output1, HIGH);  // turn the LED on (HIGH is the voltage level)
  //digitalWrite(output2, HIGH);  // turn the LED on (HIGH is the voltage level)
  //digitalWrite(output3, HIGH);  // turn the LED on (HIGH is the voltage level)
  //digitalWrite(output4, HIGH);  // turn the LED on (HIGH is the voltage level)
  //digitalWrite(output5, HIGH);  // turn the LED on (HIGH is the voltage level)
  //digitalWrite(output6, HIGH);  // turn the LED on (HIGH is the voltage level)
  //digitalWrite(output7, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(output8, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  //digitalWrite(output1, LOW);   // turn the LED off by making the voltage LOW
  //digitalWrite(output2, LOW);   // turn the LED off by making the voltage LOW
  //digitalWrite(output3, LOW);   // turn the LED off by making the voltage LOW
  //digitalWrite(output4, LOW);   // turn the LED off by making the voltage LOW
  //digitalWrite(output5, LOW);   // turn the LED off by making the voltage LOW
  //digitalWrite(output6, LOW);   // turn the LED off by making the voltage LOW
  //digitalWrite(output7, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(output8, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second

  
}