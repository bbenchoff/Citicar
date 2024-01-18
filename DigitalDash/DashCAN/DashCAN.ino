#include <mcp_can.h>
#include <mcp_can_dfs.h>

#include <mcp_can.h>
#include <avr/io.h>
#include <util/delay.h>
#include <SPI.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "BlinkingLight.h"

#define CAN0_INT 2      //set int pin to 2

const int SPI_CS_PIN = 10;

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];

byte lfsrArray[20];
unsigned long lfsr = 0xACE1u;
unsigned long lfsrTap = 0x000B;

const int output1 = 17; // I might put a relay here for turn signal noise
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

// Create an instance of BlinkingLight for each blinker light
// and CAN status update
BlinkingLight RearDriverTailLow(0x420201);
BlinkingLight RearReverseLight(0x420202);
BlinkingLight RearPassengerMarker(0x420203);
BlinkingLight RearDriverTailHigh(0x420204);
BlinkingLight RearPassengerTailHigh(0x420205);
BlinkingLight RearPassengerTailLow(0x420206);
BlinkingLight RearLicense(0x420207);
BlinkingLight RearDriverMarker(0x420208);

BlinkingLight FrontPassengerMarker(0x420101);
BlinkingLight FrontPassengerHighBeam(0x420102);
BlinkingLight FrontPassengerLowBeam(0x420103);
BlinkingLight FrontPassengerTurnHigh(0x420104);
BlinkingLight FrontPassengerTurnLow(0x420105);
BlinkingLight FrontDriverMarker(0x420106);
BlinkingLight FrontDriverHighBeam(0x420107);
BlinkingLight FrontDriverLowBeam(0x420108);
BlinkingLight FrontDriverTurnHigh(0x420109);
BlinkingLight FrontDriverTurnLow(0x420110);

BlinkingLight HighBeamState(0x420301);
BlinkingLight LightState(0x420302);
BlinkingLight WiperState(0x420303);
BlinkingLight DefrostState(0x420304);
BlinkingLight HazardState(0x420305);
BlinkingLight BrakeState(0x420306);

BlinkingLight RightTurnState(0x420310);
BlinkingLight LeftTurnState(0x420311);

enum StateLights { LIGHTS_OFF, LIGHTS_LOW, LIGHTS_HIGH };
enum StateBrake { BRAKE_OFF, BRAKE_ON};
enum StateTurn { TURN_OFF, TURN_LEFT, TURN_RIGHT};

volatile StateLights stateLights = LIGHTS_OFF;
volatile StateBrake stateBrakes = BRAKE_OFF;
volatile StateTurn stateTrun = TURN_OFF;

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

  // Configure Timer1 to generate an interrupt every 500 ms
  cli(); // Disable interrupts

  // Set Timer1 to CTC (Clear Timer on Compare Match) mode
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0; // Initialize counter value
  OCR1A = 15624; // Set the compare match value (16MHz / 1024 / 2Hz - 1)
  TCCR1B |= (1 << WGM12); // Enable CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024
  TIMSK1 |= (1 << OCIE1A); // Enable Timer1 compare match A interrupt

  sei(); // Enable interrupts

  CAN0.setMode(MCP_NORMAL); 
  pinMode(CAN0_INT, INPUT);

  memset(lfsrArray, 0, sizeof(lfsrArray));

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
  // Update LFSR
  unsigned long newLfsrValue = lfsrIncrement();

  // Update the boolean array based on the LFSR value
  for (int i = 0; i < sizeof(lfsrArray); ++i) {
    lfsrArray[i] = newLfsrValue & (1 << i);
  }

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
  //This was here for testing
  if(shiftState == 0xFF)
    sndStat = CAN0.sendMsgBuf(0x420102, 1, 1, CANon);
  else
    sndStat = CAN0.sendMsgBuf(0x420102, 1, 1, CANoff); 
  */
  /*
  sndStat = CAN0.sendMsgBuf(0x420201, 1, 1, CANon);
  sndStat = CAN0.sendMsgBuf(0x420202, 1, 1, CANon);
  sndStat = CAN0.sendMsgBuf(0x420203, 1, 1, CANon);
  sndStat = CAN0.sendMsgBuf(0x420204, 1, 1, CANon);
  sndStat = CAN0.sendMsgBuf(0x420205, 1, 1, CANon);
  sndStat = CAN0.sendMsgBuf(0x420206, 1, 1, CANon);
  sndStat = CAN0.sendMsgBuf(0x420207, 1, 1, CANon);
  sndStat = CAN0.sendMsgBuf(0x420208, 1, 1, CANon);
*/
  /*
  * Now, state machine shit
  */
  updateLightsState();

}

