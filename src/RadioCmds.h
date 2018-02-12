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
* @file			radioCmds.h
* @brief		Contains all the RADIO commands.
* @details		This class defines all the RADIO commands available for the user, such as getters and setters
*/

#ifndef _RADIOCMDS_H
#define _RADIOCMDS_H

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ConstOrangeForRN2483.h"

/**
* \brief     Different kind of RADIO commands
* \details   Each of these values is used to find the correct string value in the \e params attribute of the class
*/
typedef enum _paramRad {
	RX = 0,
	TX_RADIO,
	CW,
	BT,
	MOD,
	FREQ,
	PWR,
	SPR_FACTOR,
	AUTO_FREQ_CORR_BW,
	RECEIVE_BW,
	BIT_RATE,
	FREQ_DEVIATION,
	PREAMBLE_LENGTH,
	CRC,
	IQ_INVERS,
	CODING_RATE,
	WATCHDOG_TIMER,
	BANDWIDTH,
	SIG_NOISE_RATIO,
	SYNC_RADIO,
	COUNT_PARAM_RAD
}eParamRad;

class RadioCmdsClass
{
 protected:
	 const char* params[COUNT_PARAM_RAD] = {
		 "rx",
		 "tx",
		 "cw",
		 "bt",
		 "mod",
		 "freq",
		 "pwr",
		 "sf",
		 "afcbw",
		 "rxbw",
		 "bitrate",
		 "fdev",
		 "prlen",
		 "crc",
		 "iqi",
		 "cr",
		 "wdt",
		 "bw",
		 "snr",
		 "sync",
	 };

 public:
	 /**constOrangeForRn2483
	 * @brief		Getter on the data shaping FSK configuration
	 * @details		This function allows the user to have access to the \b data \b shaping \b FSK \b configuration
	 *				by executing a "radio get bt" command on the module
	 * @return		The received value as an \e eBT value (see constOrangeForRN2483.h for more information)
	 */
	 eBT getBt();

	 /**
	 * @brief		Setter for the data shaping value of the module
	 * @details		This function allows the user to set or update the \b data \b shaping \b value applied to FSK transmissions
	 *				by executing a "radio set bt <gfBT>" command on the module
	 * @param		bt		eBT value representing the Gaussian baseband data shaping (see constOrangeForRN2483.h for more information)
	 * @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	 */
	 bool setBt(eBT bt);

	 /**
	 * @brief		Getter on the current mode of operation of the module
	 * @details		This function allows the user to have access to the current \b mode \b of \b operation of the module
	 *				by executing a "radio get mod" command on the module
	 * @return		The received value as an \e eModulation value (see constOrangeForRN2483.h for more information)
	 */
	 eModulation getModulation();

	 /**
	 * @brief		Setter for the modulation method of the module
	 * @details		This function allows the user to set or update the \b modulation \b method used by the module
	 *				by executing a "radio set mod <mode>" command on the module
	 * @param		mode		eModulation value representing the modulation mode (see constOrangeForRN2483.h for more information)
	 * @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	 */
	 bool setModulation(eModulation mode);

	 /**
	 * @brief		Getter on the current spreading factor of the module
	 * @details		This function allows the user to have access to the current \b spreading \b factor used by the transceiver
	 *				by executing a "radio get sf" command on the module
	 * @return		The received value as an \e eSpreadingFactor value (see constOrangeForRN2483.h for more information)
	 */
	 eSpreadingFactor getSF();

	 /**
	 * @brief		Setter for the spreading factor used during transmission
	 * @details		This function allows the user to set or update the \b spreading \b factor used during transmission
	 *				by executing a "radio set sf <spreadingFactor>" command on the module
	 * @param		spreadingFactor		eSpreadingFactor value representing the spreading factor (see constOrangeForRN2483.h for more information)
	 * @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	 */
	 bool setSF(eSpreadingFactor spreadingFactor);

	 /**
	 * @brief		Getter on the status of the CRC header
	 * @details		This function allows the user to have access to the status of the \b CRC \b header
	 *				by executing a "radio get crc" command on the module
	 * @return		The received value as an \e eBoolean value (see constOrangeForRN2483.h for more information)
	 */
	 eBoolean getCrc();

	 /**
	 * @brief		Getter on the status of the Invert IQ functionnality
	 * @details		This function allows the user to have access to the status of the \b Invert \b IQ \b functionnality
	 *				by executing a "radio get iqi" command on the module
	 * @return		The received value as an \e eBoolean value (see constOrangeForRN2483.h for more information)
	 */
	 eBoolean getIqInversion();

	 /**
	 * @brief		Getter on the current value settings used for the coding rate
	 * @details		This function allows the user to have access to the current value settings used for the \b coding \b rate  
	 *				during communication by executing a "radio get cr" command on the module
	 * @return		The received value as an \e eCodingRate value (see constOrangeForRN2483.h for more information)
	 */
	 eCodingRate getCodingRate();
	 
