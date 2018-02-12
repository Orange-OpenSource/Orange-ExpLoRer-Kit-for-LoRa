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

/*!
 * @mainpage OrangeForRN2483
 * @version 1.0.5
 * @author Karim Baali
 */


/**
* @file			orangeForRN2483.h
* @brief		User's main interface to use the module        
* @details		This class contains all the necessary methods to be able to easily use
*				the Sodaq RN2483 module
*/

#ifndef _ORANGEFORRN2483_H
#define _ORANGEFORRN2483_H

#include <Arduino.h>

#include "InternalConstForRN2483.h"
#include "ConstOrangeForRN2483.h"
#include "RadioCmds.h"
#include "SysCmds.h"
#include "LpwaOrangeEncoder.h"
#include "RnRequest.h"
#include "DownlinkMessage.h"

class OrangeForRN2483Class
{
protected:	
	RadioCmdsClass RadioCmds;
	SysCmdsClass SysCmds;
	DownlinkMessage downlinkMessage;	

	Stream* diagStream;
	bool isNetworkJoined;
	bool deepSleeping;
	bool exitSleepMode;

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
	const char* possibleResponses[LORA_COUNT_ERRORS] = { "ok"
													"invalid_param",
													"keys_not_init",
													"no_free_ch",
													"silent",
													"busy",
													"mac_paused",
													"denied",
													"invalid_data_len",
													"frame_counter_err_rejoin_needed"}; 
	bool isStreamInit();
	
	uint8_t* tx(eTypeMessage typeMessage, uint8_t * data, uint8_t size, uint8_t port);


	void setLastError(eErrorType errorType);

	bool setOttaKeys(const uint8_t* devEui, const uint8_t* appEui, const uint8_t* appKey);

	void resetDevice();

public:
	static OrangeForRN2483Class* refOrangeForRN2483;

	void onAlarmInterrupt();

	/**
	* @brief		Constructor for the OrangeForRN2483Class class
	* @details		Used to instanciate a new OrangeForRN2483Class object
	*/
	OrangeForRN2483Class();

	/**
	* @brief		Destructor for the OrangeForRN2483Class class
	* @details		Used to delete an OrangeForRN2483Class instance
	*/
	virtual ~OrangeForRN2483Class();

	/**
	* @brief		Initializing the lorastream attribute
	* @details		This function is used to initialize the lorastream with UART stream
	*/
	void init();

	/**
	* @brief		Getter for the \e isNetworkJoined class attribute
	* @details		This function allows the user to have access to the isNetworkJoined attribute
	* @return		Boolean corresponding to the attribute value
	*/
	bool getJoinState();

