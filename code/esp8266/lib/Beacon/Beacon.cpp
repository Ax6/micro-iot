//
// Created by Aaron Russo on 24/02/2018.
//

#include "Beacon.h"
#include <Arduino.h>
#include <FileSystem.h>
#include <LogLog.h>
#include <OS.h>
#include <ESP.h>

void Beacon::init(void) {
    log0("Loading beacon time");
    log0("Just checking if millisSinceReset is init with 0");
    log0(this->millisSinceReset);
    this->savedElapsedTime = this->readSavedElapsedTime();
}

bool Beacon::isNeeded(void) {
    return this->getElapsedTime() > BEACON_PERIOD;
}

void Beacon::saveElapsedTime(void) {
    uint32 time;
    time = this->getElapsedTime();
    flash.write(TIME_FROM_LAST_BEACON, (const char *) (&time), 4);
}

uint32 Beacon::readSavedElapsedTime(void) {
    uint32 *pointer;
    pointer = (uint32 *) flash.read(TIME_FROM_LAST_BEACON);
    return *pointer;
}

uint32 Beacon::getElapsedTime(void) {
    return this->savedElapsedTime + millis() - this->millisSinceReset;
}

void Beacon::reset(void) {
    this->savedElapsedTime = 0;
    this->millisSinceReset = millis();
}

void Beacon::setAsSent(void) {
    this->reset();
}