// Timer1 compare match A interrupt handler
ISR(TIMER1_COMPA_vect) {
  blinkState = !blinkState;
}

void updateLightsState() {
    switch(stateLights) {
        case LIGHTS_OFF:
            //turn off all the lights
            if (lightState == 0xFF) {
                stateLights = LIGHTS_LOW; // Switch to LOW if light switch is on
            }
            FrontPassengerHighBeam.turnOff(CAN0);
            FrontDriverHighBeam.turnOff(CAN0);
            FrontPassengerLowBeam.turnOff(CAN0);
            FrontDriverLowBeam.turnOff(CAN0);
            FrontPassengerMarker.turnOff(CAN0);
            FrontPassengerTurnLow.turnOff(CAN0);
            FrontDriverMarker.turnOff(CAN0);
            FrontDriverTurnLow.turnOff(CAN0);
            RearDriverTailLow.turnOff(CAN0);
            RearPassengerMarker.turnOff(CAN0);
            RearDriverTailLow.turnOff(CAN0);
            RearPassengerTailLow.turnOff(CAN0);
            RearDriverMarker.turnOff(CAN0);
            RearLicense.turnOff(CAN0);
            break;

        case LIGHTS_LOW:
            if (highState == 0xFF) {
                stateLights = LIGHTS_HIGH; // Switch to HIGH if high beam switch is on
            } else if (lightState == 0x00) {
                stateLights = LIGHTS_OFF; // Switch to OFF if light switch is off
            }
            FrontDriverHighBeam.turnOff(CAN0);
            FrontPassengerHighBeam.turnOff(CAN0);
            FrontPassengerLowBeam.turnOn(CAN0);
            FrontDriverLowBeam.turnOn(CAN0);
            FrontPassengerMarker.turnOn(CAN0);
            FrontPassengerTurnLow.turnOn(CAN0);
            FrontDriverMarker.turnOn(CAN0);
            FrontDriverTurnLow.turnOn(CAN0);
            RearDriverTailLow.turnOn(CAN0);
            RearDriverTailLow.turnOn(CAN0);
            RearDriverMarker.turnOn(CAN0);
            RearPassengerTailLow.turnOn(CAN0);
            RearLicense.turnOn(CAN0);
            RearPassengerMarker.turnOn(CAN0);
            break;

        case LIGHTS_HIGH:
            if (highState == 0x00) {
                stateLights = LIGHTS_LOW; // Switch to LOW if high beam switch is off
            }
            else if (lightState == 0x00) {
                stateLights = LIGHTS_OFF; // Switch to OFF if light switch is off
            }
            FrontDriverHighBeam.turnOn(CAN0);
            FrontPassengerHighBeam.turnOn(CAN0);
            FrontPassengerLowBeam.turnOff(CAN0);
            FrontDriverLowBeam.turnOff(CAN0);
            FrontPassengerMarker.turnOn(CAN0);
            FrontPassengerTurnLow.turnOn(CAN0);
            FrontDriverMarker.turnOn(CAN0);
            FrontDriverTurnLow.turnOn(CAN0);
            RearDriverTailLow.turnOn(CAN0);
            RearPassengerMarker.turnOn(CAN0);
            RearDriverTailLow.turnOn(CAN0);
            RearDriverMarker.turnOn(CAN0);
            RearPassengerTailLow.turnOn(CAN0);
            RearLicense.turnOn(CAN0);
            break;
    }
}

unsigned long lfsrIncrement() {
  // Shift the LFSR and calculate the new bit
  unsigned long lsb = lfsr & 1; // Get LSB (bit 0)
  lfsr >>= 1; // Shift register
  if (lsb == 1) {
    lfsr ^= lfsrTap; // Apply the tap if LSB was 1
  }
  return lfsr;
}

void handleSwitches(void)
{
  /*
  * This function handles the global variables responsible for
  * going into new states of the state machine. 
  */


  /*This was here for testing
  //if(shiftState == 0xFF)
  //  sndStat = CAN0.sendMsgBuf(0x420202, 1, 1, CANon);
  //else
  //  sndStat = CAN0.sendMsgBuf(0x420202, 1, 1, CANoff); */

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