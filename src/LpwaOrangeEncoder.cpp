/*
* Copyright (C) 2017 Orange
*
* This software is distributed under the terms and conditions of the 'Apache-2.0'
* license which can be found in the file 'LICENSE.txt' in this package distribution
* or at 'http://www.apache.org/licenses/LICENSE-2.0'.
*/

/* Orange LoRa Explorer Kit
*
* Version:    1.0-SNAPSHOT
* Created:    2017-04-21 by Halim BENDIABDALLAH
* Modified:	  2017-10-27 by Karim BAALI
*/

#include <Arduino.h>

#include "LpwaOrangeEncoder.h"

#define MAX_LEN_PAYLOAD			64

#define CHECK_COUNTER(X)		if((counter + (X - 1)) >= MAX_LEN_PAYLOAD) return false;  // X = byte length of value

LpwaOrangeEncoderClass LpwaOrangeEncoder;

LpwaOrangeEncoderClass::LpwaOrangeEncoderClass()
{
    counter = 0;
    memset(framePayload, 0, MAX_LEN_PAYLOAD);
}

LpwaOrangeEncoderClass::~LpwaOrangeEncoderClass()
{
}

void LpwaOrangeEncoderClass::flush()
{
	counter = 0;
	memset(framePayload, 0, MAX_LEN_PAYLOAD);
}

uint8_t* LpwaOrangeEncoderClass::getFramePayload(int8_t* len)
{
	if (len == 0) return NULL;
	*len = counter;
	return (uint8_t*)framePayload;
}

bool LpwaOrangeEncoderClass::addByte(int8_t value)
{
    CHECK_COUNTER(1);    
	framePayload[counter++] = (value & 0xFF);
    return true;
}

bool LpwaOrangeEncoderClass::addUByte(uint8_t value)
{
	return addByte((int8_t)value);
}

bool LpwaOrangeEncoderClass::addBool(bool value)
{
	return addByte((int8_t)value);
}

bool LpwaOrangeEncoderClass::addShort(int16_t value)
{
    CHECK_COUNTER(2);

	framePayload[counter++] = (value >> 8) & 0xFF;
	framePayload[counter++] = (value & 0xFF);
	
    return true;
}

bool LpwaOrangeEncoderClass::addUShort(uint16_t value)
{
	return addShort((int16_t)value);
}

bool LpwaOrangeEncoderClass::addInt(int32_t value)
{
    CHECK_COUNTER(4);

	framePayload[counter++] = value >> 24;
	framePayload[counter++] = (value >> 16) & 0xFF;
	framePayload[counter++] = (value >> 8) & 0xFF;
	framePayload[counter++] = (value & 0xFF);

    return true;
}

bool LpwaOrangeEncoderClass::addUInt(uint32_t value)
{
	return addInt((int32_t)value);
}

bool LpwaOrangeEncoderClass::addLong(int64_t value)
{
    CHECK_COUNTER(8);

	framePayload[counter++] = value >> 56; 
	framePayload[counter++] = (value >> 48) & 0xFF;
	framePayload[counter++] = (value >> 40) & 0xFF; 
	framePayload[counter++] = (value >> 32) & 0xFF;
	framePayload[counter++] = (value >> 24) & 0xFF;
	framePayload[counter++] = (value >> 16) & 0xFF;
	framePayload[counter++] = (value >> 8) & 0xFF;
	framePayload[counter++] = (value & 0xFF);

	return true;
}

bool LpwaOrangeEncoderClass::addULong(uint64_t value)
{

	return addLong((int64_t)value);
}

bool LpwaOrangeEncoderClass::addFloat(float value)
{
	CHECK_COUNTER(4);
	char floatValue[4];
	memcpy(&floatValue, &value, 4);

	for(int i = 0; i < 4; i++)
		framePayload[counter++] = floatValue[3 - i];

	return true;
}

