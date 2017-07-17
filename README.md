# Arduino Library for mp3/wav Serial module based on JQ8400TF or QJ004-16S

![JQ8400TF module](https://github.com/Cyb3rn0id/mp3Serial_JQ8400TF/blob/master/documents/mp3wav_module.jpg)

Module that can be used with this library is depicted above: is the one with only 4 pins (vcc, gnd, tx and rx) and micro-sd  (trans-flash) card. Module includes a 3W power amplifier (8002A chip). I'm pretty sure the chip on this module is the JQ8400TF or the QJ004-16S (chip label on these modules are erased). Library is not suitable for other modules (like the YX5300 and similar) nor for the module with micro-usb port and flash memory on board: this module uses chip JQ8400FL that have different serial commands. 

The library uses the hardware serial port. I've written it for usage with ESP-01 (ESP8266) but I've tested it also on Arduino Duemilanove and Arduino Leonardo. The library includes features for be used with other Serial ports (1,2 and 3) on Arduino Leonardo, Mega and Mega2560.

More info on the module and library here: http://www.settorezero.com/wordpress/en/un-player-wavmp3-economico-controllabile-da-porta-seriale-libreria-per-arduino-e-esp8266/

## Library Install

Download the .zip library from here. In the Arduino IDE, from the 'Sketch' menu, select '#include library' and then 'add library from .zip'. Select the .zip you've downloaded here. An example usage is included.

## Libray Usage

First, be sure you've included at least 1 file on the microSD card! (you can use WAV or MP3). In your arduino sketch, include library:

```C
#include <mp3serial_JQ8400TF.h>
```

Then instance the library giving it the name you prefer and defining which serial port you want to use:

```C
mp3Serial mp3(0); // initialize library on serial port 0 (for Arduino duemilanove, ESP8266 and others)
//mp3Serial mp3(1); // for Serial 1 on Arduino Leonardo (rx:0, tx:1) or Mega (rx:19, tx:18)
//mp3Serial mp3(2); // for Serial 2 on Mega (rx:17, tx:16)
//mp3Serial mp3(3); // for Serial 3 on Mega (rx:15, tx:14)
```

In the Setup function, initialize the module

```C
mp3.begin(); // init module
```

Now you can use the commands:

```C
.play(); // play an injected song or resume play after pause
.pause(); // pause play
.next(); // next song
.prev(); // previous song
.volumeup(); // increase volume 1 step
.volumedown(); // decrease volume 1 step
.forward(); // play forward
.rewind(); // play rewind
.stop(); // stop the song
.stopInject(); // ?
.playIndex(uint16_t index); // play the 'index'th song (0x0000 to 0xFFFF)
.setVolume(uint8_t volume); // set volume to 'volume' value (0x00 to 0x30)
.playWithVolume(uint8_t volume, uint8_t index); // play 'index'th song at 'volume' volume value
.injectSong(uint16_t index); // inject the 'index'th song (without playing it)
.playFromFolder(uint8_t folder, uint8t index); // play 'index'th song from 'folder'th folder
```
