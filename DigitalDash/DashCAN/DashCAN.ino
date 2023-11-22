#include <mcp_can.h>
#include <mcp_can_dfs.h>

#include <mcp_can.h>
#include <avr/io.h>
#include <util/delay.h>
#include <SPI.h>

#define CAN0_INT 2      //set int pin to 2

const int SPI_CS_PIN = 10;

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];                   


const int output1 = 17;
const int output2 = 16;
const int output3 = 15;
const int output4 = 14;
const int output5 = 26; // Light Switch MOS
const int output6 = 25; // Wiper Switch MOS
const int output7 = 6; // Defrost Switch MOS
const int output8 = 5; // Hazard Switch MOS
const int input1 = 4; // Right Blink
const int input2 = 3; // Left Blink
const int input3 = 0; // High Beam
const int input4 = 19; // Brake
const int input5 = 18; // Light Switch
const int input6 = 9; // Wiper Switch
const int input7 = 8; // Defrost Switch
const int input8 = 7;  // Hazard Switch
                



MCP_CAN CAN0(SPI_CS_PIN);//set CS pin to 10

byte drive[1] = {0xAA};
byte neutral[1] = {0x55};
byte reverse[1] = {0xFF};


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

  byte sndStat;

  digitalWrite(output1, HIGH);
  sndStat = CAN0.sendMsgBuf(0x420010, 1, 1, drive);
  sndStat = CAN0.sendMsgBuf(0x420201, 1, 1, (byte*)"\xFF");
  sndStat = CAN0.sendMsgBuf(0x420202, 1, 1, (byte*)"\xFF");
  sndStat = CAN0.sendMsgBuf(0x420203, 1, 1, (byte*)"\xFF");
  sndStat = CAN0.sendMsgBuf(0x420204, 1, 1, (byte*)"\xFF");
  sndStat = CAN0.sendMsgBuf(0x420205, 1, 1, (byte*)"\xFF");
  sndStat = CAN0.sendMsgBuf(0x420206, 1, 1, (byte*)"\xFF");
  sndStat = CAN0.sendMsgBuf(0x420207, 1, 1, (byte*)"\xFF");
  sndStat = CAN0.sendMsgBuf(0x420101, 1, 1, (byte*)"\xFF");
  sndStat = CAN0.sendMsgBuf(0x420102, 1, 1, (byte*)"\xFF");
  sndStat = CAN0.sendMsgBuf(0x420103, 1, 1, (byte*)"\xFF");
  sndStat = CAN0.sendMsgBuf(0x420104, 1, 1, (byte*)"\xFF");
  sndStat = CAN0.sendMsgBuf(0x420105, 1, 1, (byte*)"\xFF");
  sndStat = CAN0.sendMsgBuf(0x420106, 1, 1, (byte*)"\xFF");
  sndStat = CAN0.sendMsgBuf(0x420107, 1, 1, (byte*)"\xFF");
  sndStat = CAN0.sendMsgBuf(0x420108, 1, 1, (byte*)"\xFF");
  sndStat = CAN0.sendMsgBuf(0x420109, 1, 1, (byte*)"\xFF");
  sndStat = CAN0.sendMsgBuf(0x420110, 1, 1, (byte*)"\xFF");
  delay(1000);
  digitalWrite(output1, LOW);
  sndStat = CAN0.sendMsgBuf(0x420010, 1, 1, neutral);
  sndStat = CAN0.sendMsgBuf(0x420201, 1, 1, (byte*)"\x00");
  sndStat = CAN0.sendMsgBuf(0x420202, 1, 1, (byte*)"\x00");
  sndStat = CAN0.sendMsgBuf(0x420203, 1, 1, (byte*)"\x00");
  sndStat = CAN0.sendMsgBuf(0x420204, 1, 1, (byte*)"\x00");
  sndStat = CAN0.sendMsgBuf(0x420205, 1, 1, (byte*)"\x00");
  sndStat = CAN0.sendMsgBuf(0x420206, 1, 1, (byte*)"\x00");
  sndStat = CAN0.sendMsgBuf(0x420207, 1, 1, (byte*)"\x00");
  sndStat = CAN0.sendMsgBuf(0x420101, 1, 1, (byte*)"\x00");
  sndStat = CAN0.sendMsgBuf(0x420102, 1, 1, (byte*)"\x00");
  sndStat = CAN0.sendMsgBuf(0x420103, 1, 1, (byte*)"\x00");
  sndStat = CAN0.sendMsgBuf(0x420104, 1, 1, (byte*)"\x00");
  sndStat = CAN0.sendMsgBuf(0x420105, 1, 1, (byte*)"\x00");
  sndStat = CAN0.sendMsgBuf(0x420106, 1, 1, (byte*)"\x00");
  sndStat = CAN0.sendMsgBuf(0x420107, 1, 1, (byte*)"\x00");
  sndStat = CAN0.sendMsgBuf(0x420108, 1, 1, (byte*)"\x00");
  sndStat = CAN0.sendMsgBuf(0x420109, 1, 1, (byte*)"\x00");
  sndStat = CAN0.sendMsgBuf(0x420110, 1, 1, (byte*)"\x00");
  delay(1000);

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