/* Copyright (C) 2019 Lee C. Bussy (@LBussy)

This file is part of Lee Bussy's Brew Bubbbles (brew-bubbles).

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#ifndef CONFIG_H
#define CONFIG_H

//////////////////////////////////////////////////////////////////////////
//
// Set verbosity of debug messages 0-6
//
//      * 0 - LOG_LEVEL_SILENT     no output 
//      * 1 - LOG_LEVEL_FATAL      fatal errors 
//      * 2 - LOG_LEVEL_ERROR      all errors  
//      * 3 - LOG_LEVEL_WARNING    errors, and warnings 
//      * 4 - LOG_LEVEL_NOTICE     errors, warnings and notices 
//      * 5 - LOG_LEVEL_TRACE      errors, warnings, notices & traces 
//      * 6 - LOG_LEVEL_VERBOSE    all 
//
// Uncomment #define DISABLE_LOGGING to remove all logging
//
#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_VERBOSE
// #define DISABLE_LOGGING // Uncomment to disable all logging
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define API Key (identifies application to target)
//
#ifndef API_KEY
#define API_KEY "Brew Bubbles"
#endif
//
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
//
// Define data source (identifies sensor source to target)
//
#ifndef SOURCE
#define SOURCE "Brew Bubbles"
#endif
//
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
//
// Define build version (Git tag from PIO Env)
//
#ifndef VERSION_STRING
#define VERSION_STRING PIO_SRC_TAG
#endif
//
//////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////////////////////////////////////////////
//
// Define build commit (Git commit from PIO Env)
//
#ifndef BUILD_NAME
#define BUILD_NAME PIO_SRC_REV
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Set WiFi Channel (1, 6, 11 are the only ones which should be used)
// https://www.metageek.com/training/resources/why-channels-1-6-11.html
//
#ifndef WIFI_CHAN
#define WIFI_CHAN 1
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Set WiFi country (US, JP or CN)
// US = 1-11, CN = 1-13, JP = 1-14
//
#ifndef WIFI_COUNTRY
#define WIFI_COUNTRY "US"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Set serial baud rate (if not set via PlatformIO build flag)
//
#ifndef BAUD
#define BAUD 74880
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Access Point name
//
#ifndef APNAME
#define APNAME "brewbubbles"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Access point password
//
#ifndef AP_PASSWD
#define AP_PASSWD "brewbubbles"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Set Version JSON location
//
#ifndef VERSIONJSONLOC
#define VERSIONJSONLOC "http://www.brewbubbles.com/firmware/version.json"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Firmware URL
//
#ifndef FIRMWAREURL
#define FIRMWAREURL "http://www.brewbubbles.com/firmware/firmware.bin"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// SPIFFS URL
//
#ifndef SPIFFSURL
#define SPIFFSURL "http://www.brewbubbles.com/firmware/spiffs.bin"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Default host name
//
#ifndef HOSTNAME
#define HOSTNAME "brewbubbles"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Reset mDNS to help the connectiviy issues
//
#ifndef MDNSTIMER
#define MDNSTIMER 3600
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Reboot timer
//
#ifndef REBOOTTIMER
#define REBOOTTIMER 86400
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Default Bubble name
//
#ifndef BUBNAME
#define BUBNAME "Fermenter 1"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Input pin for counter
//
#ifndef COUNTPIN
#define COUNTPIN D1
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define temperature format (true = Fahrenheit, false = Celsius)
//
#ifndef TEMPFORMAT
#define TEMPFORMAT true
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define ambient temp sensor pin
//
#ifndef AMBSENSOR
#define AMBSENSOR D2 // Uncomment to use Ambient temp sensor
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define vessel temp sensor pin
//
#ifndef VESSENSOR
#define VESSENSOR D3 // Uncomment to use vessel temp sensor
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define reset WiFi on boot pin - reset if pulled low on boot
//
#ifndef RESETWIFI
#define RESETWIFI D5
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Bubble loop time in seconds
//
#ifndef BUBLOOP
#define BUBLOOP 60 // One minute
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Number of BPM readings in a sliding window for averaging (one per min)
//
#ifndef BUBAVG
#define BUBAVG 15
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Number of temp readings in a sliding window for averaging (one per min)
//
#ifndef TEMPAVG
#define TEMPAVG 5
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Resolution time in microseconds (de-bouncer) - Must be declared as an UL
//
#ifndef RESOLUTION
#define RESOLUTION 500UL
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Frequency with which to blink LED when in Access Point blocking loop
//
#ifndef APBLINK
#define APBLINK 1000UL // 1000ms each state = 2000ms per cycle = 0.5Hz
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Frequency with which to blink LED when in Station Connect blocking loop
//
#ifndef STABLINK
#define STABLINK 333UL // 333ms each state = 666ms per cycle = ~1.5Hz
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Frequency with which to blink LED when in NTP blocking loop
//
#ifndef NTPBLINK
#define NTPBLINK 50UL // 50ms each state = 100ms per cycle = 10Hz
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Port for local web services
//
#ifndef PORT
#define PORT 80
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// URL Target Name
//
#ifndef URLTARGET
#define URLTARGET "URL Target"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// URL Target Frequency (default 2 minutes)
//
#ifndef URLTARGETFREQ
#define URLTARGETFREQ 2
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Default Brewer's Friend Frequency (default 15 mins)
//
#ifndef BFFREQ
#define BFFREQ 15
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Brewer's Friend URL
//
#ifndef BFURL
#define BFURL "http://log.brewersfriend.com/stream/"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// NTP Server
//
#ifndef TIMESERVER
#define TIMESERVER "pool.ntp.org"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Output pin for LED
//
#ifndef LED
#define LED LED_BUILTIN
#endif
//
//////////////////////////////////////////////////////////////////////////

#endif // CONFIG_H
