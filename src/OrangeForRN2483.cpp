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
*/

#include <stdio.h>
#include <stdlib.h>

#include "OrangeForRN2483.h"

OrangeForRN2483Class OrangeForRN2483;

OrangeForRN2483Class::OrangeForRN2483Class()
{
}

OrangeForRN2483Class::~OrangeForRN2483Class()
{
}

void OrangeForRN2483Class::init()
{
	RnRequest.init();
	resetDevice();
}

RadioCmdsClass* OrangeForRN2483Class::getRadioCmds()
{
	return &RadioCmds;
}

SysCmdsClass* OrangeForRN2483Class::getSysCmds() {
	return &SysCmds;
}

eErrorType OrangeForRN2483Class::getLastError()
{
	RnRequest.getLastError();
}

void OrangeForRN2483Class::setLastError(eErrorType errorType)
{
	RnRequest.setLastError(errorType);
}

bool OrangeForRN2483Class::getJoinState()
{
	return this->isNetworkJoined;
}

bool OrangeForRN2483Class::isStreamInit()
{
	return RnRequest.isStreamInit();
}

bool OrangeForRN2483Class::setAbpKeys(const int8_t* nwkSkey, const int8_t* appSKey)
{
	return (setNwkSKey(nwkSkey) && setAppSKey(appSKey));
}

bool OrangeForRN2483Class::setOttaKeys(const int8_t* devEui, const int8_t* appEui, const int8_t* appKey)
{
	return (setDevEUI(devEui) && setAppEUI(appEui) && setAppKey(appKey));
}

void OrangeForRN2483Class::resetDevice()
{
	pinMode(LORA_RESET, OUTPUT);
	digitalWrite(LORA_RESET, LOW);
	delay(10);
	digitalWrite(LORA_RESET, HIGH);
	delay(200);
	RnRequest.getResponse();
}

bool OrangeForRN2483Class::joinNetwork(const int8_t* appEui, const int8_t* appKey)
{
	String hwDevEuiString = SysCmds.getHardwareDevEUI();
	const char* hwDevEuiBuffer = hwDevEuiString.c_str();

	char hwDevEui[8];
	
	for (int i = 0; i < 8; i++)
	{
		char highNibbleStr = hwDevEuiBuffer[i * 2];
		char lowNibbleStr = hwDevEuiBuffer[(i * 2) + 1];

		hwDevEui[i] = HEX_CHAR_TO_HIGH_NIBBLE(highNibbleStr) + HEX_CHAR_TO_LOW_NIBBLE(lowNibbleStr);
		
		debugInt((int)hwDevEui[i]); debugPrint(" ");
	}
	debugPrintLn("");
	return joinNetwork((const int8_t*)hwDevEui, appEui, appKey);
}

bool OrangeForRN2483Class::joinNetwork(const int8_t* devEui, const int8_t* appEui, const int8_t* appKey)
{
	setOttaKeys(devEui, appEui, appKey);
	this->isNetworkJoined = join();
	this->isNetworkJoined ? SerialUSB.println("Join success") : SerialUSB.println("Join failed");
	return this->isNetworkJoined;
}

bool OrangeForRN2483Class::sendMessage(eTypeMessage typeMessage, int8_t* data, uint8_t size, int8_t port)
{
	if (isStreamInit()) {
		if (getJoinState()) {
			SerialUSB.println("Sending message...");
			int8_t* response = tx(typeMessage, data, size, port);

			eSuccessType successType = RnRequest.getLastSuccess();
			downlinkMessage.setResponseMessage((successType == LORA_RX) ? response : NULL);
			return (response != NULL);
		}
		else
		{
			setLastError(LORA_NETWORK_NOT_JOINED);
			return false;
		}
	}
	setLastError(LORA_NOT_INIT);
	return false;
}

DownlinkMessage* OrangeForRN2483Class::getDownlinkMessage()
{
	return &downlinkMessage;
}