	 /**
	 * @brief		Getter on the synchronization word used for radio communication
	 * @details		This function allows the user to have access to the configured synchronization word used for 
	 *				radio communication during communication by executing a "radio get sync" command on the module
	 * @return		The received value as a \e short value
	 */
	 short getSync();

	 /**
	 * @brief		Getter on the status of the Automatic Frequency Correction Bandwidth 
	 * @details		This function allows the user to have access to the status of the \b automatic \b frequency 
	 *				\b correction \b bandwidth by executing a "radio get afcbw" command on the module
	 * @return		The received value as a \e float value
	 */	
	 float getAutoFreqCorrBw();

	 /**
	 * @brief		Getter on the signal bandwidth used for receiving
	 * @details		This function allows the user to have access to the \b signal \b bandwidth used for 
	 *				receiving by executing a "radio get rxbw" command on the module
	 * @return		The received value as a \e float value
	 */
	 float getReceiveBw();

	 /**
	 * @brief		Getter on the current power level setting used in operation
	 * @details		This function allows the user to have access to the current \b power \b level setting used in
	 *				operation by executing a "radio get pwr" command on the module
	 * @param		outputPower		uint8_t variable to store the received power from the module
	 * @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	 */
	 bool getOutputPower(int8_t& outputPower);

	 /**
	 * @brief		Getter on the current operating radio bandwidth
	 * @details		This function allows the user to have access to the current \b operating \b radio \b bandwidth
	 *				by executing a "radio get bw" command on the module
	 * @return		The received value as a \e decimal value
	 */
	 int16_t getBandWidth();

	 /**
	 * @brief		Getter on the value of the signal to noise ratio (SNR)
	 * @details		This function allows the user to have access to the value of the \b signal \b to \b noise \b ratio
	 *				for the last received packet by executing a "radio get snr" command on the module
	 * @return		The received value as a \e signed \e decimal value
	 */
	 int16_t getSigNoiseRation();

	 /**
	 * @brief		Getter on the configured bit rate for FSK communication
	 * @details		This function allows the user to have access to the configured \b bit \b rate for FSK communication
	 *				by executing a "radio get bitrate" command on the module
	 * @return		The received value as a \e signed \e decimal value
	 */
	 int32_t getBitRate();

	 /**
	 * @brief		Getter on the frequency deviation setting on the transceiver
	 * @details		This function allows the user to have access to the \b frequency \b deviation \b setting on the transceiver
	 *				by executing a "radio get fdev" command on the module
	 * @return		The received value as a \e signed \e decimal value
	 */
	 int32_t getFreqDeviation();

	 /**
	 * @brief		Getter on the current preamble length used for communication
	 * @details		This function allows the user to have access to the current \b preamble \b length used for communication
	 *				by executing a "radio get prlen" command on the module
	 * @return		The received value as a \e signed \e decimal value
	 */
	 int32_t getPreambleLength();

	 /**
	 * @brief		Getter on the current operation frequency of the module
	 * @details		This function allows the user to have access to the current \b operation \b frequency of the module
	 *				by executing a "radio get freq" command on the module
	 * @return		The received value as a \e decimal value
	 */
	 int32_t getFrequency();

	 /**
	 * @brief		Setter for the communication frequency of the radio transceiver
	 * @details		This function allows the user to set or update the \b communication \b frequency of the radio transceiver
	 *				by executing a "radio set freq <frequency>" command on the module
	 * @param		frequency		Decimal number representing the communication frequency, from 433050000 to 434790000 or
	 *								from 863000000 to 870000000, in Hz.
	 * @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	 */
	 bool setFrequency(int32_t frequency);

	 /**
	 * @brief		Getter on the length used for the watchdog time-out
	 * @details		This function allows the user to have access to the \b length used for the \b watchdog \b time-out
	 *				by executing a "radio get wdt" command on the module
	 * @param		watchdog		uint64_t variable to store the received value from the module
	 * @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	 */
	 bool getWatchdog(uint64_t& watchdog);

	 /**
	 * @brief		Setter for the transceiver output power 
	 * @details		This function allows the user to set or update the \b transceiver \b output \b power
	 *				by executing a "radio set pwr <pwrout>" command on the module
	 * @param		pwrout		Decimal number representing the transceiver output power, from -3 to 15
	 * @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	 */
	 bool setOutputPower(int8_t pwrout);

	 /**
	 * @brief		Setter for the automatic frequency correction bandwidth
	 * @details		This function allows the user to set or update the \b automatic \b frequency \b correction \b bandwidth
	 *				for receiving/transmitting by executing a "radio set afcbw <autoFreqBand>" command on the module
	 * @param		autoFreqBand		String representing the automatic frequency correction
	 * @return		Boolean value, true if everything is ok, false if there was a problem during the execution
	 */
	 bool setAutoFreqBand(String autoFreqBand);
};

#endif

