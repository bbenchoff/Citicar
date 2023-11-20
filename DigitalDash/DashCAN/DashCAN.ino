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
const int input1 = 4;
const int input2 = 3;
const int input3 = 0;
const int input4 = 19;
const int input5 = 18; 
const int input6 = 9; 
const int input7 = 8;
const int input8 = 7;  

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

  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
  pinMode(input3, INPUT);
  pinMode(input4, INPUT);
  pinMode(input5, INPUT);
  pinMode(input6, INPUT);
  pinMode(input7, INPUT);
  pinMode(input8, INPUT);
 

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

 if((digitalRead(input1)) == LOW)
 {
   digitalWrite(output1, HIGH);
 }
  if((digitalRead(input1)) == HIGH)
 {
   digitalWrite(output1, LOW);
 }

  if((digitalRead(input2)) == LOW)
 {
   digitalWrite(output2, HIGH);
 }
  if((digitalRead(input2)) == HIGH)
 {
   digitalWrite(output2, LOW);
 }

   if((digitalRead(input3)) == LOW)
 {
   digitalWrite(output3, HIGH);
 }
  if((digitalRead(input3)) == HIGH)
 {
   digitalWrite(output3, LOW);
 }

  if((digitalRead(input4)) == LOW)
 {
   digitalWrite(output4, HIGH);
 }
  if((digitalRead(input4)) == HIGH)
 {
   digitalWrite(output4, LOW);
 }
  
  if((digitalRead(input5)) == LOW)
 {
   digitalWrite(output5, LOW);
 }
  if((digitalRead(input5)) == HIGH)
 {
   digitalWrite(output5, HIGH);
 }

  if((digitalRead(input6)) == LOW)
 {
   digitalWrite(output6, LOW);
 }
  if((digitalRead(input6)) == HIGH)
 {
   digitalWrite(output6, HIGH);
 }

  if((digitalRead(input7)) == LOW)
 {
   digitalWrite(output7, LOW);
 }
  if((digitalRead(input7)) == HIGH)
 {
   digitalWrite(output7, HIGH);
 }

   if((digitalRead(input8)) == LOW)
 {
   digitalWrite(output8, LOW);
 }
  if((digitalRead(input8)) == HIGH)
 {
   digitalWrite(output8, HIGH);
 }

}