bool OrangeForRN2483Class::sendMessage(int8_t* data, uint8_t size, int8_t port)
{
	return sendMessage(UNCONFIRMED_MESSAGE, data, size, port);
}

String OrangeForRN2483Class::getDevAddr()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[DEVADDR]);
	return String((response == NULL) ? "" : (char*)response);
}

bool OrangeForRN2483Class::setDevAddr(const int8_t* devAddr)
{
	return (RnRequest.rnRequest(MAC, SET, params[DEVADDR], devAddr, 4) != NULL);
}

String OrangeForRN2483Class::getDevEUI()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[DEVEUI]);
	if (response == NULL) return String("");
	return String((char*)response);
}

String OrangeForRN2483Class::getAppEUI()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[APPEUI]);
	if (response == NULL) return String("");
	return String((char*)response);
}

bool OrangeForRN2483Class::setNwkSKey(const int8_t* nwkSKey)
{
	return (RnRequest.rnRequest(MAC, SET, params[NWKS_KEY], nwkSKey, 16) != NULL);
}

eBoolean OrangeForRN2483Class::isAdr()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[ADR]);
	return (response != NULL) ? iS_ON(String((char*)response)) : BOOL_ERROR;
}

bool OrangeForRN2483Class::enableAdr(bool adr)
{
	String adrStr = adr ? STR_ON : STR_OFF;
	return (RnRequest.rnRequest(MAC, SET, params[ADR], adrStr.c_str()) != NULL);
}

bool OrangeForRN2483Class::getStatus(uint32_t& status)
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[STATUS]);

	if (response == NULL) return false;
	status = (uint32_t)String((char*)response).toInt();
	return true;
}

short OrangeForRN2483Class::getSync()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[SYNC]);
	if (response == NULL) return INT_ERROR_FAILED;
	return String((char*)response).toInt();
}

String OrangeForRN2483Class::getAutoReply()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[AUTO_REPLY]);
	return String((response == NULL) ? "" : (char*)response);
}

eDataRate OrangeForRN2483Class::getDataRate()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[DATARATE]);
	return (response != NULL) ? (eDataRate)String((char*)response).toInt() : DATA_RATE_ERROR;
}

bool OrangeForRN2483Class::setDataRate(eDataRate dataRate)
{
	if (dataRate < 0 || dataRate > COUNT_DATA_RATE - 1) return false;

	return (RnRequest.rnRequest(MAC, SET, params[DATARATE], String(dataRate).c_str()) != NULL);
}

ePowerIdx OrangeForRN2483Class::getPwrIdxValue()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[PWR_IND_VAL]);
	return (response != NULL) ? (ePowerIdx)String((char*)response).toInt() : POWER_ERROR;
}

int16_t OrangeForRN2483Class::getBand()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[BAND]);
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

int16_t OrangeForRN2483Class::getRetransNb()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[RETRANS_NB]);
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

int16_t OrangeForRN2483Class::getDemodMargin()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[DEMOD_MARGIN]);
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

int16_t OrangeForRN2483Class::getGatewayNb()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[GATEWAY_NB]);
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

int16_t OrangeForRN2483Class::getRx2(uint16_t freqBand)
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[RX2], String(freqBand).c_str());
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

int32_t OrangeForRN2483Class::getRxdelay1()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[RX_DELAY_1]);
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

int32_t OrangeForRN2483Class::getRxdelay2()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[RX_DELAY_2]);
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

int32_t OrangeForRN2483Class::getDCyclePs()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[D_CYCLE_PS]);
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

int64_t OrangeForRN2483Class::getUpctr()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[UP_CTR]);
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

bool OrangeForRN2483Class::setUpctr(uint32_t upctr)
{
	return (RnRequest.rnRequest(MAC, SET, params[UP_CTR], String(upctr).c_str()) != NULL);
}

int64_t OrangeForRN2483Class::getDwnctr()
{
	int8_t* response = RnRequest.rnRequest(MAC, GET, params[DWN_CTR]);
	return (response != NULL) ? String((char*)response).toInt() : INT_ERROR_FAILED;
}

