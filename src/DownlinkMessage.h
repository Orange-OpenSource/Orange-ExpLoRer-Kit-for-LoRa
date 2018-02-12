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
* Created:     2017-06-01 by Halim BENDIABDALLAH
* Modified:    2017-06-01 by Karim BAALI
*			   2017-10-27 by Karim BAALI
*/

/**
* @file			DownlinkMessage.h
* @brief		User's interface to access to the received data
* @details		This class contains all the necessary methods to be able to use and manipulate
*				the data sent by the server after an uplink transmission.
*/

#ifndef _DOWNLINK_MESSAGE_H
#define _DOWNLINK_MESSAGE_H

#include "InternalConstForRN2483.h"
#include <Arduino.h>

class DownlinkMessage
{
private:
	uint8_t port;
	uint8_t receiveBuffer[DEFAULT_INPUT_BUFFER_SIZE];	
	uint8_t arrayMessage[DEFAULT_INPUT_BUFFER_SIZE / 2];
protected:
	void setPort(uint8_t port);
	void setResponseMessage(uint8_t* message);
public:
	friend class OrangeForRN2483Class;

	/**
	* @brief		Constructor for the DownlinkMessage class
	* @details		Used to instanciate a new DownlinkMessage object
	*/
	DownlinkMessage();

	/**
	* @brief		Destructor for the DownlinkMessage class
	* @details		Used to delete an DownlinkMessage instance
	*/
	~DownlinkMessage();

	/**
	* @brief		Getter for the \e port class attribute
	* @details		This function allows the user to have access to the port attribute
	* @return		Decimal number corresponding to the port attribute value
	*/
	uint8_t getPort();

	/**
	* @brief		Getter for the \e receiveBuffer class attribute as a string value
	* @details		This function allows the user to have access to the receiveBuffer attribute
	*				corresponding to the data sent by the server as a string value
	* @return		String value corresponding to the receiveBuffer attribute value
	*/
	const String getMessage();

	/**
	* @brief		Getter for the \e receiveBuffer class attribute as a byte array
	* @details		This function allows the user to have access to the receiveBuffer attribute
	*				corresponding to the data sent by the server as a byte array
	* @param		len		Pointer on an uint8_t value to receive the message length value
	* @return		Byte array corresponding to the receiveBuffer attribute value
	*/
	const uint8_t* getMessageByteArray(int8_t* len);
};
#endif