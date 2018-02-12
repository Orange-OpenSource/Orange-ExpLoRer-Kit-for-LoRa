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
*			   2017-10-27 by Karim BAALI
*/


#include "DownlinkMessage.h"

DownlinkMessage::DownlinkMessage() {
	this->port = 0;
	this->receiveBuffer[0] = '\0';
}

DownlinkMessage::~DownlinkMessage()
{

}

void DownlinkMessage::setPort(uint8_t port)
{
	this->port = port;
}

void DownlinkMessage::setResponseMessage(uint8_t* message)
{
	if (message == NULL)
	{
		receiveBuffer[0] = '\0';
		this->port = 0;
		return;
	}

	String msg_str = String((char*)message);
	int first_idx = msg_str.indexOf(" ");
	String msgType = msg_str.substring(0, first_idx);
	int second_idx = msg_str.indexOf(" ", first_idx+1);
	String port = msg_str.substring(first_idx+1, second_idx);
	String msg = msg_str.substring(second_idx+1, msg_str.length());

	setPort(port.toInt());
	strcpy((char*)receiveBuffer, msg.c_str());
}

uint8_t DownlinkMessage::getPort(){
	return this->port;
}

const String DownlinkMessage::getMessage() {
	const String msg = String((char*)receiveBuffer);
	if (msg == NULL) {
		SerialUSB.println("Response with empty payload");
	}
	return msg;
}

const uint8_t* DownlinkMessage::getMessageByteArray(int8_t* len) {
	*len = (int8_t) strlen((char*)receiveBuffer);

	if (*len == 0) {
		SerialUSB.println("Response with empty payload");
		return NULL;
	}

	for (int i = 0; i < *len; i++)
	{
		char highNibbleStr = receiveBuffer[i * 2];
		char lowNibbleStr = receiveBuffer[(i * 2) + 1];

		arrayMessage[i] = HEX_CHAR_TO_HIGH_NIBBLE(highNibbleStr) + HEX_CHAR_TO_LOW_NIBBLE(lowNibbleStr);

		debugInt((int)arrayMessage[i]); debugPrint(" ");
	}
	*len /= 2;
	return arrayMessage;
}