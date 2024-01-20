#include <mcp_can.h>
#include <mcp_can_dfs.h>

#include <mcp_can.h>
#include <avr/io.h>
#include <util/delay.h>
#include <SPI.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define CAN0_INT 2      //set int pin to 2

const int SPI_CS_PIN = 10;

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];

const int output1 = 17; // I might put a relay here for turn signal noise
const int output2 = 16; // This is empty but kept for debugging
const int output3 = 15; // This is empty but kept for debugging
const int output4 = 14; // This is empty but kept for debugging
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

byte sndStat;

volatile byte shiftState = 0; // 0xAA: Drive, 0x55: Neutral, 0xFF: Reverse
volatile byte turnState = 0xAA; // 0x55 = Left 0xAA = No Turn, 0xFF = Right
volatile byte highState = 0x00; // 0x00 = off, 0xFF = on
volatile byte lightState = 0x00; // 0x00 = off, 0xFF = on
volatile byte wiperState = 0x00; //0x00 = off, 0xFF = on
volatile byte defrostState = 0x00; //0x00 = off, 0xFF = on
volatile byte hazardState = 0x00; //0x00 = off, 0xFF = on
volatile byte brakeState = 0x00; //0x00 = off, 0xFF = on
volatile bool blinkState = false; 

byte CANon[1] = {0xFF};
byte CANoff[1] = {0x00};
byte leftTurn[1] = {0x55};
byte noTurn[1] = {0xAA};
byte rightTurn[1] = {0xFF};

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

  // Configure Timer1 to generate an interrupt every 750ms
  cli(); // Disable interrupts

  // Set Timer1 to CTC (Clear Timer on Compare Match) mode
  // This shoud be around 90Hz; the target for blinking is
  // 60-120 flashes per minute, or 0.75Hz. This value comes
  // from 67 Pa. Code § 175.66 - Lighting and electrical systems,
  // "(4) The turn signals shall have a frequency of flash
  // between 60-120 flashes per minute."
  //
  // This must be divided by two because _I believe_ the reg
  // is interpreted that way. Whatever.
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0; // Initialize counter value
  OCR1A = 20832; // Set the compare match value for 0.75Hz (16MHz / 1024 / 0.75Hz - 1)
  TCCR1B |= (1 << WGM12); // Enable CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024
  TIMSK1 |= (1 << OCIE1A); // Enable Timer1 compare match A interrupt

  sei(); // Enable interrupts

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
  //setup optos as inputs
  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
  pinMode(input3, INPUT);
  pinMode(input4, INPUT);
  pinMode(input5, INPUT);
  pinMode(input6, INPUT);
  pinMode(input7, INPUT);
  pinMode(input8, INPUT);
  
  //Write all outputs Low
  digitalWrite(output1, LOW);
  digitalWrite(output2, LOW);
  digitalWrite(output3, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output5, LOW);
  digitalWrite(output6, LOW);
  digitalWrite(output7, LOW);
  digitalWrite(output8, LOW);

  //half second-ish delay for reasons
  delay(420);

  //Turn off all lights.
  sndStat = CAN0.sendMsgBuf(0x420101, 1, 1, CANoff);  //Front passenger marker
  sndStat = CAN0.sendMsgBuf(0x420102, 1, 1, CANoff);  //Front passenger High beam
  sndStat = CAN0.sendMsgBuf(0x420103, 1, 1, CANoff);  //Front passenger low beam
  sndStat = CAN0.sendMsgBuf(0x420104, 1, 1, CANoff);  //Front passenger turn high
  sndStat = CAN0.sendMsgBuf(0x420105, 1, 1, CANoff);  //Front passenger turn low
  sndStat = CAN0.sendMsgBuf(0x420106, 1, 1, CANoff);  //Front Driver marker
  sndStat = CAN0.sendMsgBuf(0x420107, 1, 1, CANoff);  //Front Driver High beam
  sndStat = CAN0.sendMsgBuf(0x420108, 1, 1, CANoff);  //Front Driver Low Beam
  sndStat = CAN0.sendMsgBuf(0x420109, 1, 1, CANoff);  //Front Driver Turn High
  sndStat = CAN0.sendMsgBuf(0x420110, 1, 1, CANoff);  //Front Driver Turn Low

  sndStat = CAN0.sendMsgBuf(0x420201, 1, 1, CANoff);  //Rear Driver Tail Low
  sndStat = CAN0.sendMsgBuf(0x420202, 1, 1, CANoff);  //Reverse Light
  sndStat = CAN0.sendMsgBuf(0x420203, 1, 1, CANoff);  //Rear passenger marker
  sndStat = CAN0.sendMsgBuf(0x420204, 1, 1, CANoff);  //Rear Driver Tail High
  sndStat = CAN0.sendMsgBuf(0x420205, 1, 1, CANoff);  //Rear Passenger Tail High
  sndStat = CAN0.sendMsgBuf(0x420206, 1, 1, CANoff);  //Rear Passenger Tail Low
  sndStat = CAN0.sendMsgBuf(0x420207, 1, 1, CANoff);  //Rear License
  sndStat = CAN0.sendMsgBuf(0x420208, 1, 1, CANoff);  //Rear Driver marker
}

