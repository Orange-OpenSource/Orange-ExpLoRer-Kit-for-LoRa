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
* Created:     2017-04-21 by Halim BENDIABDALLAH
* Modified:	   2017-10-27 by Karim BAALI
*/

/**
* @file			InternalConstRN2483.h
* @brief		Contains all private constants Library
*/

#ifndef _INTERNAL_CONST_RN2483_H
#define _INTERNAL_CONST_RN2483_H


#define DEBUG    //Remove this line to avoid debug printing

#ifdef DEBUG
#define debugPrintLn(X) SerialUSB.println((char*)X)
#define debugPrint(X) SerialUSB.print((char*)X)
#define debugInt(X) SerialUSB.print((int)X, HEX)
#define debugIntLn(X) SerialUSB.println((int)X, HEX)
#warning "Debug mode is ON"
#else
#define debugPrintLn(...)
#define debugPrint(...)
#define debugInt(...)
#define debugIntLn(...)
#endif

#define HEX_CHAR_TO_HIGH_NIBBLE(X) (((X >= 'A') ? X - 'A' + 10 : X - '0') << 4)
#define HEX_CHAR_TO_LOW_NIBBLE(X) ((X >= 'A') ? X - 'A' + 10 : X - '0')

#define NIBBLE_TO_HEX_CHAR(i) ((i <= 9) ? ('0' + i) : ('A' - 10 + i))
#define HIGH_NIBBLE(i) ((i >> 4) & 0x0F)
#define LOW_NIBBLE(i) (i & 0x0F)

#define iS_ON(X) X.equals("on") ? BOOL_TRUE : BOOL_FALSE

#define DEFAULT_TIMEOUT					200
#define UPLINK_TIMEOUT					7000
#define SAVE_TIMEOUT					2000
#define JOIN_TIMEOUT					10000  // TimeOnAir + RX2Window 

#define DEFAULT_INPUT_BUFFER_SIZE		64 

#define SEPARATOR						((char*)" ")
#define STR_OTAA						"otaa"
#define STR_ABP							"abp"
#define GET								"get"
#define SET								"set"
#define STR_MAC_RX						"mac_rx"

#define STR_OK							"ok"
#define STR_ON							"on"
#define STR_OFF							"off"
#define STR_CNF							"cnf"
#define STR_UNCNF						"uncnf"
#define CRLF							"\r\n"

#define STR_ERROR_EMPTY_BUFFER			"Error : receiving buffer is empty"
#define STR_ERROR_LORASTR_NOT_INIT		"Error : lorastream is not initialized"
#define STR_ERROR_NETWORK_NOT_JOINED	"Error : network isn't joined yet"
#define INT_ERROR_FAILED				-1
#define FLT_ERROR_FAILED				-1.0

#endif
