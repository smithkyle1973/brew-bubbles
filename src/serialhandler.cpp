/* Copyright (C) 2019-2020 Lee C. Bussy (@LBussy)

This file is part of Lee Bussy's Brew Bubbles (brew-bubbles).

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

#include "serialhandler.h"

#undef SERIAL
#if DOTELNET == true
ESPTelnet SerialAndTelnet;
#define SERIAL SerialAndTelnet // Use Telnet
#else
#define SERIAL Serial // Use hardware serial
#endif

#ifndef DISABLE_LOGGING

void setSerial()
{                // Start serial with auto-detected rate (default to BAUD)
    delay(2000); // Delay to allow monitor to start
    SERIAL.begin(BAUD);
    // SERIAL.setDebugOutput(true);
    SERIAL.flush();
    Log.begin(LOG_LEVEL, &SERIAL, true);
    Log.setPrefix(printTimestamp);
    Log.notice(F("SERIAL logging started at %l." CR), BAUD);
}

void printTimestamp(Print *_logOutput)
{
    time_t now;
    time_t rawtime = time(&now);
    struct tm ts;
    ts = *localtime(&rawtime);
    char locTime[22] = {'\0'};
    strftime(locTime, sizeof(locTime), "%FT%TZ ", &ts);
    _logOutput->print(locTime);
}

#else // DISABLE_LOGGING

void serial() {}

#endif // DISABLE_LOGGING