void loop() 
{
  /*
  * No you can't put the CAN interrupt in an ISR because dumb shit happens
  */
  if(!digitalRead(CAN0_INT))
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);

    if((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
      //sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    //else
      //sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);

    if((rxId & 0x40000000) == 0x40000000){    // Determine if message is a remote request frame.
      //sprintf(msgString, " REMOTE REQUEST FRAME");
      //Serial.print(msgString);
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
  }

  // Now, handle the position of the turn stalk
  // and the dashboard buttons. This is broken 
  // out into its own function for clarity.
  handleSwitches();

  /*
  * Now, state machine shit
  */
  updateLightsState();

}

// Timer1 compare match A interrupt handler
ISR(TIMER1_COMPA_vect) {
  blinkState = !blinkState;

  if(blinkState)
  {
    CAN0.sendMsgBuf(0x420312, 1, 1, CANon);  //Blink State
  }
  if(!blinkState)
  {
    CAN0.sendMsgBuf(0x420312, 1, 1, CANoff);  //Blink State
  }
}

void updateLightsState() {

  if(turnState == 0xAA)
  {
    CAN0.sendMsgBuf(0x420300, 1, 1, noTurn);  //No turn
  }
  if(turnState == 0x55)
  {
    CAN0.sendMsgBuf(0x420300, 1, 1, leftTurn);
  }
  if(turnState == 0xFF)
  {
     CAN0.sendMsgBuf(0x420300, 1, 1, rightTurn);
  }

  if(highState == 0xFF)
    CAN0.sendMsgBuf(0x420301, 1, 1, CANon);
  if(highState == 0x00)
    CAN0.sendMsgBuf(0x420301, 1, 1, CANoff);

  if(lightState == 0xFF)
    CAN0.sendMsgBuf(0x420302, 1, 1, CANon);
  if(lightState == 0x00)
    CAN0.sendMsgBuf(0x420302, 1, 1, CANoff);

  if(defrostState == 0xFF)
    CAN0.sendMsgBuf(0x420304, 1, 1, CANon);
  if(defrostState == 0x00)
    CAN0.sendMsgBuf(0x420304, 1, 1, CANoff);

  if(wiperState == 0xFF)
    CAN0.sendMsgBuf(0x420303, 1, 1, CANon);
  if(wiperState == 0x00)
    CAN0.sendMsgBuf(0x420303, 1, 1, CANoff);

  if(hazardState == 0xFF)
    CAN0.sendMsgBuf(0x420305, 1, 1, CANon);
  if(hazardState == 0x00)
    CAN0.sendMsgBuf(0x420305, 1, 1, CANoff);

  if(brakeState == 0xFF)
    CAN0.sendMsgBuf(0x420306, 1, 1, CANon);
  if(brakeState == 0x00)
    CAN0.sendMsgBuf(0x420306, 1, 1, CANoff);

}

void handleSwitches(void)
{
  /*
  * This function handles the global variables responsible for
  * going into new states of the state machine. 
  */

  //Handle the blink stuff / variable turnState
  //// 0x55 = Left 0xAA = No Turn, 0xFF = Right
  // Right blink = input1, left blink = input2
  if(digitalRead(input1) == LOW)
  {
    digitalWrite(output1, LOW);
    digitalWrite(output2, HIGH);
    turnState = 0xFF;
  }
  if(digitalRead(input2) == LOW)
  {
    digitalWrite(output2, LOW);
    digitalWrite(output1, HIGH);
    turnState = 0x55;
  }
  if((digitalRead(input1) == HIGH) && (digitalRead(input2) == HIGH))
  {
    digitalWrite(output1, HIGH);
    digitalWrite(output2, HIGH);
    turnState = 0xAA;
  }

  if(digitalRead(input3) == HIGH)
  {
    digitalWrite(output3, HIGH);
    highState = 0x00;
  }
  else
  {
    digitalWrite(output3, LOW);
    highState = 0xFF;
  }

  if(digitalRead(input4) == HIGH)
  {
    digitalWrite(output4, HIGH);
    brakeState = 0x00;
  }
  else
  {
    digitalWrite(output4, LOW);
    brakeState = 0xFF;
  }

  if(digitalRead(input5) == HIGH)
  {
    digitalWrite(output5, HIGH);
    lightState = 0xFF;
  }
  else
  {
    digitalWrite(output5, LOW);
    lightState = 0x00;
  }

  if(digitalRead(input6) == HIGH)
  {
    digitalWrite(output6, HIGH);
    wiperState = 0xFF;
  }
  else
  {
    digitalWrite(output6, LOW);
    wiperState = 0x00;
  }

  if(digitalRead(input7) == HIGH)
  {
    digitalWrite(output7, HIGH);
    defrostState = 0xFF;
  }
  else
  {
    digitalWrite(output7, LOW);
    defrostState = 0x00;
  }

  if(digitalRead(input8) == HIGH)
  {
    digitalWrite(output8, HIGH);
    hazardState = 0xFF;
  }
  else
  {
    digitalWrite(output8, LOW);
    hazardState = 0x00;
  }
}