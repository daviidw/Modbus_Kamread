 /*
 * Copyright © 2011-2012 Stéphane Raimbault <stephane.raimbault@gmail.com>
 * License ISC, see LICENSE for more details.
 */


#include <SimpleModbusSlave.h>
#include <KamRead.h>
#include <ActivityLed.h>
#include <AltSoftSerial.h>

/* Define Pins */
#define LED  13   // onboard led
#define TX_En_Pin 2   // Enable pin for TX transmission
#define Default_Slave_ID 1

//////////////// registers of your slave ///////////////////
enum 
{     
  // just add or remove registers and your good to go...
  //0x003C,0x0050,0x004A,0x0056,0x0057,0x0059
  MWh_Counter,     
  KW_Power,        
  Heat_Flow,
  Input_Temp,
  Return_Temp,
  Delta_In_Out,
  Error_Code,
  // leave this one
  TOTAL_REGS_SIZE 
  // total number of registers for function 3 and 16 share the same register array
};
unsigned int Total_Errors;

int holdingRegs[TOTAL_REGS_SIZE]; // function 3 and 16 register array
////////////////////////////////////////////////////////////

/* Allocate a mapping of 10 values */
//uint16_t tab_reg[10];
//int tab_reg[10];

//Setup kamstrup interface
// "Heat Energy Counter","Power", "Max power this year", "Input temperature","Return temperature","Delta temperature"
unsigned int Registers[] = {0x003C,0x0050,0x004A,0x0056,0x0057,0x0059};
#define NUMREGS 6

KamRead Kamstrup(1200);

void setup() {
  /* The transfer speed is set to 19200 bauds (Eight bits, no parity, One stop bit) */
  modbus_configure(19200, Default_Slave_ID, TX_En_Pin, LED, TOTAL_REGS_SIZE, true);
  
  Kamstrup.Setup(holdingRegs, Registers, NUMREGS);
}

void loop() {

 
  Total_Errors = modbus_update(holdingRegs);

  Kamstrup.Loop();

  //Led_Blink(digitalRead(TX_En_Pin), LED);
    
}
