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

#define DHTPIN A8     // what pin we're connected to

// The following keys are for structure purpose only. You must define YOUR OWN. 
const uint8_t appEUI[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint8_t appKey[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

bool first = true;
  
bool joinNetwork()
{             
  OrangeForRN2483.setDataRate(DATA_RATE_1); // Set DataRate to SF11/125Khz
  return OrangeForRN2483.joinNetwork(appEUI, appKey);
}

void setup() {
  debugSerial.begin(57600); 
  
  while ((!debugSerial) && (millis() < 10000)) ;

  OrangeForRN2483.init();
}

bool SendLoRaMessage()
{
  const uint8_t size = 5;
  uint8_t port = 5;
  uint8_t data[size] = { 0x48, 0x65, 0x6C, 0x6C, 0x6F }; // Hello

  return OrangeForRN2483.sendMessage(data, size, port); // send unconfirmed message
}

void loop() {

  if(first)
  {
    first = false;
    debugSerial.println("Join Request");
    bool res = joinNetwork();
    if(res)
    {
      debugSerial.println("Join Success");
      OrangeForRN2483.enableAdr();

      debugSerial.println("Send Message #1");
      SendLoRaMessage();
      delay(20000);
      debugSerial.println("Send Message #2");
      SendLoRaMessage();
      delay(20000);
      debugSerial.println("Send Message #3");
      SendLoRaMessage();      
    }else debugSerial.println("Join Failed");
    debugSerial.println("Program Finished");
  }
}



