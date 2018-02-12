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

/**
* @file			sysCmds.h
* @brief		Contains all the SYS commands.
* @details		This class defines all the SYS commands available for the user : getters, setters
*				or other specific commands such as sleep.
*/

#ifndef _SYSCMDS_H
#define _SYSCMDS_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

/**
* @brief     Different kind of SYS commands
* @details   Each of these values is used to find the correct string value in the \e params attribute of the class
*/
typedef enum _paramSys {
	VERSION = 0,
	NVM,
	VDD,
	PIN_DIG,
	PIN_ANA,
	PIN_MODE,
	HWEUI,
	SLEEP,
	RESET,
	COUNT_PARAM_SYS
}eParamSys;


class SysCmdsClass
{
 protected:
	 const char* params[COUNT_PARAM_SYS] = {
		 "ver",
		 "nvm",
		 "vdd",
		 "pindig",
		 "pinana",
		 "pinmode",
		 "hweui",
		 "sleep",
		 "reset",
	 };
 public:

	 /**
	 * @brief		Getter on the firmware version of the device
	 * @details		This function allows the user to have access to the \b firmware \b version of the device by
	 *				executing a "sys get ver" command on the module
	 * @return		The received firmware version as a \e string value
	 */
	 String getVersion();
	
	 /**
	 * @brief		Getter on the data stored in the user EEPROM of the module
	 * @details		This function allows the user to have access to the \b data \b stored in the \b user \b EEPROM
	 *				of the device by executing a "sys get vnm <address>" command on the module
	 * @param		address			Hexadecimal number represented by an array whose size is \b 2 int8_t
	 * @return		The received hexadecimal data stored at the address as a \e string value
	 */
	 String getNvm(uint8_t address[2]);

	 /**
	 * @brief		Setter for the data stored in the user EEPROM of the module
	 * @details		This function allows the user to set or update the \b data \b stored \b in \b the \b user \b EEPROM
	 *				used for by executing a "sys set nvm <address> <data>" command on the module
	 * @param		address		Hexadecimal number representing the user EEPROM address, from 300 to 3FF
	 * @param		data		Hexadecimal number representing the data to be stored at this address, from 00 to FF
	 * @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	 */
	 bool setNvm(uint8_t address[2], uint8_t data[1]);

	 /**
	 * @brief		Getter on the preprogrammed EUI address of the device
	 * @details		This function allows the user to have access to the \b preprogrammed \b EUI \b address of 
	 *				the device by executing a "sys get hweui" command on the module
	 * @return		The received DevEUI address as a \e string value
	 */
	 String getHardwareDevEUI();

	 /**
	 * @brief		Getter on the state of a specified digital input
	 * @details		This function allows the user to have access to the \b state \b of \b a \b digital \b input
	 *				of the device by executing a "sys get pindig <pinname>" command on the module
	 * @param		pinname			String value representing the name of the digital input
	 * @return		The received state as a \e string value, either 0 or 1
	 */
	 String getPindig(String pinname);

	 /**
	 * @brief		Setter for the state of a specified pin
	 * @details		This function allows the user to set or update the \b state of a pin
	 *				by executing a "sys set pinstate <pinname> <pinstate>" command on the module
	 * @param		pinname			String value representing the pin name ("GPIO0", "GPIO13", "UART_CTS", "UART_RTS")
	 * @param		pinstate		Decimal number representing the state (\e 0 or \e 1)
	 * @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	 */
	 bool setPinDig(String pinname, String pinstate);

	 /**
	 * @brief		Getter on the state of a specified analog input
	 * @details		This function allows the user to have access to the \b state \b of \b a \b analog \b input
	 *				of the device by executing a "sys get pinana <pinname>" command on the module
	 * @param		pinname			String value representing the name of the analog input
	 * @return		The received state as a \e string value, from 0 to 1023
	 */
	 String getPinana(String pinname);

	 /**
	 * @brief		Getter on the Vdd value measured for the module
	 * @details		This function allows the user to have access to an \b ADC \b converted \b value of
	 *				Vdd measure by executing a "sys get vdd" command on the module
	 * @return		The received converted value as a \e decimal value
	 */
	 int16_t getVdd();

	 /**
	 * @brief		Setter for the function of a specified pin
	 * @details		This function allows the user to set or update the \b function of a pin
	 *				by executing a "sys set pinmode <pinname> <pinfunc>" command on the module
	 * @param		pinname		String value representing the pin name ("GPIO0", "GPIO13", "UART_CTS", "UART_RTS")
	 * @param		pinfunc		String value representing the function of a pin ("digin", "digout", "ana")
	 * @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	 */
	 bool setPinMode(String pinname, String pinfunc);

	 /**
	 * @brief		Put the system to sleep mode for a specified number of milliseconds
	 * @details		This function allows the user to put the module in a \b sleep \b mode  for a specified
	 *				number of milliseconds by executing a "sys sleep <delay>" command on the module
	 * @param		delay		Decimal number representing the number of milliseconds
	 * @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	 */
	 bool sleep(uint32_t delay);

	 /**
	 * @brief		Getter for the current state (sleeping or not) of the RN2483 module
	 * @details		This function allows the user to know if the LoRa module is currently in sleeping mode or not
	 * @return		Boolean value, true if sleeping mode is active, false either
	 */
	 bool isAsleep();

	 /**
	 * @brief		Reset and restart the RN2483 module and return firmware version
	 * @details		This function allows the user to \b reset and \b restart the RN2483 module
	 *				and returns the current firmware information.
	 * @return		String value corresponding to the received firmware information 
	 */
	 String reset();

	 void wakeUp();
};

#endif

