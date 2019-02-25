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

#ifndef mp3Serial_h
#define mp3Serial_h

#include <stdint.h>

#define	BYTE_START		0x7E
#define BYTE_STOP		0xEF

// 1 bytes commands
#define CMD_PLAY		0x01
#define CMD_PAUSE		0x02
#define CMD_NEXT_SONG		0x03
#define CMD_PREV_SONG		0x04
#define CMD_VOLUME_UP   	0x05
#define CMD_VOLUME_DOWN 	0x06
#define CMD_FORWARD 		0x0A
#define CMD_REWIND  		0x0B
#define CMD_STOP 		0x0E
#define CMD_STOP_INJECT 	0x0F

// 2 bytes commands
#define CMD_SET_VOLUME 		0x31	// Set Volume: second byte is volume level: 0x00 to 0x30
#define CMD_SEL_DEV 		0x35	// Select Device
	#define DEV_TF 		0x01	// second of "Select Device" command: only Trans-Flash is selectable on this chip revision (JQ8400TF)

#define CMD_IC_MODE 		0x35
	#define MODE_WAKE_UP 	0x02	// second byte of "IC Mode" command 	
	#define MODE_SLEEP 	0x03	// ""	
	#define MODE_RESET  	0x05	// ""

// 3 bytes commands
#define CMD_PLAY_W_VOL 		0x31	// 2nd byte is volume level: 0x00 to 0x30, 3rd byte is song index (0x00 to 0xFF)
#define CMD_PLAY_INDEX   	0x41	// after 0x41, 2 bytes are expected: high byte and low byte of song index (0x0001 - 0xFFFF)
#define CMD_PLAY_DIR_INDEX 	0X42	// after 0x42, 2 bytes are expected: first byte is the directory index, second byte is the song index
#define CMD_INJECT_INDEX 	0X43	// Same as 0x41, but "inject" (prepare the song) without playing it, you must use play command after

// Special commands
#define	CMD_SET_PLAY_MODE		0x33
	#define PLAY_MODE_ALL		0x00	// starts from first song, plays all and then return to first, continuously
	#define PLAY_MODE_STUP		0x01	// ? don't works
	#define PLAY_MODE_REPEAT	0x00	// ! warning: this is a 3 bytes command: 0x33, 0x00 and then the song index to repeat
	
#define CMD_PLAY_COMBINE 	0x45	// play combination up to 15 songs, followed by folder index and song index, up to 15. Example:
										// 7E 08 45 01 05 02 01 01 03 EF : plays song 5 in folder 1, then song 1 in folder 2 and then song 3 in folder 1

class mp3Serial
	{
	public:
		mp3Serial(void);
		mp3Serial(uint8_t serialport);
	
		void begin(void);
		void play(void);
		void pause(void);
		void next(void);
		void prev(void);
		void volumeup(void);
		void volumedown(void);
		void forward(void);
		void rewind(void);
		void stop(void);
		void stopInject(void);
		void playIndex(uint16_t index);
		void setVolume(uint8_t volume);
		void playWithVolume(uint8_t volume, uint8_t index);
		void injectSong(uint16_t index);
		void playFromFolder(uint8_t folder, uint8_t index);
				
	private:
		void write_nBytes(uint8_t n);
		void write_1byte(uint8_t command);
		void write_2bytes(uint8_t command, uint8_t data);
		void write_3bytes(uint8_t command, uint16_t data);
	};
	
#endif