	/**
	* @brief		Setting the mandatory keys for a join request
	* @details		This function allows the user to set the different kind of \b keys \b needed to be able to 
	*				send an ABP join request to the server.
	* @param		nwkSkey		Hexadecimal number represented by an array whose size is \b 16 int8_t
	* @param		appSKey		Hexadecimal number represented by an array whose size is \b 16 int8_t
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setAbpKeys(const uint8_t* nwkSkey, const uint8_t* appSKey);

	/**
	* @brief		Sending a join request to the server
	* @details		This function allows the user to send a \e join \e request to the server
	* @param		devEUI		Hexadecimal number represented by an array whose size is \b 8 int8_t
	* @param		appEUI		Hexadecimal number represented by an array whose size is \b 8 int8_t
	* @param		appKey		Hexadecimal number represented by an array whose size is \b 16 int8_t
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool joinNetwork(const uint8_t* devEUI, const uint8_t* appEUI, const uint8_t* appKey);

	/**
	* @brief		Sending a join request to the server with HWEUI by default
	* @details		This function allows the user to send a \e join \e request to the server with the 
	*				hardware devEUI (HWEUI) used by default
	* @param		appEUI		Hexadecimal number represented by an array whose size is \b 8 int8_t
	* @param		appKey		Hexadecimal number represented by an array whose size is \b 16 int8_t
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool joinNetwork(const uint8_t* appEUI, const uint8_t* appKey);

	/**
	* @brief		Sending data to the server 
	* @details		This function allows the user to \b send \b data to the server by giving 
	*				the data, the size the port to use
	* @param		typeMessage		eTypeMessage value representing the uplink payload type (\e CONFIRMED_MESSAGE or \e UNCONFIRMED_MESSAGE)
	* @param		data		Hexadecimal value representing the data sent to the server
	* @param		size		Unsigned integer value representing the size of the transmitted data only
	* @param		port		Integer value representing the port to use
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool sendMessage(eTypeMessage typeMessage, uint8_t* data, uint8_t size, uint8_t port);

	/**
	* @brief		Sending data to the server
	* @details		This function allows the user to \b send \b data to the server by giving
	*				the data, the size the port to use. An unconfirmed message is sent by default by calling previous method
	* @param		data		Hexadecimal value representing the data sent to the server
	* @param		size		Unsigned integer value representing the size of the transmitted data only
	* @param		port		Integer value representing the port to use
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool sendMessage(uint8_t* data, uint8_t size, uint8_t port);

	/**
	* @brief		Getter for DownlinkMessage attribute
	* @details		This function allows the user to have access to the methods available in the DownlinkMessage object
	* @return		Pointer on the attribute
	*/
	DownlinkMessage* getDownlinkMessage();

	/**
	* @brief		Getter for RadioCmds attribute
	* @details		This function allows the user to have access to the radio commands available in the RadioCmds object
	* @return		Pointer on the attribute
	*/
	RadioCmdsClass* getRadioCmds();

	/**
	* @brief		Getter for SysCmds attribute
	* @details		This function allows the user to have access to the system commands available in the SysCmds object
	* @return		Pointer on the attribute
	*/
	SysCmdsClass* getSysCmds();


	/**
	* @brief		Getter for the last saved error
	* @details		This function allows the user to have access to the value of the last saved error
	* @return		\e eErrorType value corresponding to the last error found (see constOrangeForRn2483.h for more information)
	*/
	eErrorType getLastError();

	/**
	* @brief		Getter on the device address
	* @details		This function allows the user to have access to the \b device \b address by
	*				executing a "mac get devaddr" command on the module
	* @return		The received device address as a \e string value
	*/
	String getDevAddr();

	/**
	* @brief		Getter on the device EUI
	* @details		This function allows the user to have access to the unique \b device \b EUI
	*				identifier by executing a "mac get deveui" command on the module
	* @return		The received device EUI as a \e string value
	*/
	String getDevEUI();

	/**
	* @brief		Getter on the application EUI
	* @details		This function allows the user to have access to the \b application \b EUI
	*				identifier by executing a "mac get appeui" command on the module
	* @return		The received application EUI as a \e string value
	*/
	String getAppEUI();

	/**
	* @brief		Getter on the adaptive data rate mechanism
	* @details		This function allows the user to have access to the \b adaptive \b data \b rate
	*				by executing a "mac get adr" command on the module
	* @return		The received value as an \e eBoolean value (see constOrangeForRn2483.h for more information)
	*/
	eBoolean isAdr();

	/**
	* @brief		Setter for the adaptive data rate value
	* @details		This function allows the user to set or update the \b adaptive \b data \b rate (ADR)
	*				by executing a "mac set adr <adr>" command on the module
	* @param		adr			Boolean value enabling or not the adaptive data rate
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool enableAdr(bool adr = true);

	/**
	* @brief		Getter on the current status of the module
	* @details		This function allows the user to have access to the \b module \b status
	*				by executing a "mac get status" command on the module
	* @param		status		uint32_t variable to store the received status from the module
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool getStatus(uint32_t& status);

	/**
	* @brief		Getter on the synchronization word
	* @details		This function allows the user to have access to the \b synchronization \b word
	*				by executing a "mac get sync" command on the module
	* @return		The received value as a \e short value
	*/
	short getSync();

