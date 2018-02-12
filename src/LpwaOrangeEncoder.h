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
* @file			LpwaOrangeEncoder.h
* @brief		Helpful methods to create, update or decode payloads
* @details		This class contains all the necessary methods to be able to easily
*				interact with a payload and modify it if necessary
*/

#ifndef LPWA_ORANGE_ENCODER_CPP_H
#define LPWA_ORANGE_ENCODER_CPP_H

class LpwaOrangeEncoderClass
{
private:
    char framePayload[64];
    int counter;
 
public:
	/**
	* @brief		Constructor for the LpwaOrangeEncoderClass class
	* @details		Used to instanciate a new LpwaOrangeEncoderClass object
	*/
    LpwaOrangeEncoderClass();

	/**
	* @brief		Destructor for the LpwaOrangeEncoderClass class
	* @details		Used to delete an LpwaOrangeEncoderClass instance
	*/
    virtual ~LpwaOrangeEncoderClass();

	/**
	* @brief		Flushing the payload and counter attributes of the class
	* @details		This function is used to reset the counter to 0 and and clear the framePayload attribute
	*/
	void flush();

	/**
	* @brief		Getter for a payload and its length
	* @details		This function allows the user to get a pointer on a frame payload to be able to manipulate it easily
	*				and to receive its length in the argument variable
	* @param		len		Pointer on an uint8_t value to receive the payload length value
	* @return		An uint8_t pointer on the frame payload
	*/
	uint8_t* getFramePayload(int8_t* len);

	/**
	* @brief		Quickly add a boolean value to a payload
	* @details		This function allows the user to quickly add a boolean value to a payload if it doesn't 
	*				exceed the maximal length
	* @param		value		Boolean value to add to the payload
	* @return		A boolean value, true if everything is ok, false if the add was impossible
	*/
	bool addBool(bool value);

	/**
	* @brief		Quickly add a byte to a payload
	* @details		This function allows the user to quickly add a byte to a payload if it doesn't
	*				exceed the maximal length
	* @param		value		Byte to add to the payload
	* @return		A boolean value, true if everything is ok, false if the add was impossible
	*/
	bool addByte(int8_t value);

	/**
	* @brief		Quickly add a short to a payload
	* @details		This function allows the user to quickly add a short to a payload if it doesn't
	*				exceed the maximal length
	* @param		value		Short to add to the payload
	* @return		A boolean value, true if everything is ok, false if the add was impossible
	*/
	bool addShort(int16_t value);

	/**
	* @brief		Quickly add an integer to a payload
	* @details		This function allows the user to quickly add an integer to a payload if it doesn't
	*				exceed the maximal length
	* @param		value		Integer to add to the payload
	* @return		A boolean value, true if everything is ok, false if the add was impossible
	*/
	bool addInt(int32_t value);

	/**
	* @brief		Quickly add a long to a payload
	* @details		This function allows the user to quickly add a long to a payload if it doesn't
	*				exceed the maximal length
	* @param		value		Long to add to the payload
	* @return		A boolean value, true if everything is ok, false if the add was impossible
	*/
	bool addLong(int64_t value);

	/**
	* @brief		Quickly add a float to a payload
	* @details		This function allows the user to quickly add a float to a payload if it doesn't
	*				exceed the maximal length
	* @param		value		Float to add to the payload
	* @return		A boolean value, true if everything is ok, false if the add was impossible
	*/
	bool addFloat(float value);
	
	/**
	* @brief		Quickly add an unsigned byte to a payload
	* @details		This function allows the user to quickly add an unsigned byte to a payload if it doesn't
	*				exceed the maximal length
	* @param		value		Unsigned byte to add to the payload
	* @return		A boolean value, true if everything is ok, false if the add was impossible
	*/
	bool addUByte(uint8_t value);

	/**
	* @brief		Quickly add an unsigned short to a payload
	* @details		This function allows the user to quickly add an unsigned short to a payload if it doesn't
	*				exceed the maximal length
	* @param		value		Unsigned short to add to the payload
	* @return		A boolean value, true if everything is ok, false if the add was impossible
	*/
	bool addUShort(uint16_t value);

	/**
	* @brief		Quickly add an unsigned integer to a payload
	* @details		This function allows the user to quickly add an unsigned integer to a payload if it doesn't
	*				exceed the maximal length
	* @param		value		Unsigned integer to add to the payload
	* @return		A boolean value, true if everything is ok, false if the add was impossible
	*/
	bool addUInt(uint32_t value);

	/**
	* @brief		Quickly add an unsigned long to a payload
	* @details		This function allows the user to quickly add an unsigned long to a payload if it doesn't
	*				exceed the maximal length
	* @param		value		Unsigned long to add to the payload
	* @return		A boolean value, true if everything is ok, false if the add was impossible
	*/
	bool addULong(uint64_t value);		
};

extern LpwaOrangeEncoderClass LpwaOrangeEncoder;

#endif // LPWA_ORANGE_ENCODER_CPP_H
