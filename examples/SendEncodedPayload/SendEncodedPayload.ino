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

int count = 0;
int buttonCount = 0;
long timestamp = 0;
int pushButton = 0;
int nbrPush = 0;

typedef enum _eLedColor {
  RED = 0,
  GREEN,
  BLUE,
  WHITE,
  ORANGE 
}eLedColor;

typedef struct _sRgbColor
{
  int red;
  int green;
  int blue;
}sRgbColor;

sRgbColor listRgbColor[] = {
  {.red = LOW, .green = HIGH, .blue = HIGH},
  {.red = HIGH, .green = LOW, .blue = HIGH},
  {.red = HIGH, .green = HIGH, .blue = LOW},
  {.red = LOW, .green = LOW, .blue = LOW},
  {.red = LOW, .green = LOW, .blue = HIGH},
};

void initRgbLed()
{
  //Initialize the LEDs and turn them all off
  pinMode(LED_RED, OUTPUT) ;
  pinMode(LED_GREEN, OUTPUT) ;
  pinMode(LED_BLUE, OUTPUT) ;   
}

void initPin()
{
  //Initialize the LEDs and turn them all off
  initRgbLed();
 
  //Set the temperature sensor pin as input
  pinMode(TEMP_SENSOR, INPUT) ;
  //Set ADC resolution to 12 bits
  analogReadResolution(12) ;  
}

void setRgbColor(eLedColor color){
  digitalWrite(LED_RED, listRgbColor[color].red);
  digitalWrite(LED_GREEN, listRgbColor[color].green);
  digitalWrite(LED_BLUE, listRgbColor[color].blue);
}

void setup()
{ 
  initPin();     
  debugSerial.begin(57600); 

  while((!debugSerial) && (millis() < 10000));
  
  OrangeForRN2483.init();

  setRgbColor(ORANGE);

  LpwaOrangeEncoder.flush();

  bool res = 0;
  int attempt = 0;
  do 
  {
    setRgbColor(BLUE);
    debugSerial.println("Join Request") ;

    OrangeForRN2483.setDataRate(DATA_RATE_1); // Set DataRate to SF11/125Khz
    
    res = OrangeForRN2483.joinNetwork(appEUI, appKey);
    debugSerial.println(res ? "Join Accepted." : "Join Failed! Trying again. Waiting 10 seconds.") ;
    
    if(!res)
    {
      setRgbColor(RED);
      attempt++;
      delay(10000);
    }
    
    if (attempt == 3) 
    {
      debugSerial.println("All Join Failed. Program stoped") ;
      while(true) {        
        setRgbColor(RED);
        delay(1000);
        setRgbColor(ORANGE);
        delay(1000);
        setRgbColor(WHITE);
        delay(1000);

      }
    }
  }while (res == 0);
  
  debugSerial.println("Sleeping for 5 seconds before starting sending out test packets.");
  sleep(5);  
}

void sleep(unsigned short count)
{
  for (uint8_t i = count; i > 0; i--)
  {
    debugSerial.println(i) ;
    delay(1000) ;
  }
}

void debugFrame(int8_t* frame, int8_t len)
{  
    if(frame != NULL)
    {
        debugSerial.print("Payload: ");
        int i = 0;
        for(i = 0; i < len; i++)
        {
            unsigned char value = (unsigned char)frame[i];
            debugSerial.print(value, HEX); debugSerial.print(" ");
        }
        debugSerial.print("\r\n");
    }
}

float getTemperature()
{
  uint8_t samples = 10;

  float sum = 0.0 ;    // reset averaged reading to start at 0
  // This loop does 10 readings of the voltage, and adds this to the variable
  for(int i = 0; i < samples; i++)
    sum += 3.3/4095.0 * (float)analogRead(TEMP_SENSOR) ;

  // Divide the voltage to get average
  float voltage = sum / samples ;
  
  // Convert voltage to temperature
  double temperature = (voltage - 0.5) * 100.0 ;
  return temperature;
}

void updateStateButton()
{
    int sensorVal = digitalRead(BUTTON);
    
    if(sensorVal == LOW){
      digitalWrite(LED_BUILTIN, HIGH);
      pushButton = 1;
    }
    else if((sensorVal == HIGH) && (pushButton == 1)){
      digitalWrite(LED_BUILTIN, LOW);
      nbrPush++;
      pushButton = 0;
    }  
}

void loop() {
  updateStateButton();
  
  if ((millis() - timestamp) > 15000) {
    setRgbColor(WHITE);
    float temperature = getTemperature();

    LpwaOrangeEncoder.flush();
    LpwaOrangeEncoder.addFloat(temperature);
    LpwaOrangeEncoder.addInt(nbrPush);

    uint8_t port = 5;
    int8_t len;
    uint8_t* frame = LpwaOrangeEncoder.getFramePayload(&len);
    debugFrame(frame, len);
    bool res = OrangeForRN2483.sendMessage(frame, len, port);

    if(res) {
        debugSerial.println("Successful transmission.");
        DownlinkMessage* downlinkMessage = OrangeForRN2483.getDownlinkMessage();

        int port = downlinkMessage->getPort();
        String message = downlinkMessage->getMessage();
                
        debugSerial.print("Port :");
        debugSerial.print(port);
        if(message == NULL) 
          debugSerial.println("Response with empty payload"); 
        else {
          debugSerial.print("Frame Payload :");
          debugSerial.println(message);
        }   
        
        setRgbColor(GREEN);
        count = 0;
        delay(2000);  
        setRgbColor(WHITE);   
      }
      else {
          setRgbColor(RED);
          eErrorType errorType = OrangeForRN2483.getLastError();
          switch(errorType) {   
            case LORA_TIMEOUT:       
              debugSerial.println("Connection timed-out. Check your serial connection to the device! Sleeping for 20sec.");
              delay(20000) ;
            break ;
      
            case LORA_INVALID_DATA_LEN:
              debugSerial.println("The size of the payload is greater than allowed. Transmission failed!");
            break ;
           
            case LORA_BUSY:
              debugSerial.println("The device is busy. Sleeping for 10 extra seconds.");
              delay(10000) ;
            break ;
              
            default: 
              debugSerial.println("Other error");
              delay(10000) ;
            break ;
      } 
    } 
    nbrPush = 0; 
    timestamp = millis();   
  }
}




