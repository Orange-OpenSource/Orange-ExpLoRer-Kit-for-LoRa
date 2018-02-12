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

// The following keys are for structure purpose only. You must define YOUR OWN. 
const uint8_t appEUI[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t appKey[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

bool first = true;
  
bool joinNetwork()
{             
  debugSerial.print("devEUI = "); debugSerial.println(OrangeForRN2483.getSysCmds()->getHardwareDevEUI());  
  OrangeForRN2483.setDataRate(DATA_RATE_1); // Set DataRate to SF11/125Khz

  return OrangeForRN2483.joinNetwork(appEUI, appKey);
}

void setup() {
  debugSerial.begin(57600); 
  
  while ((!debugSerial) && (millis() < 10000)) ;

  OrangeForRN2483.init();
  debugSerial.println("Start");

  if(joinNetwork()){
    debugSerial.println("Join : success");
    OrangeForRN2483.enableAdr();
  } else {
    debugSerial.println("Join : fail");
  }
}

bool SendLoRaMessage()
{
  const uint8_t size = 5;
  uint8_t port = 5;
  uint8_t data[size] = { 0x48, 0x65, 0x6C, 0x6C, 0x6F };

  return OrangeForRN2483.sendMessage(UNCONFIRMED_MESSAGE, data, size, port); 
}

// the loop function runs over and over again until power down or reset
void loop() {

  if(first)
  {
    first = false;
    if(OrangeForRN2483.getJoinState())
    {     
      if(SendLoRaMessage())
      {
        DownlinkMessage* downlinkMessage = OrangeForRN2483.getDownlinkMessage();
        debugSerial.print("Port :");debugSerial.println(downlinkMessage->getPort());
        
        const String msgStr = downlinkMessage->getMessage();
        int8_t len = 0;
        const char* msgByte = (const char*)downlinkMessage->getMessageByteArray(&len);
        
        if(msgStr != NULL) debugSerial.print("Msg str :"); debugSerial.println(msgStr.c_str());
        
        if(msgByte != NULL){
          debugSerial.print("Msg array : ");
                    
          for(int i = 0; i < len; i++){
            debugSerial.print(msgByte[i], HEX);
          }
        }
                
      }
      
      delay(20000);

    }
    else debugSerial.println("Stop programm");
  }
}


