/* Copyright (C) 2019 Lee C. Bussy (@LBussy)

This file is part of Lee Bussy's Brew Bubbles (Brew-Bubbles).

Brew Bubbles is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

Brew Bubbles is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
General Public License for more details.

You should have received a copy of the GNU General Public License along
with Brew Bubbles. If not, see <https://www.gnu.org/licenses/>. */

#include "bubbles.h"

Bubbles *pBubbles; // Pointer to Counter class

static ICACHE_RAM_ATTR void HandleInterruptsStatic(void) { // External interrupt handler
    pBubbles->handleInterrupts(); // Calls class member handler
}

bool Bubbles::instanceFlag = false;

Bubbles* Bubbles::single = NULL; // Holds pointer to class

Bubbles* Bubbles::getInstance() {
    if(!instanceFlag) {
        single = new Bubbles();
        instanceFlag = true;
        single->start();
        return single;
    } else {
        return single;
    }
}

void Bubbles::start() {
    pinMode(COUNTPIN, INPUT);       // Change pinmode to input
    attachInterrupt(digitalPinToInterrupt(COUNTPIN), HandleInterruptsStatic, RISING); // FALLING, RISING or CHANGE
    pBubbles = single;              // Assign current instance to pointer 
    single->ulLastReport = millis();// Store the last report timer
    single->pulse = 0;              // Reset pulse counter

    // Set starting values
    unsigned long ulNow = millis();
    single->ulStart = ulNow;
    single->lastPpm = 0.0;
    
    // Set starting time
    NtpHandler *ntpTime = NtpHandler::getInstance();
    ntpTime->update();
    single->lastTime, ntpTime->Time;

    // Set starting Bubble
    strlcpy(single->Bubble, "{}", 3);

    // Set circular buffers 
    CircularBuffer<float, TEMPAVG> *tempAmbAvg;
    CircularBuffer<float, TEMPAVG> *tempVesAvg;
    CircularBuffer<float, BUBAVG> *bubAvg;
}

Bubbles::~Bubbles() {
    instanceFlag = false;
}

void Bubbles::update() {
    // Handle NTP Time
    NtpHandler *ntpTime = NtpHandler::getInstance();
    ntpTime->update();
    single->lastTime = ntpTime->Time;
    // Handle PPM Calculations
    single->lastPpm = single->getRawPpm();
    single->bubAvg->push(single->lastPpm);
    // Handle Temps
    single->tempVesAvg->push(single->getVesselTemp());
    single->tempAmbAvg->push(single->getAmbientTemp());
    single->createBubbleJson(); // Update current JSON
    Log.verbose(F("Time is %s, PPM is %D." CR), single->lastTime, single->lastPpm);
}

void Bubbles::handleInterrupts(void) { // Bubble Interrupt handler
    digitalWrite(LED, LOW);
    unsigned long now = micros();
    if ((now - ulMicroLast) > RESOLUTION) { // Filter noise/bounce
        single->pulse++;    // Increment pulse count
    }
    Log.verbose(F("॰°ₒ৹๐" CR)); // Looks like a bubble, right?
}

float Bubbles::getRawPpm() { // Return raw pulses per minute (resets counter)
    unsigned long thisTime = millis(); // Get timer value now
    unsigned long ulLapsed = thisTime - single->ulLastReport; // Millis since last run
    float fLapsed = (float) ulLapsed; // Cast to float
    float secs = fLapsed / 60000.0; // Minutes since last request
    float ppm = (pulse / secs); // Calculate PPM
    single->pulse = 0; // Zero the pulse counter
    single->ulLastReport = millis(); // Store the last report timer
    return ppm; // Return pulses per minute
}

float Bubbles::getPpm() {
    return single->lastPpm;
}

float Bubbles::getAmbientTemp() {
    OneWire ambient(AMBSENSOR);
    byte addrAmb[8];
    float fAmbTemp = -100.0;
    while (ambient.search(addrAmb)) { // Make sure we have a sensor
        DallasTemperature sensorAmbient(&ambient);
        sensorAmbient.begin();
        sensorAmbient.requestTemperatures();

        JsonConfig *config = JsonConfig::getInstance();
        if (config->tempinf == true)
            fAmbTemp = sensorAmbient.getTempFByIndex(0) + config->calAmbient;
        else
            fAmbTemp = sensorAmbient.getTempCByIndex(0) + config->calAmbient;
    }
    return fAmbTemp;
}

float Bubbles::getVesselTemp() {
    OneWire vessel(VESSENSOR);
    byte addrVes[8];
    float fVesTemp = -100.0;
    while (vessel.search(addrVes)) { // Make sure we have a sensor
        DallasTemperature sensorVessel(&vessel);
        sensorVessel.begin();
        sensorVessel.requestTemperatures();

        JsonConfig *config = JsonConfig::getInstance();
        if (config->tempinf == true)
            fVesTemp = sensorVessel.getTempFByIndex(0) + config->calVessel;
        else
            fVesTemp = sensorVessel.getTempCByIndex(0) + config->calVessel;
    }
    return fVesTemp;
}

float Bubbles::getAvgAmbient() {
    // Retrieve TEMPAVG readings to calculate average
    // float avg = 0.0;
    // uint8_t size = single->tempAmbAvg->size();
    // for (int i = 0; i < single->tempAmbAvg->size(); i++) {
    //     float thisTemp = single->tempAmbAvg[i];
    //     avg += single->tempAmbAvg[i] / size;
    // }
    // return(avg);
}

float Bubbles::getAvgVessel() {
    // Return TEMPAVG readings to calculate average
}

float Bubbles::getAvgPpm() {
    // Return BUBAVG readings to calculate average
}

void Bubbles::createBubbleJson() {
    // const size_t capacity = 3*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5);
    const size_t capacity = BUBBLEJSON;
    StaticJsonDocument<capacity> doc;
    JsonConfig *config = JsonConfig::getInstance();

    doc[F("api_key")] = F(API_KEY);
    doc[F("vessel")] = config->bubname;
    doc[F("datetime")] = single->lastTime;
    
    if (config->tempinf == true) {
        doc[F("format")] = F("F");
    } else {
        doc[F("format")] = F("C");
    }

    // Get bubbles data (updated by minute, no averages)
    JsonObject data = doc.createNestedObject(F("data"));
    data[F("bpm")] = single->lastPpm;
    data[F("ambtemp")] = single->getAmbientTemp();
    data[F("vestemp")] = single->getVesselTemp();

    char output[capacity];
    serializeJson(doc, output, sizeof(output));
    strlcpy(single->Bubble, output, sizeof(output));
}
