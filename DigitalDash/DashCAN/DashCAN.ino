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

bool lightstate;

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
byte shiftState = 0; // 0xAA: Drive, 0x55: Neutral, 0xFF: Reverse
byte turnState = 0xAA; // 0x55 = Left 0xAA = No Turn, 0xFF = Right
byte highState = 0x00; // 0x00 = off, 0xFF = on
byte lightState = 0x00; // 0x00 = off, 0xFF = on
byte wiperState = 0x00; //0x00 = off, 0xFF = on
byte defrostState = 0x00; //0x00 = off, 0xFF = on
byte hazardState = 0x00; //0x00 = off, 0xFF = on
byte brakeState = 0x00; //0x00 = off, 0xFF = on

byte CANon[1] = {0xFF};
byte CANoff[1] = {0x00};

// Create an instance of BlinkingLight for each blinker light
BlinkingLight RearDriverTailLow(0x420201);
BlinkingLight RearReverseLight(0x420202);
BlinkingLight RearPassengerMarker(0x420203);
BlinkingLight RearDriverTailHigh(0x420204);
BlinkingLight RearPassengerTailHigh(0x420205);
BlinkingLight RearPassengerTailLow(0x420206);
BlinkingLight RearLicense(0x420207);
BlinkingLight RearDriverMarker(0x420208);

BlinkingLight FrontPassengerMarker(0x420101);
BlinkingLight FrontPassengerHighBeam(0x420202);
BlinkingLight FrontPassengerLowBeam(0x420203);
BlinkingLight FrontPassengerTurnHigh(0x420204);
BlinkingLight FrontPassengerTurnLow(0x420205);
BlinkingLight FrontDriverMarker(0x420206);
BlinkingLight FrontDriverHighBeam(0x420207);
BlinkingLight FrontDriverLowBeam(0x420208);
BlinkingLight FrontDriverTurnHigh(0x420209);
BlinkingLight FrontDriverTurnLow(0x420210);


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
  delay(520);

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

  // Set up interrupts for the input pins
  attachInterrupt(digitalPinToInterrupt(input1), handleInput1, CHANGE); // Right Blink
  attachInterrupt(digitalPinToInterrupt(input2), handleInput2, CHANGE); // Left Blink
  attachInterrupt(digitalPinToInterrupt(input3), handleInput3, CHANGE); // High Beam
  attachInterrupt(digitalPinToInterrupt(input4), handleInput4, CHANGE); // Brake
  attachInterrupt(digitalPinToInterrupt(input5), handleInput5, CHANGE); // Light Switch
  attachInterrupt(digitalPinToInterrupt(input6), handleInput6, CHANGE); // Wiper Switch
  attachInterrupt(digitalPinToInterrupt(input7), handleInput7, CHANGE); // Defrost Switch
  attachInterrupt(digitalPinToInterrupt(input8), handleInput8, CHANGE); // Hazard Switch


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
      if ((rxId & 0x1FFFFFFF) == 0x420010) {
        // Check the state of the shift knob
        if (rxBuf[0] == 0xAA) { // 0xAA is Drive
          shiftState = 0xAA;
          sndStat = CAN0.sendMsgBuf(0x420202, 1, 1, CANoff);  //Reverse Light
          if(lightstate)
          {
            
            sndStat = CAN0.sendMsgBuf(0x420201, 1, 1, CANon);  //DriverTailLow Light
            sndStat = CAN0.sendMsgBuf(0x420206, 1, 1, CANon);  //PassengerTailLow Light
          }
          else
          {
            sndStat = CAN0.sendMsgBuf(0x420202, 1, 1, CANoff);  //Reverse Light
            sndStat = CAN0.sendMsgBuf(0x420201, 1, 1, CANoff);  //DriverTailLow Light
            sndStat = CAN0.sendMsgBuf(0x420206, 1, 1, CANoff);  //PassengerTailLow Light
          }
        } else if (rxBuf[0] == 0x55) {
          // 0x55 is Neutral
          shiftState = 0x55;
          if(lightstate)
          {
            sndStat = CAN0.sendMsgBuf(0x420201, 1, 1, CANon);  //DriverTailLow Light
            sndStat = CAN0.sendMsgBuf(0x420206, 1, 1, CANon);  //PassengerTailLow Light
          }
          else
          {
            sndStat = CAN0.sendMsgBuf(0x420202, 1, 1, CANoff);  //Reverse Light
            sndStat = CAN0.sendMsgBuf(0x420201, 1, 1, CANoff);  //DriverTailLow Light
            sndStat = CAN0.sendMsgBuf(0x420206, 1, 1, CANoff);  //PassengerTailLow Light
          }
        } else if (rxBuf[0] == 0xFF) {
          // 0xFF is Reverse
          shiftState = 0xFF;
          if(lightstate)
          {
            sndStat = CAN0.sendMsgBuf(0x420202, 1, 1, CANon);  //Reverse Light
          }
          sndStat = CAN0.sendMsgBuf(0x420201, 1, 1, CANon);  //DriverTailLow Light
          sndStat = CAN0.sendMsgBuf(0x420206, 1, 1, CANon);  //PassengerTailLow Light
        }
      }
    }


  if((digitalRead(input1)) == LOW) /// Right Blink
  {
    digitalWrite(output1, LOW);
  } else if((digitalRead(input1)) == HIGH)
  {
    digitalWrite(output1, HIGH);
  }

  if((digitalRead(input2)) == LOW)  ///Left Blink
  {
    digitalWrite(output2, LOW);
  } else if((digitalRead(input2)) == HIGH)
  {
    digitalWrite(output2, HIGH);
  }

  if((digitalRead(input3)) == LOW) ///High Beams
  {
    digitalWrite(output3, LOW);
    highState = 0x00;
  } else if((digitalRead(input3)) == HIGH)
  {
    digitalWrite(output3, HIGH);
    highState = 0xFF;
  }

  if((digitalRead(input4)) == LOW) ///Brake Switch
  {
    digitalWrite(output4, LOW);
  } else if((digitalRead(input4)) == HIGH)
  {
    digitalWrite(output4, HIGH);
  }
  
  if((digitalRead(input5)) == LOW) ///Lights
  {
    lightstate = false;
    if(shiftState == 0xFF)
    {
      sndStat = CAN0.sendMsgBuf(0x420202, 1, 1, CANoff);
    }
    digitalWrite(output5, LOW);
  } else if((digitalRead(input5)) == HIGH)
  {
    lightstate = true;
    if(shiftState == 0xFF)
    {
      sndStat = CAN0.sendMsgBuf(0x420202, 1, 1, CANon);
    }
    digitalWrite(output5, HIGH);
  }

  if((digitalRead(input6)) == LOW) ///Wiper
  {
    digitalWrite(output6, LOW);
  } else if((digitalRead(input6)) == HIGH)
  {
    digitalWrite(output6, HIGH);
  }

  if((digitalRead(input7)) == LOW) ///Defrost
  {
    digitalWrite(output7, LOW);
  } else if((digitalRead(input7)) == HIGH)
  {
    digitalWrite(output7, HIGH);
  }

  /*if((digitalRead(input8)) == LOW) ///Hazard Lights
  {
    digitalWrite(output8, LOW);
  } else if((digitalRead(input8)) == HIGH)
  {
    digitalWrite(output8, HIGH);
  }*/
}

