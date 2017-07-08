/*
* Example for mp3serial_JQ8400TF Library
* by Giovanni Bernardo (www.settorezero.com)
* Simple play the first song on the SD
* Module attached on hardware serial port of
* Arduino Duemilanove (rx:0, tx:1)
* song can be either a WAV or MP3
*/
#include <mp3serial_JQ8400TF.h>

mp3Serial mp3(0); // initialize library on serial port 0 (for Arduino duemilanove)
//mp3Serial mp3(1); // for Serial 1 on Arduino Leonardo (rx:0, tx:1) or Mega (rx:19, tx:18)
//mp3Serial mp3(2); // for Serial 2 on Mega (rx:17, tx:16)
//mp3Serial mp3(3); // for Serial 3 on Mega (rx:15, tx:14)

void setup(void)
	{
	mp3.begin(); // init module
	mp3.playIndex(1); // play first song
	}
	
void loop(void)
	{
	
	}
