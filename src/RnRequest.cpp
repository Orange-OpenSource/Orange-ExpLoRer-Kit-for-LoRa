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

#include <stdio.h>
#include <stdlib.h>

#include "RnRequest.h"

RnRequestClass RnRequest;


RnRequestClass::RnRequestClass(){
	this->receiveBuffer[0] = 0;
	isAsleep = false;
}

RnRequestClass::~RnRequestClass(){
}

void RnRequestClass::init()
{
	this->loraStream = &Serial2;
	this->loraStream->begin(57600);
}

bool RnRequestClass::isStreamInit()
{
	return (this->loraStream);
}

bool RnRequestClass::cmdRequest(uint8_t type, const char* command, const char* paramName)
{
	if (command == NULL)  return false;

	debugPrint(commandType[type]); debugPrint(SEPARATOR);  debugPrint(command); debugPrint(SEPARATOR);  debugPrintLn(paramName);

	this->loraStream->print(commandType[type]);
	this->loraStream->print(SEPARATOR);
	this->loraStream->print(command);

	if (paramName != NULL)
	{
		this->loraStream->print(SEPARATOR);
		this->loraStream->print(paramName);
	}
	return true;
}

bool RnRequestClass::writeHexString(const uint8_t* paramValue, uint8_t lenParamValue)
{
	if ((paramValue == NULL) || (lenParamValue <= 0)) return false;

	this->loraStream->print(SEPARATOR);
	for (int i = 0; i < lenParamValue; i++) {
		this->loraStream->print(static_cast<char>(NIBBLE_TO_HEX_CHAR(HIGH_NIBBLE(paramValue[i]))));
		this->loraStream->print(static_cast<char>(NIBBLE_TO_HEX_CHAR(LOW_NIBBLE(paramValue[i]))));
	}
}

uint8_t* RnRequestClass::rnUplinkRequest(const char* paramName, const uint8_t* paramValue, uint8_t lenParamValue, uint8_t port)
{
	if (checkIsAsleep()) return NULL;

	if (!cmdRequest(MAC, params[TX_MAC], paramName)) return NULL;

	this->loraStream->print(SEPARATOR);
	this->loraStream->print(port);

	writeHexString(paramValue, lenParamValue);
	this->loraStream->print(CRLF);

	uint8_t* response = getResponse();
	if (response == NULL) return NULL;

	return getResponse(UPLINK_TIMEOUT);
}

uint8_t* RnRequestClass::rnRequest(uint8_t type, const char* command, const char* paramName, const uint8_t* paramValue, uint8_t lenParamValue)
{
	if (checkIsAsleep()) return NULL;

	if (!cmdRequest(type, command, paramName)) return NULL;

	writeHexString(paramValue, lenParamValue);
	this->loraStream->print(CRLF);

	return getResponse();
}

uint8_t* RnRequestClass::rnRequest(uint8_t type, const char* command, const char* paramName, const char* paramValues)
{
	if (checkIsAsleep()) return NULL;

	if (!cmdRequest(type, command, paramName)) return NULL;

	if (paramValues != NULL)
	{
		this->loraStream->print(SEPARATOR);
		this->loraStream->print(paramValues);
	}

	this->loraStream->print(CRLF);


	return getResponse(getTimeoutDelay(command));
}

uint32_t RnRequestClass::getTimeoutDelay(const char* command)
{
	return (strcmp(command, "save") != 0) ? DEFAULT_TIMEOUT : SAVE_TIMEOUT;
}

uint8_t* RnRequestClass::getResponse(uint32_t timeout)
{
	uint16_t len;
	unsigned long start = millis();

	while (millis() < start + timeout) {
		len = getReceivedData();

		if (len > 0) {
			debugPrint("Rn2483 Buffer: ");
			debugPrintLn(this->receiveBuffer);
			
			this->successType = checkSuccess(this->receiveBuffer);
			if (this->successType != LORA_FAILED) return this->receiveBuffer;

			this->errorType = checkErrors(this->receiveBuffer);

			return (this->errorType == LORA_SUCCESS) ? this->receiveBuffer : NULL;
		}
	}

	this->errorType = LORA_TIMEOUT;
	return NULL;
}

uint16_t RnRequestClass::getReceivedData()
{
	return readLn(this->receiveBuffer, DEFAULT_INPUT_BUFFER_SIZE);
}

uint16_t RnRequestClass::readLn(uint8_t* buffer, uint16_t size)
{
	uint16_t len = this->loraStream->readBytesUntil('\n', (uint8_t*)buffer, size);
	if (len > 0) {
		this->receiveBuffer[len - 1] = 0;
	}
	return len;
}

eSuccessType RnRequestClass::checkSuccess(uint8_t* resp) {
	int resNum = -1;

	bool found = false;
	int i = 0;

	while ((i <	LORA_COUNT_SUCCESS) && (!found))
	{
		if (strncmp(successResponses[i], (char*)resp, strlen(successResponses[i])) == 0) found = true;
		else i++;
	}

	return (found ? (eSuccessType)i : LORA_FAILED);
}

eErrorType RnRequestClass::checkErrors(uint8_t* resp) {
	int resNum = -1;

	bool found = false;
	int i = 0;

	while ((i <	LORA_COUNT_ERRORS) && (!found))
	{
		if (strcmp((char*)resp, possibleResponses[i]) == 0) found = true;
		else i++;
	}

	debugPrint("Response : "); debugPrint(resp); debugPrintLn(" received during execution !");
	return (found ? (eErrorType)i : LORA_SUCCESS);
}

eSuccessType RnRequestClass::getLastSuccess()
{
	return this->successType;
}

eErrorType RnRequestClass::getLastError()
{
	return this->errorType;
}

void RnRequestClass::setLastError(eErrorType errorType)
{
	this->errorType = errorType;
}

bool RnRequestClass::checkIsAsleep()
{
	if (!isAsleep) return false;
	
	if (getResponse() == NULL)
	{
		this->errorType = LORA_SLEEP;
		return true;
	}
	
	isAsleep = false;

	return isAsleep;
}

void RnRequestClass::setBreakCondition()
{
	// "emulate" break condition
	this->loraStream->flush();

	this->loraStream->begin(300);
	this->loraStream->write((uint8_t)0x00);
	this->loraStream->flush();
}

void RnRequestClass::setWakeupFlag()
{
	this->loraStream->begin(57600);
	this->loraStream->write((uint8_t)0x55);
	this->loraStream->flush();

	RnRequest.getResponse();
}