bool OrangeForRN2483Class::setDwnctr(uint32_t dwnctr)
{
	return (RnRequest.rnRequest(MAC, SET, params[DWN_CTR], String(dwnctr).c_str()) != NULL);
}

bool OrangeForRN2483Class::setDevEUI(const int8_t* devEUI)
{
	return (RnRequest.rnRequest(MAC, SET, params[DEVEUI], devEUI, 8) != NULL);
}

bool OrangeForRN2483Class::setAppEUI(const int8_t* appEUI)
{
	return (RnRequest.rnRequest(MAC, SET, params[APPEUI], appEUI, 8) != NULL);
}

bool OrangeForRN2483Class::setAppSKey(const int8_t* appSKey)
{
	return (RnRequest.rnRequest(MAC, SET, params[APPS_KEY], appSKey, 16) != NULL);
}

bool OrangeForRN2483Class::setAppKey(const int8_t* appKey)
{
	return (RnRequest.rnRequest(MAC, SET, params[APP_KEY], appKey, 16) != NULL);
}

bool OrangeForRN2483Class::setPwrIdx(uint8_t pwrIdx)
{
	return (RnRequest.rnRequest(MAC, SET, params[PWR_IND_VAL], String(pwrIdx).c_str()) != NULL);
}

bool OrangeForRN2483Class::setBatLvl(uint8_t lvl)
{
	return (RnRequest.rnRequest(MAC, SET, params[BAT_LVL], String(lvl).c_str()) != NULL);
}

bool OrangeForRN2483Class::setRetx(uint8_t retx)
{
	return (RnRequest.rnRequest(MAC, SET, params[RETRANS_NB], String(retx).c_str()) != NULL);
}

bool OrangeForRN2483Class::setLinkCheck(uint16_t linkCheck)
{
	return (RnRequest.rnRequest(MAC, SET, params[LINK_CHECK], String(linkCheck).c_str()) != NULL);
}

bool OrangeForRN2483Class::setRxDelay1(uint16_t rxDelay1)
{
	return (RnRequest.rnRequest(MAC, SET, params[RX_DELAY_1], String(rxDelay1).c_str()) != NULL);
}

bool OrangeForRN2483Class::setAutoReply(String autoRep)
{
	return (RnRequest.rnRequest(MAC, SET, params[AUTO_REPLY], autoRep.c_str()) != NULL);
}

bool OrangeForRN2483Class::setRx2(eDataRate dataRate, uint32_t frequency)
{
	String rx2Param = String(dataRate) + SEPARATOR + String(frequency);
	return (RnRequest.rnRequest(MAC, SET, params[RX2], rx2Param.c_str()) != NULL);
}

bool OrangeForRN2483Class::setSync(int8_t syncWord)
{
	return (RnRequest.rnRequest(MAC, SET, params[SYNC], String(syncWord).c_str()) != NULL);
}

bool OrangeForRN2483Class::join()
{
	int8_t* response = RnRequest.rnRequest(MAC, params[JOIN], STR_OTAA);
	if (response == NULL) return false;

	response = RnRequest.getResponse(JOIN_TIMEOUT);
	return (response != NULL);
}

int8_t* OrangeForRN2483Class::tx(eTypeMessage typeMessage, int8_t * data, uint8_t size, int8_t port)
{
	String type = (typeMessage == CONFIRMED_MESSAGE) ? STR_CNF : STR_UNCNF;
	return RnRequest.rnUplinkRequest(type.c_str(), data, size, port);
}

bool OrangeForRN2483Class::save()
{
	return (RnRequest.rnRequest(MAC, params[SAVE]) != NULL);
}

bool OrangeForRN2483Class::pause() {
	return (RnRequest.rnRequest(MAC, params[PAUSE]) != NULL);
}

bool OrangeForRN2483Class::resume() {
	return (RnRequest.rnRequest(MAC, params[RESUME]) != NULL);
}