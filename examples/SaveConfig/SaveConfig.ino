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
*              2017-05-09 by Karim BAALI
*              2017-10-27 by Karim BAALI
*/

#include "OrangeForRN2483.h"

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
   
    OrangeForRN2483.enableAdr();
    OrangeForRN2483.setDataRate(DATA_RATE_0);
         
    debugSerial.println("Save LoRaWAN Parameters");
    
    OrangeForRN2483.save();    
    
    OrangeForRN2483.getSysCmds()->sleep(10000);
    debugSerial.println("Sleeping 10 seconds");

    bool sleep = OrangeForRN2483.getSysCmds()->isAsleep();

    while(sleep)
    {
      eBoolean isAdr = OrangeForRN2483.isAdr();
      if(isAdr == BOOL_ERROR)
      {
        eErrorType error = OrangeForRN2483.getLastError();
        if(error == LORA_SLEEP)
        {
          debugSerial.println("RN2483 already sleeping");
        }
        else
        {
          debugSerial.print("Error: ");
          debugSerial.println(error);
        }
      }
      else
      {
        sleep = false;
        debugSerial.print("Is Adr ? ");debugSerial.println(isAdr);        
      }
      delay(500);
    }
        
    debugSerial.println("Program finished");
  }
}

