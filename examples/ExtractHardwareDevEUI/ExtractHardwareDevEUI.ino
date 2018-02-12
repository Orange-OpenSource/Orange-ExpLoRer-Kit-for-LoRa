/*
* Copyright (C) 2017 Orange
*
* This software is distributed under the terms and conditions of the 'Apache-2.0'
* license which can be found in the file 'LICENSE.txt' in this package distribution
* or at 'http://www.apache.org/licenses/LICENSE-2.0'.
*/

/* Orange LoRa Explorer Kit
*
* Version:     1.0-SNAPSHOT
* Created:     2017-02-15 by Karim BAALI
* Modified:    2017-04-21 by Halim BENDIABDALLAH
*			         2017-05-09 by Karim BAALI
*              2017-10-27 by Karim BAALI
*/

#include <OrangeForRN2483.h>

#define debugSerial SerialUSB

bool first = true;

void setup() {
  debugSerial.begin(57600); 

  while ((!debugSerial) && (millis() < 10000)) ;

  OrangeForRN2483.init();
}

void loop() {

  if(first)
  {   
    first = false;
    
    String devEUI = OrangeForRN2483.getSysCmds()->getHardwareDevEUI();
    debugSerial.print("devEUI = "); debugSerial.println(devEUI);    
    debugSerial.println("Program finished");
  } 
}

