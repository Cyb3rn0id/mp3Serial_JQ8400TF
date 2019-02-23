/*
Mp3 Serial Library for boards with JQ8400TF or QJ004-16S chip

Copyright (c) 2017 Giovanni Bernardo (CyB3rn0id)
http://www.settorezero.com
http://www.facebook.com/settorezero
http://www.twitter.com/settorezero

LICENSE
The MIT License (MIT)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORTOR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <Arduino.h>
#include "mp3serial_JQ8400TF.h"

static uint8_t mp3Buffer[6] = {0};
static uint8_t uart=0; // uart number

// public functions

// Initialize Serial port and module
mp3Serial::mp3Serial(void)
	{uart=0;};
	
mp3Serial::mp3Serial(uint8_t serialport)
	{serialport>3?uart=0:uart=serialport;};
	
void mp3Serial::begin(void)
	{
	switch (uart)
		{
		case 0:
			Serial.begin(9600);
			break;
		#if defined(AVR_LEONARDO) || defined(AVR_MEGA) || defined(AVR_MEGA2560)
		case 1:
			Serial1.begin(9600);
			break;
		#endif
		#if defined(AVR_MEGA) || defined(AVR_MEGA2560)
		case 2:
			Serial2.begin(9600);
			break;
		case 3:
			Serial3.begin(9600);
			break;
		#endif
		}
	delay(500);
	write_2bytes(CMD_SEL_DEV,DEV_TF);
	delay(200);
	setVolume(0x30);
	};

// -------------------------------------------------------------------------------
// 1 byte commands
// -------------------------------------------------------------------------------
void mp3Serial::play(void)
	{
	write_1byte(CMD_PLAY);
	}
	
void mp3Serial::pause(void)
	{
	write_1byte(CMD_PAUSE);
	}

void mp3Serial::next(void)
	{
	write_1byte(CMD_NEXT_SONG);
	}

void mp3Serial::prev(void)
	{
	write_1byte(CMD_PREV_SONG);
	}

void mp3Serial::volumeup(void)
	{
	write_1byte(CMD_VOLUME_UP);
	}
	
void mp3Serial::volumedown(void)
	{
	write_1byte(CMD_VOLUME_DOWN);
	}

void mp3Serial::forward(void)
	{
	write_1byte(CMD_FORWARD);
	}
	
void mp3Serial::rewind(void)
	{
	write_1byte(CMD_REWIND);
	}
	
void mp3Serial::stop(void)
	{
	write_1byte(CMD_STOP);
	}
	
void mp3Serial::stopInject(void)
	{
	write_1byte(CMD_STOP_INJECT);
	}

	
// -------------------------------------------------------------------------------
// 2 bytes commands
// -------------------------------------------------------------------------------

// Set Volume (0x00 - 0x30)
void mp3Serial::setVolume(uint8_t volume)
	{
	write_2bytes(CMD_SET_VOLUME, volume);
	};

// -------------------------------------------------------------------------------
// 3 bytes commands
// -------------------------------------------------------------------------------

// Play song index (0x0000 - 0xFFFF)
void mp3Serial::playIndex(uint16_t index)
	{
	write_3bytes(CMD_PLAY_INDEX, index);
	};

// play song INDEX with volume VOLUME
void mp3Serial::playWithVolume(uint8_t volume, uint8_t index)
	{
	write_3bytes(CMD_PLAY_W_VOL, (uint16_t)((volume<<8)|index)); 
	};

// inject song INDEX (0x0000 - 0xFFFF)
void mp3Serial::injectSong(uint16_t index)
	{
	write_3bytes(CMD_INJECT_INDEX, index); 
	};

// play song INDEX from folder FOLDER
void mp3Serial::playFromFolder(uint8_t folder, uint8_t index)
	{
	write_3bytes(CMD_PLAY_DIR_INDEX, (uint16_t)((folder<<8)|index)); 
	};

// -------------------------------------------------------------------------------
// private functions	
// -------------------------------------------------------------------------------

void mp3Serial::write_nBytes(uint8_t n)
	{
	for(uint8_t i=0; i<n; i++)//
		{
		switch (uart)
		{
		case 0:
			Serial.write(mp3Buffer[i]);
			break;
		#if defined(AVR_LEONARDO) || defined(AVR_MEGA) || defined(AVR_MEGA2560)
		case 1:
			Serial1.write(mp3Buffer[i]);
			break;
		#endif
		#if defined(AVR_MEGA) || defined(AVR_MEGA2560)
		case 2:
			Serial2.write(mp3Buffer[i]);
			break;
		case 3:
			Serial3.write(mp3Buffer[i]);
			break;
		#endif
		}
		}
	};
	
	
void mp3Serial::write_1byte(uint8_t command)
	{
	mp3Buffer[0]=BYTE_START;
	mp3Buffer[1]=2;
	mp3Buffer[2]=command; 
	mp3Buffer[3]= BYTE_STOP;
	write_nBytes(4);
	};
	
void mp3Serial::write_2bytes(uint8_t command, uint8_t data)
	{
	mp3Buffer[0]=BYTE_START;
	mp3Buffer[1]=3;
	mp3Buffer[2]=command; 
	mp3Buffer[3]=data;
	mp3Buffer[4]= BYTE_STOP;
	write_nBytes(5);
	};
	
void mp3Serial::write_3bytes(uint8_t command, uint16_t data)
	{
	mp3Buffer[0]=BYTE_START;
	mp3Buffer[1]=4;
	mp3Buffer[2]=command; 
	mp3Buffer[3]=(uint8_t)(data>>8);
	mp3Buffer[4]=(uint8_t) data;
	mp3Buffer[5]= BYTE_STOP;
	write_nBytes(6); 
	};
