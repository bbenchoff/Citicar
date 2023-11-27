#include <mcp_can.h>
#include <mcp_can_dfs.h>

#include <mcp_can.h>
#include <avr/io.h>
#include <util/delay.h>
#include <SPI.h>

void writeChar(char letter);
void driveState(void);
void neutralState(void);
void reverseState(void);

const int SPI_CS_PIN = 10;
const int latchPin = 6;
const int clockPin = 7;
const int dataPin = 5;

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];                   

byte drive[1] = {0xAA};
byte neutral[1] = {0x55};
byte reverse[1] = {0xFF};


const int drivePin = 16;
const int neutralPin = 15;
const int reversePin = 14;

#define CAN0_INT 2      //set int pin to 2
MCP_CAN CAN0(SPI_CS_PIN);//set CS pin to 10

uint16_t character[128] = {
    0b1111111111111110, //00 NUL
    0b1011111111111111, //01  SOH
    0b1110111111111111, //02  STX
    0b1111110111111111, //03  ETX
    0b1111111011111111, //04  EOT
    0b0111111111111111, //05  ENQ
    0b1111111101111111, //06  ACK
    0b1111111111110111, //07  BEL
    0b1111111111111011, //08  BS
    0b1111111111111101, //09  HT
    0b1101111111111111, //10  LF
    0b1111011111111111, //11  VT
    0b1111101111111111, //12  FF
    0b1111111111011111, //13  CR
    0b1111111110111111, //14  SO
    0b1111111111101111, //15  SI
    0b1111111111111111, //16  DLE
    0b1111111111111111, //17  DC1
    0b1111111111111111, //18  DC2
    0b1111111111111111, //19  DC3
    0b1111111111111111, //20  DC4
    0b1111111111111111, //21  NAK
    0b1111111111111111, //22  SYN
    0b1111111111111111, //23  ETB
    0b1111111111111111, //24  CAN
    0b1111111111111111, //25  EM
    0b1111111111111111, //26  SUB
    0b1111111111111111, //27  ESC
    0b1111111111111111, //28  FS
    0b1111111111111111, //29 GS
    0b1111111111111111, //30  RS
    0b1111111111111111, //31  US
    0b1111111111111111, //32 space
    0b1111111111111111, //33  !
    0b1111111111111111, //34  "
    0b1111111111111111, //35  #
    0b1111111111111111, //36  $
    0b1111111111111111, //37  %
    0b1111111111111111, //38  &
    0b1111111111111111, //39 '
    0b1111111111111111, //40  (
    0b1111111111111111, //41  )
    0b1111111111111111, //42  *
    0b1111111111111111, //43  +
    0b1111111111111111, //44  ,
    0b1111111111111111, //45  -
    0b1111111111111111, //46  .
    0b1111111111111111, //47  /
    0b0010110001110110, //48  0
    0b1111111111011101, //49  1
    0b0010011001101110, //50  2
    0b0010010011111110, //51  3
    0b1110010111100111, //52  4
    0b0011010011100110, //53  5
    0b0011010001100110, //54  6
    0b1010110111111110, //55  7
    0b0010010001100110, //56  8
    0b0010010011100110, //57  9
    0b1111111111111111, //58  :
    0b1111111111111111, //59  ;
    0b1111111111111111, //60  <
    0b1111111111111111, //61  =
    0b1111111111111111, //62  >
    0b1111111111111111, //63  ?
    0b1111111111111111, //64  @
    0b1010010101100110, //65  A
    0b0010010011011100, //66  B
    0b0011111001110110, //67  C
    0b0010110011011100, //68  D
    0b0011011001100110, //69  E
    0b1011011101100110, //70  F
    0b0011010001110110, //71  G
    0b1110010101100111, //72  H
    0b0011111011011100, //73  I
    0b0110110001111111, //74  J
    0b1101101101100111, //75  K
    0b0111111001110111, //76  L
    0b1100110101110011, //77  M
    0b1110100101110011, //78  N
    0b0010110001110110, //79  O
    0b1010011101100110, //80  P
    0b0010100001110110, //81  Q
    0b1010001101100110, //82  R
    0b0011000011100010, //83  S
    0b1011111111011100, //84  T
    0b0110110001110111, //85  U
    0b1101111100110111, //86  V
    0b1110100100110111, //87  W
    0b1101101110111011, //88  X
    0b1101111111011011, //89  Y
    0b0001111010111110, //90  Z
    0b1111111111111111, //91  [
    0b1111111111111111, //92  bs
    0b1111111111111111, //93  ]
    0b1111111111111111, //94  ^
    0b1111111111111111, //95  _
    0b1111111111111111, //96  `
    0b0111111001001111, //97  a
    0b0111111101000111, //98  b
    0b0111111101101111, //99  c
    0b0111111101001101, //100 d
    0b0111111100101111, //101 e
    0b1011011111001101, //102 f
    0b0111111111000100, //103 g
    0b1111111101000111, //104 h
    0b1111111111011110, //105 i
    0b0111111111011101, //106 j
    0b1111001101100111, //107 k
    0b0111111101110111, //108 l
    0b1111010101001111, //109 m
    0b1111111101001111, //110 n
    0b0111111101001111, //111 o
    0b1111111101100100, //112 p
    0b1111111111000100, //113 q
    0b1111111101101111, //114 r
    0b0111001011111111, //115 s
    0b0111111101100111, //116 t
    0b0111111101011111, //117 u
    0b1111111100111111, //118 v
    0b1111100100111111, //119 w
    0b1101101110111011, //120 x
    0b0111111111000101, //121 y
    0b0111111110101111, //122 z
    0b1111111111111111, //123 {
    0b1111111111111111, //124 |
    0b1111111111111111, //125 }
    0b1111111111111111, //126 ~
    0b1111111111111111, //127 DEL
    };



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
    writeChar('C');
  }

  CAN0.setMode(MCP_NORMAL); 
  pinMode(CAN0_INT, INPUT);

  // Setup pins as Outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(drivePin, INPUT);
  pinMode(neutralPin, INPUT);
  pinMode(reversePin, INPUT);

  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, HIGH);
  digitalWrite(dataPin,  LOW);

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

  if(digitalRead(drivePin))
  {
    byte sndStat = CAN0.sendMsgBuf(0x420010, 1, 1, drive);
    driveState();
  }
  else if(digitalRead(neutralPin))
  {
    byte sndStat = CAN0.sendMsgBuf(0x420010, 1, 1, neutral);
    neutralState();
  }
  else if(digitalRead(reversePin))
  {
    byte sndStat = CAN0.sendMsgBuf(0x420010, 1, 1, reverse);
    reverseState();
  }
  else
    writeChar('Z');
}

void comutacar(void)
{
  writeChar('C');
  delay(250);
  writeChar('O');
  delay(250);
  writeChar('M');
  delay(250);
  writeChar('U');
  delay(250);
  writeChar('T');
  delay(250);
  writeChar('A');
  delay(250);
  writeChar('C');
  delay(250);
  writeChar('A');
  delay(250);
  writeChar('R');
  delay(250);
  writeChar(' ');
  delay(1000);

}

void driveState(void)
{
  writeChar('D');
}

void neutralState(void)
{
  writeChar('N');
}

void reverseState(void)
{
  writeChar('R');
}

void writeChar(char letter)
{
  uint8_t characterNumber;
  characterNumber = letter;

  digitalWrite(latchPin, LOW);
  delay(10);
  // Shift out the bits
  shiftOut(dataPin, clockPin, LSBFIRST, highByte(character[characterNumber]));
  shiftOut(dataPin, clockPin, LSBFIRST, lowByte(character[characterNumber]));
  delay(10);
  //latch
  digitalWrite(latchPin, HIGH);

}