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
const int output11 = 0;
const int output12 = 19; 

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
  pinMode(output11, OUTPUT);
  pinMode(output12, OUTPUT);

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
  digitalWrite(output11, LOW);
  digitalWrite(output12, LOW);
}

void loop() {

  digitalWrite(output1, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(output2, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(output3, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(output4, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(output5, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(output6, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(output7, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(output8, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(output9, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(output10, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(output11, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(output12, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(output1, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(output2, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(output3, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(output4, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(output5, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(output6, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(output7, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(output8, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(output9, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(output10, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(output11, LOW);   // turn the LED off by making the voltage LOW
  digitalWrite(output12, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second

  
}