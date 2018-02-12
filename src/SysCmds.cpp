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
*			   2017-10-27 by Karim BAALI
*/

#include "SysCmds.h"
#include "RnRequest.h"

//Getters
String SysCmdsClass::getVersion()
{
	return String((char*)RnRequest.rnRequest(SYS, GET, params[VERSION]));
}

String SysCmdsClass::getNvm(uint8_t address[2])
{
	return String((char*)RnRequest.rnRequest(SYS, GET, params[NVM], address, 2));
}

bool SysCmdsClass::setNvm(uint8_t address[2], uint8_t data[1])
{
//	int8_t temp[4] = { address[0], address[1], -1, data[0] };
//	return !isEmpty(RnRequest.rnRequest(SYS, SET, params[NVM], temp, 4));
	return false;
}

String SysCmdsClass::getHardwareDevEUI()
{
	uint8_t* data = RnRequest.rnRequest(SYS, GET, params[HWEUI]);
	return String((char*)data);
}

String SysCmdsClass::getPindig(String pinname)
{
	return String((char*)RnRequest.rnRequest(SYS, GET, params[PIN_DIG], pinname.c_str()));
}

bool SysCmdsClass::sleep(uint32_t delay)
{	
	RnRequest.isAsleep = (RnRequest.rnRequest(SYS, params[SLEEP], String(delay).c_str()) == NULL);
	return RnRequest.isAsleep;
}

bool SysCmdsClass::isAsleep()
{
	return RnRequest.checkIsAsleep();
}

bool SysCmdsClass::setPinDig(String pinname, String pinstate)
{
	String pinDig = pinname + SEPARATOR + pinstate;
	return (RnRequest.rnRequest(SYS, SET, params[PIN_DIG], pinDig.c_str()) != NULL);
}

String SysCmdsClass::getPinana(String pinname)
{
	return String((char*)RnRequest.rnRequest(SYS, GET, params[PIN_ANA], pinname.c_str()));
}

int16_t SysCmdsClass::getVdd()
{
	uint8_t* response = RnRequest.rnRequest(SYS, GET, params[VDD]);
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

bool SysCmdsClass::setPinMode(String pinname, String pinfunc)
{
	String pinMode = pinname + SEPARATOR + pinfunc;
	return (RnRequest.rnRequest(SYS, SET, params[PIN_MODE], pinMode.c_str()) != NULL);
}

String SysCmdsClass::reset()
{
	return String((char*)RnRequest.rnRequest(SYS, params[RESET]));
}

void SysCmdsClass::wakeUp()
{
	if (isAsleep())
	{
		RnRequest.setBreakCondition();

		delay(100);

		// set baudrate
		RnRequest.setWakeupFlag();
		RnRequest.isAsleep = false;
	}
}