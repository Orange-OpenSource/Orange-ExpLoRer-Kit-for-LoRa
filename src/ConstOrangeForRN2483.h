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
*			   2017-05-09 by Karim BAALI
*/

/**
* @file        constOrangeForRN2483.h
* @brief       Defines all the constant values used in the project.
* @details     This file defines all the constant variables and functions used in this project
*/

#ifndef _CONST_ORANGE_FOR_RN2483_H
#define _CONST_ORANGE_FOR_RN2483_H


/**
* @brief     Different values for the \b confirmer \b message parameter
* @details   Each of these values is used to guide the user when trying to send a message with
*			 a confirmed or unconfirmed message
*/
typedef enum _typeMessage {
	UNCONFIRMED_MESSAGE = 0,
	CONFIRMED_MESSAGE
}eTypeMessage;

/**
* @brief     Different values for the \b datarate attribute
* @details   Each of these values is used to guide the user when trying to set the datarate value
*/
typedef enum _dataRate {
	DATA_RATE_0 = 0,
	DATA_RATE_1,
	DATA_RATE_2,
	DATA_RATE_3,
	DATA_RATE_4,
	DATA_RATE_5,
	DATA_RATE_6,
	DATA_RATE_7,
	COUNT_DATA_RATE,
	DATA_RATE_ERROR = -1
}eDataRate;

/**
* @brief     Different values for the \b power \b index attribute
* @details   Each of these values is used to guide the user when trying to set the power index value
*/
typedef enum _ePowerIdx {
	POWER_0 = 0,
	POWER_1,
	POWER_2,
	POWER_3,
	POWER_4,
	POWER_5,
	COUNT_POWER,
	POWER_ERROR = -1
}ePowerIdx;

/**
* @brief     Different values for the \b data \b shaping \b value applied to FSK transmissions
* @details   Each of these values is used to guide the user when trying to set the data shaping value applied to FSK transmissions
*/
typedef enum _eBT
{
	BT_NONE = 0,
	BT_1_0,
	BT_0_5,
	BT_0_3,
	BT_COUNT,
	BT_ERROR = -1
}eBT;

/**
* @brief     Different values for a \b boolean value
* @details   Each of these values is used to guide the user when trying to set an attribute to true or false
*/
typedef enum _eBoolean
{
	BOOL_FALSE = 0,
	BOOL_TRUE,
	BOOL_ERROR = -1

}eBoolean;

/**
* @brief     Different values for the \b modulation \b type attribute
* @details   Each of these values is used to guide the user when trying to set the modulation type value
*/
typedef enum _eModulation 
{
	FSK_MODULATION = 0,
	LORA_MODULATION,
	GET_MODULATION_ERROR = -1
}eModulation;

/**
* @brief     Different values for the \b coding \b rate attribute
* @details   Each of these values is used to guide the user when trying to set the coding rate value
*/
typedef enum _eCodingRate
{
	CR_4_5 = 0,
	CR_4_6,
	CR_4_7,
	CR_4_8,
	CR_ERROR = -1
}eCodingRate;

/**
* @brief     Different values for the \b spreading \b factor attribute
* @details   Each of these values is used to guide the user when trying to set the spreading factor value
*/
typedef enum _eSpreadingFactor
{
	SF7 = 7,
	SF8,
	SF9,
	SF10,
	SF11,
	SF12,
	SF_COUNT,
	SF_ERROR = -1
}eSpreadingFactor;


/**
* @brief     Different kind of error which could be encountered
* @details   Each of these values is used to find the correct string value in the \e possibleResponses attribute of the OrangeForRn2483 class
*			 and other error cases
*/
typedef enum _eErrorType {		
	LORA_SUCCESS = 0,
	LORA_INVALID_PARAM,						// The used parameters doesn't correspond to expected ones
	LORA_KEYS_NOT_INIT,						// Mandatory keys for a join request were not initialized before
	LORA_NO_FREE_CH,						// All free chanels are busy while sending a join request
	LORA_SILENT,							// The device is in a Silent Immediately state while sending a join request
	LORA_BUSY,								// MAC state isn't in an idle state
	LORA_MAC_PAUSED,						// MAC was paused but not resumed back 
	LORA_JOIN_DENIED,						// The join procedure was unsuccessful 
	LORA_INVALID_DATA_LEN,					// Application payload length is greater than the maximum allowed by the current data rate
	LORA_ERR_FRAME_CNTR_ERR_REJOIN_NEEDED,	// The frame counter rolled over
	LORA_COUNT_ERRORS,						// Error counter
	LORA_NOT_INIT,							// The lora stream was not initialized
	LORA_NETWORK_NOT_JOINED,				// Failed to join the network
	LORA_TIMEOUT,							// A timeout occured while waiting a response
	LORA_SLEEP,								// The LoRa module is currently sleeping
}eErrorType;

#endif

