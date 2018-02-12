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

#include "RadioCmds.h"
#include "RnRequest.h"

eBT RadioCmdsClass::getBt()
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[BT]);

	if(response == NULL) return BT_ERROR;

	String res = String((char*) response);

	if (res.equals("none")) return BT_NONE;
	else if (res.equals("1.0")) return BT_1_0;
	else if (res.equals("0.5")) return BT_0_5;
	else if (res.equals("0.3")) return BT_0_3;
	else return BT_ERROR;	
}

bool RadioCmdsClass::setBt(eBT bt)
{
	String gfBT[] = {"none", "1.0", "0.5", "0.3" };
	if ((bt < 0) || (bt > BT_COUNT - 1)) return false;
	return (RnRequest.rnRequest(RADIO, SET, params[BT], gfBT[bt].c_str()) != NULL);
}

eModulation RadioCmdsClass::getModulation()
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[MOD]);
	if (response == NULL) return GET_MODULATION_ERROR;

	eModulation modulation = String((char*)response).equals("lora") ? LORA_MODULATION : FSK_MODULATION;
	return modulation;
}

bool RadioCmdsClass::setModulation(eModulation modulation)
{
	String mod = (modulation == FSK_MODULATION) ? "fsk" : "lora";

	return (RnRequest.rnRequest(RADIO, SET, params[MOD], mod.c_str()) != NULL);
}

eSpreadingFactor RadioCmdsClass::getSF()
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[SPR_FACTOR]);
	
	if(response == NULL) return SF_ERROR;
	
	String strValue = String((const char*)response + 2);
	return (eSpreadingFactor)strValue.toInt();
}

bool RadioCmdsClass::setSF(eSpreadingFactor spreadingFactor)
{
	String strSF = "sf" + String(spreadingFactor);
	return (RnRequest.rnRequest(RADIO, SET, params[SPR_FACTOR], strSF.c_str()) != NULL);
}

eBoolean RadioCmdsClass::getCrc()
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[CRC]);
	return (response != NULL) ? iS_ON(String((char*)response)) : BOOL_ERROR;
}

eBoolean RadioCmdsClass::getIqInversion()
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[IQ_INVERS]);
	return (response != NULL) ? iS_ON(String((char*)response)) : BOOL_ERROR;
}

eCodingRate RadioCmdsClass::getCodingRate()
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[CODING_RATE]);
	if (response == NULL) return CR_ERROR;

	String res = String((char*)response);

	if(res.equals("4/5")) return CR_4_5;
	else if(res.equals("4/6")) return CR_4_6;
	else if (res.equals("4/7")) return CR_4_7;
	else if (res.equals("4/8")) return CR_4_8;
	else return CR_ERROR;	
}

short RadioCmdsClass::getSync()
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[SYNC_RADIO]);
	if (response == NULL) return INT_ERROR_FAILED;

	String sync = "0x" + String((char*)response);
	return sync.toInt();
}

float RadioCmdsClass::getAutoFreqCorrBw()
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[AUTO_FREQ_CORR_BW]);
	return (response != NULL) ? String((char*)response).toFloat() : FLT_ERROR_FAILED;
}

float RadioCmdsClass::getReceiveBw()
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[RECEIVE_BW]);
	return (response != NULL) ? String((char*)response).toFloat() : FLT_ERROR_FAILED;
}

bool RadioCmdsClass::getOutputPower(int8_t& outputPower)
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[PWR]);
	if(response == NULL) return false;
  
	outputPower = String((char*)response).toInt();
	return true;
}

bool RadioCmdsClass::setOutputPower(int8_t pwrout)
{
	return (RnRequest.rnRequest(RADIO, SET, params[PWR], String(pwrout).c_str()) != NULL);
}

int16_t RadioCmdsClass::getBandWidth()
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[BANDWIDTH]);
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

int16_t RadioCmdsClass::getSigNoiseRation()
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[SIG_NOISE_RATIO]);
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

int32_t RadioCmdsClass::getBitRate()
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[BIT_RATE]);
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

int32_t RadioCmdsClass::getFreqDeviation()
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[FREQ_DEVIATION]);
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

int32_t RadioCmdsClass::getPreambleLength()
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[PREAMBLE_LENGTH]);
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

int32_t RadioCmdsClass::getFrequency()
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[FREQ]);
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

bool RadioCmdsClass::setFrequency(int32_t frequency)
{	
	return (RnRequest.rnRequest(RADIO, SET, params[FREQ], String(frequency).c_str()) != NULL);
}

bool RadioCmdsClass::getWatchdog(uint64_t& watchdog)
{
	uint8_t* response = RnRequest.rnRequest(RADIO, GET, params[WATCHDOG_TIMER]);
	if (response == NULL) return false;
	
	watchdog = String((char*)response).toInt();
	return true;
}

bool RadioCmdsClass::setAutoFreqBand(String autoFreqBand)
{
	return (RnRequest.rnRequest(RADIO, SET, params[AUTO_FREQ_CORR_BW], autoFreqBand.c_str()) != NULL);
}

