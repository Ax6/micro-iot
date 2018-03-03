//
// Created by Aaron Russo on 19/02/2018.
//

#include "LogLog.h"
#include <Arduino.h>

void LogLog::begin(void) {
#ifdef logLevel0
    Serial.begin(BAUD_RATE);
#endif
}

LogLog logger;