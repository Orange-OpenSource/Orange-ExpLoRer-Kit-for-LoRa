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
* Created:     2017-05-03 by Halim BENDIABDALLAH
* Modified:	   2017-10-27 by Karim BAALI
*/

/**
* @file			RnRequest.h
* @brief		Main methods used by the library to communicate with the module
* @details		This class contains all the necessary methods to be able to easily communicate
*				the Sodaq RN2483 module
*/

#ifndef _RN_REQUEST_H
#define _RN_REQUEST_H

#include <Arduino.h>

#include "InternalConstForRN2483.h"
#include "ConstOrangeForRN2483.h"

#if defined(ARDUINO_ARCH_AVR)
typedef HardwareSerial SerialType;
#define ENABLE_SLEEP
#elif defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD)
typedef Uart SerialType;
#define ENABLE_SLEEP
#else
typedef Stream SerialType;
#endif

/**
* \brief     Different kind of commands which could be sent to the Rn2483 module
* \details   Each of these values is used to find the correct string value in the \e commandType attribute of the class
*/
typedef enum _typecmd {
	MAC = 0,
	SYS,
	RADIO,
	COUNT_TYPE
}eTypeCommand;

/**
* \brief     Different kind of MAC commands
* \details   Each of these values is used to find the correct string value in the \e params attribute of the class
*/
typedef enum _paramMac {
	DEVADDR = 0,
	DEVEUI,
	APPEUI,
	BAND,
	DATARATE,
	PWR_IND_VAL,
	ADR,
	RETRANS_NB,
	RX_DELAY_1,
	RX_DELAY_2,
	AUTO_REPLY,
	RX2,
	D_CYCLE_PS,
	DEMOD_MARGIN,
	GATEWAY_NB,
	STATUS,
	SYNC,
	UP_CTR,
	DWN_CTR,
	NWKS_KEY,
	APPS_KEY,
	APP_KEY,
	JOIN,
	TX_MAC,
	BAT_LVL,
	LINK_CHECK,
	SAVE,
	PAUSE,
	RESUME,
	COUNT_PARAM_MAC
}eParamMac;

/**
* \brief     Different kind of success message
* \details   Each of these values is used to find the correct string value in the \e successResponses attribute of the class
*/
typedef enum _eSuccessType {
	LORA_OK = 0,
	LORA_MAC_TX_OK,
	LORA_ACCEPTED,
	LORA_RX,
	LORA_COUNT_SUCCESS,
	LORA_FAILED,
}eSuccessType;

class RnRequestClass
{
public:
	friend class OrangeForRN2483Class;
	friend class RadioCmdsClass;
	friend class SysCmdsClass;

protected:
	SerialType* loraStream;

	uint8_t receiveBuffer[DEFAULT_INPUT_BUFFER_SIZE];
	eSuccessType successType;
	eErrorType errorType;
	bool isAsleep;

	const char* params[COUNT_PARAM_MAC] = {
		"devaddr",
		"deveui",
		"appeui",
		"band",
		"dr",
		"pwridx",
		"adr",
		"retx",
		"rxdelay1",
		"rxdelay2",
		"ar",
		"rx2",
		"dcycleps",
		"mrgn",
		"gwnb",
		"status",
		"sync",
		"upctr",
		"dnctr",
		"nwkskey",
		"appskey",
		"appkey",
		"join",
		"tx",
		"bat",
		"linkchk",
		"save",
		"pause",
		"resume"
	};

	const char* commandType[COUNT_TYPE] = { "mac", "sys", "radio" };

	const char* successResponses[LORA_COUNT_SUCCESS] = { "ok",
		"mac_tx_ok",
		"accepted",
		"mac_rx"
	};

	const char* possibleResponses[LORA_COUNT_ERRORS] = {"invalid_param",
		"keys_not_init",
		"no_free_ch",
		"silent",
		"busy",
		"mac_paused",
		"denied",
		"invalid_data_len",
		"frame_counter_err_rejoin_needed"
	};

	uint16_t getReceivedData();

	uint16_t readLn(uint8_t* buffer, uint16_t size);

	eErrorType checkErrors(uint8_t* resp);

	bool isStreamInit();

	void init();

	bool writeHexString(const uint8_t* paramValue, uint8_t lenParamValue);
	bool cmdRequest(uint8_t type, const char* command, const char* paramName);

	uint8_t* rnRequest(uint8_t type, const char* command, const char* paramName, const uint8_t* paramValue, uint8_t lenParamValue);
	uint8_t* rnUplinkRequest(const char* paramName, const uint8_t* paramValue, uint8_t lenParamValue, uint8_t port);
	uint8_t* rnRequest(uint8_t type, const char* command, const char* paramName = NULL, const char* paramValues = NULL);

	uint32_t getTimeoutDelay(const char* command);
	uint8_t* getResponse(uint32_t timeout = DEFAULT_TIMEOUT);
	
	eSuccessType getLastSuccess();
	eErrorType getLastError();
	void setLastError(eErrorType errorType);
	
	eSuccessType checkSuccess(uint8_t* resp);
	bool checkIsAsleep();
	void setBreakCondition();
	void setWakeupFlag();
public:
	/**
	* @brief		Constructor for the RnRequestClass class
	* @details		Used to instanciate a new RnRequestClass object
	*/
	RnRequestClass();

	/**
	* @brief		Destructor for the RnRequestClass class
	* @details		Used to delete an RnRequestClass instance
	*/
	virtual ~RnRequestClass();
};

extern RnRequestClass RnRequest;

#endif

