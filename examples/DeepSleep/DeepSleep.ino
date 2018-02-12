#include <OrangeForRN2483.h>

#define debugSerial SerialUSB

bool first = true;

void setup() {
  debugSerial.begin(57600); 

  while ((!debugSerial) && (millis() < 10000)) ;

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  OrangeForRN2483.init();
}

void loop() {
	  
	if(!OrangeForRN2483.isDeepSleeping())
    {
  	  String devEUI = OrangeForRN2483.getSysCmds()->getHardwareDevEUI();

      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      
      debugSerial.print("devEUI = "); debugSerial.println(devEUI);    
      debugSerial.println("Deep sleep");    
      debugSerial.end();
    }  
	// DeepSleep 00:01:30
	OrangeForRN2483.deepSleep(0, 1, 30);
     
}