// Timer1 compare match A interrupt handler
ISR(TIMER1_COMPA_vect) {
  //toggleLights();
}



// Interrupt service routines for each input pin
void handleInput1() {
    // Handle input1 change
    //Right Blink
    if(digitalRead(input1) == HIGH)
    {
      turnState = 0xFF;
    }
    else if(digitalRead(input2) == HIGH)
    {
      turnState = 0x55;
    }
    else
    {
      turnState = 0xAA;
    }

    digitalWrite(output1, digitalRead(input1));
}

void handleInput2() {
    // Handle input2 change
    // Left Blink
    if(digitalRead(input1) == HIGH)
    {
      turnState = 0xFF;
    }
    else if(digitalRead(input2) == HIGH)
    {
      turnState = 0x55;
    }
    else
    {
      turnState = 0xAA;
    }
    digitalWrite(output2, digitalRead(input2));
}

void handleInput3() {
    // Handle input3 change
    // High Beam
    if(digitalRead(input3) == HIGH)
    {
      highState = 0xFF;
    }
    else
    {
      highState = 0x00;
    }
    digitalWrite(output3, digitalRead(input3));
}

void handleInput4() {
    // Handle input4 change
    // Brake Switch
    if(digitalRead(input4) == HIGH)
    {
      brakeState = 0xFF;
    }
    else
    {
      brakeState = 0x00;
    }
    digitalWrite(output4, digitalRead(input4));
}

void handleInput5() {
    // Handle input5 change
    //Light switch
    if(digitalRead(input5) == HIGH)
    {
      lightState = 0xFF;
    }
    else
    {
      lightState = 0x00;
    }
    digitalWrite(output5, digitalRead(input5));
}

void handleInput6() {
    // Handle input6 change
    // Wiper Switch
    if(digitalRead(input6) == HIGH)
    {
      wiperState = 0xFF;
    }
    else
    {
      wiperState = 0x00;
    }
    digitalWrite(output6, digitalRead(input6));
}

void handleInput7() {
    // Handle input7 change
    // Defrost Switch
    if(digitalRead(input7) == HIGH)
    {
      defrostState = 0xFF;
    }
    else
    {
      defrostState = 0x00;
    }
    digitalWrite(output7, digitalRead(input7));
}

void handleInput8() {
    // Hazard Switch
    if(digitalRead(input8) == HIGH)
    {
      hazardState = 0xFF;
    }
    else
    {
      hazardState = 0x00;
    }
    digitalWrite(output8, digitalRead(input8));
}