	/**
	* @brief		Getter on the state of the automatic reply
	* @details		This function allows the user to have access to the \b state of the \b automatic
	*				\b reply by executing a "mac get ar" command on the module
	* @return		The received value as a \e string value, either \b on or \b off
	*/
	String getAutoReply();

	/**
	* @brief		Getter on the data rate of the module
	* @details		This function allows the user to have access to the \b data \b rate
	*				by executing a "mac get dr" command on the module
	* @return		The received value as an \e eDataRate value (see constOrangeForRn2483.h for more information)
	*/
	eDataRate getDataRate();

	/**
	* @brief		Getter on the output power index value
	* @details		This function allows the user to have access to the \b output \b power
	*				\b index \b value by executing a "mac get pwridx" command on the module
	* @return		The received value as an \e ePowerIdx value (see constOrangeForRn2483.h for more information)
	*/
	ePowerIdx getPwrIdxValue();

	/**
	* @brief		Getter on the frequency band
	* @details		This function allows the user to have access to the \b frequency \b band
	*				by executing a "mac get band" command on the module
	* @return		The received value as a \e decimal \e number, either 868 or 433
	*/
	uint16_t getBand();

	/**
	* @brief		Getter on the number of retransmissions
	* @details		This function allows the user to have access to the \b number \b of \b retransmissions
	*				by executing a "mac get retx" command on the module
	* @return		The received value as a \e decimal \e number, from 0 to 255
	*/
	uint16_t getRetransNb();

	/**
	* @brief		Getter on the demodulation margin
	* @details		This function allows the user to have access to the \b demodulation \b margin
	*				by executing a "mac get mrgn" command on the module
	* @return		The received value as a \e decimal \e number, from 0 to 255
	*/
	uint16_t getDemodMargin();

	/**
	* @brief		Getter on the number of gateways
	* @details		This function allows the user to have access to the \b number \b of \b gateways
	*				by executing a "mac get gwnb" command on the module
	* @return		The received value as a \e decimal \e number, from 0 to 255
	*/
	uint16_t getGatewayNb();

	/**
	* @brief		Getter on the data rate configured for the second receive window
	* @details		This function allows the user to have access to the \b data \b rate for the second
	*				receive window by executing a "mac get rx2 <freqBand>" command on the module
	* @param		freqBand		Decimal number representing the frequency band
	* @return		The received value as a \e decimal \e number
	*/
	uint16_t getRx2(uint16_t freqBand);

	/**
	* @brief		Getter on the interval for rxdelay1
	* @details		This function allows the user to have access to the \b interval \b for \b rxdelay1
	*				by executing a "mac get rxdelay1" command on the module
	* @return		The received value as a \e decimal \e number, from 0 to 65535
	*/
	uint32_t getRxdelay1();

	/**
	* @brief		Getter on the interval for rxdelay2
	* @details		This function allows the user to have access to the \b interval \b for \b rxdelay2
	*				by executing a "mac get rxdelay2" command on the module
	* @return		The received value as a \e decimal \e number, from 0 to 65535
	*/
	uint32_t getRxdelay2();

	/**
	* @brief		Getter on the duty cycle prescaler value
	* @details		This function allows the user to have access to the duty cycle \b prescaler \b value
	*				by executing a "mac get dcycleps" command on the module
	* @return		The received value as a \e decimal \e number, from 0 to 65535
	*/
	uint32_t getDCyclePs();

	/**
	* @brief		Getter on the uplink frame counter
	* @details		This function allows the user to have access to the \b uplink \b frame \b counter
	*				by executing a "mac get upctr" command on the module
	* @return		The received value as a \e decimal \e number, from 0 to 4294967295
	*/
	uint64_t getUpctr();

