/*****************************************************************************
/* This is the base template for the CAN Bridge. It has two CAN ports, CAN0
/* and CAN1. CAN0 is on the right and connects to the 'main' CAN bus.
/* CAN1 is on the left and connects to the sub-busses of the car. ASCII art:
/*
/*  __| |__                       __| |__
/*  |      |                      |      |
/*  | CAN1 |                      | CAN0 |
/*  |______|                      |______|
/*
/****************************************************************************/

#include <mcp_can.h>
#include <mcp_can_dfs.h>

#include <mcp_can.h>
#include <avr/io.h>
#include <util/delay.h>
#include <SPI.h>

const int SPI_CS0_PIN = 10;
const int SPI_CS1_PIN = 9;

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];                   


#define CAN0_INT 2      //set int pin to 2
#define CAN1_INT 3
MCP_CAN CAN0(SPI_CS0_PIN);//set CS pin to 10
MCP_CAN CAN1(SPI_CS1_PIN);

void setup ()
{
  Serial.begin(9600);
  while(!Serial);

  ///Initialize CAN0
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
  {
    Serial.println("CAN Bus 0 init successful");
  }
  else
  {
    Serial.println("error init can0 bus");
  }

  if(CAN1.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
  {
    Serial.println("CAN Bus 1 init successful");
  }
  else
  {
    Serial.println("error init can1 bus");
  }

  CAN0.setMode(MCP_NORMAL);
  CAN1.setMode(MCP_NORMAL);
  pinMode(CAN0_INT, INPUT);
  pinMode(CAN1_INT, INPUT);

}

void loop() {

  processCAN();

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
    if((rxId & 0x1FFFFFFF) == 0x420201)
    {

    }
    if((rxId & 0x1FFFFFFF) == 0x420202)
    {

    }
    if((rxId & 0x1FFFFFFF) == 0x420203)
    {

    }
    if((rxId & 0x1FFFFFFF) == 0x420204)
    {

    }
    if((rxId & 0x1FFFFFFF) == 0x420205)
    {

    }
    if((rxId & 0x1FFFFFFF) == 0x420206)
    {

    }
    if((rxId & 0x1FFFFFFF) == 0x420207)
    {

    }
    if((rxId & 0x1FFFFFFF) == 0x420208)
    {

    }
    if ((rxId & 0x1FFFFFFF) == 0x420010) {

    }

    if ((rxId & 0x1FFFFFFF) == 0x420300) {

    }

    if((rxId & 0x1FFFFFFF) == 0x420301) {  //state of the high beam

    }

    if((rxId & 0x1FFFFFFF) == 0x420302) {  //state of the lights

    }

    if((rxId & 0x1FFFFFFF) == 0x420303) {  //state of the wipers

    }

    if((rxId & 0x1FFFFFFF) == 0x420304) {  //state of the wipers

    }

    if((rxId & 0x1FFFFFFF) == 0x420305) {  //state of the hazard

    }


    if((rxId & 0x1FFFFFFF) == 0x420306) {  //state of the brakes

    }

    if((rxId & 0x1FFFFFFF) == 0x420312) {  //state of the blinker

    }
  }
}