	/**
	* @brief		Getter on the downlink frame counter
	* @details		This function allows the user to have access to the \b downlink \b frame \b counter
	*				by executing a "mac get dnctr" command on the module
	* @return		The received value as a \e decimal \e number, from 0 to 4294967295
	*/
	uint64_t getDwnctr();


	/**
	* @brief		Setter for the device address
	* @details		This function allows the user to set or update the \b device \b address
	*				by executing a "mac set devaddr <devAddr>" command on the module
	* @param		devAddr		Hexadecimal number represented by an array whose size is \b 4 int8_t
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setDevAddr(const uint8_t* devAddr);

	/**
	* @brief		Setter for the device EUI
	* @details		This function allows the user to set or update the \b device \b EUI \b identifier
	*				by executing a "mac set deveui <devEUI>" command on the module
	* @param		devEUI		Hexadecimal number represented by an array whose size is \b 8 int8_t
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setDevEUI(const uint8_t* devEUI);

	/**
	* @brief		Setter for the application EUI
	* @details		This function allows the user to set or update the \b application \b EUI \b identifier
	*				by executing a "mac set appeui <appEUI>" command on the module
	* @param		appEUI		Hexadecimal number represented by an array whose size is \b 8 int8_t
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setAppEUI(const uint8_t* appEUI);

	/**
	* @brief		Setter for the network session key
	* @details		This function allows the user to set or update the \b network \b session \b key
	*				by executing a "mac set nwkskey <nwkSKey>" command on the module
	* @param		nwkSKey			Hexadecimal number represented by an array whose size is \b 16 int8_t
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setNwkSKey(const uint8_t* nwkSKey);

	/**
	* @brief		Setter for the application session key
	* @details		This function allows the user to set or update the \b application \b session \b key
	*				by executing a "mac set appskey <appSessionKey>" command on the module
	* @param		appSKey		Hexadecimal number represented by an array whose size is \b 16 int8_t
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setAppSKey(const uint8_t* appSKey);

	/**
	* @brief		Setter for the application key
	* @details		This function allows the user to set or update the \b application \b key
	*				by executing a "mac set appkey <appKey>" command on the module
	* @param		appKey		Hexadecimal number represented by an array whose size is \b 16 int8_t
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setAppKey(const uint8_t* appKey);

	/**
	* @brief		Setter for the power index value
	* @details		This function allows the user to set or update the \b power \b index \b value
	*				by executing a "mac set pwridx <pwrIdx>" command on the module
	* @param		pwrIdx		Decimal number representing the index value for the output power
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setPwrIdx(uint8_t pwrIdx);

	/**
	* @brief		Setter for the data rate value
	* @details		This function allows the user to set or update the \b data \b rate \b value
	*				by executing a "mac set dr <dataRate>" command on the module
	* @param		dataRate		eDataRate value representing the data rate value (see constOrangeForRn2483.h for more information)
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setDataRate(eDataRate dataRate);

	/**
	* @brief		Setter for the battery level value
	* @details		This function allows the user to set or update the \b battery \b level \b value
	*				by executing a "mac set bat <lvl>" command on the module
	* @param		lvl			Decimal number representing the battery level, from 0 to 255
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setBatLvl(uint8_t lvl);

	/**
	* @brief		Setter for the number of retransmissions for an uplink confirmed packet
	* @details		This function allows the user to set or update the \b number \b of \b retransmissions
	*				for an uplink confirmed packet by executing a "mac set retx <retx>" command on the module
	* @param		retx		Decimal number representing the number of retransmissions, from 0 to 255
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setRetx(uint8_t retx);

	/**
	* @brief		Setter for the link check process interval
	* @details		This function allows the user to set or update the link check process \b interval
	*				by executing a "mac set linkchk <linkCheck>" command on the module
	* @param		linkCheck		Decimal number representing the interval for the link check process, from 0 to 65535
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setLinkCheck(uint16_t linkCheck);

	/**
	* @brief		Setter for the delay between the transmission and the first reception window
	* @details		This function allows the user to set or update the \b delay between the transmission and the first
	*				reception window by executing a "mac set rxdelay1 <rxDelay1>" command on the module
	* @param		rxDelay1		Decimal number representing the delay in milliseconds, from 0 to 65535
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setRxDelay1(uint16_t rxDelay1);

	/**
	* @brief		Setter for the auto reply state
	* @details		This function allows the user to set or update the \b state \b of \b the \b automatic \b reply
	*				by executing a "mac set ar <autoRep>" command on the module
	* @param		autoRep			String value enabling or not the automatic reply (\e on or \e off)
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setAutoReply(String autoRep);

	/**
	* @brief		Setter for the data rate and frequency used for the second receive window
	* @details		This function allows the user to set or update the \b data \b rate and the \b frequency used
	*				for the second receive window by executing a "mac set rx2 <dataRate> <frequency>" command on the module
	* @param		dataRate		eDataRate value representing the data rate value (see constOrangeForRn2483.h for more information)
	* @param		frequency		Decimal number representing the frequency value, 863000000 to 870000000 or from 433050000 to 434790000
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setRx2(eDataRate dataRate, uint32_t frequency);

	/**
	* @brief		Setter for the synchronization word
	* @details		This function allows the user to set or update the \b synchronization \b word for the
	*				LoRaWAN communication by executing a "mac set sync <syncWord>" command on the module
	* @param		syncWord		Decimal number representing the synchronization word
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setSync(int8_t syncWord);

	/**
	* @briSetter for the uplink frame counter
	* @details		This function allows the user to set or update the \b uplink \b frame \b counter used for
	*				the next uplink transmission by executing a "mac set upctr <upctr>" command on the module
	* @param		upctr		Decimal number representing the uplink frame counter, from 0 to 4294967295
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setUpctr(uint32_t upctr);

	/**
	* @brief		Setter for the downlink frame counter
	* @details		This function allows the user to set or update the \b downlink \b frame \b counter used for
	*				the next uplink transmission by executing a "mac set dnctr <dwnctr>" command on the module
	* @param		dwnctr		Decimal number representing the downlink frame counter, from 0 to 4294967295
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool setDwnctr(uint32_t dwnctr);


	/**
	* @brief		Send a request to authenticate with the network
	* @details		This function allows the user to send a \b join \b request to the server
	*				by executing a "mac join <mode>" command on the module
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool join();

	/**
	* @brief		Save configuration parameters to the user EEPROM
	* @details		This function allows the user to save the \b configuration \b parameters to the user EEPROM,
	*				allowing the module to be initialized with the last saved information avec a reset
	*				by executing a "mac save" command on the module
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool save();

	/**
	* @brief		Pause the LoRaWAN stack functionality
	* @details		This function allows the user to pause the \b LoRaWAN \b stack \e functionality to
	*				allow transceiver configuration	by executing a "mac pause" command on the module
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool pause();

	/**
	* @brief		Resume the LoRaWAN stack functionality
	* @details		This function allows the user to resume the \b LoRaWAN \b stack \e functionality after
	*				being paused by executing a "mac resume" command on the module
	* @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	*/
	bool resume();	

	/**
	* @brief            Put the Sodaq Explorer in deepsleep mode
	* @details         This function allows the user to put the RN2483 module and the processor in sleep mode for a given
	*                       amount of time.
	* @param         hours               Decimal number representing hour component for sleeping time
	* @param         minutes            Decimal number representing minute component for sleeping time
	* @param         seconds           Decimal number representing second component for sleeping time
	*/
	void deepSleep(uint8_t hours, uint8_t minutes, uint8_t seconds);

	/**
	* @brief            Check if the Sodaq Explorer is in deepsleep mode or not
	* @details         This function allows the user to check if the Sodaq Explorer is currently in a deepsleep mode or not.
	* @return           Boolean value corresponding to the current state.
	*/
	bool isDeepSleeping();

};

extern OrangeForRN2483Class OrangeForRN2483;

#endif

