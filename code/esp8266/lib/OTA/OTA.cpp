//
// Created by Aaron Russo on 19/02/2018.
//

#include "OTA.h"
#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <LogLog.h>

void OTAClass::init(void) {
    ArduinoOTA.onStart([]() {
        log0("OTA Started");
    });
    ArduinoOTA.onEnd([]() {
        log0("OTA Finished");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        log0("In progress");
    });
    ArduinoOTA.onError([](ota_error_t error) {
        log0("Error:");
        log0(error);
        if (error == OTA_AUTH_ERROR) log0("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) log0("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) log0("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) log0("Receive Failed");
        else if (error == OTA_END_ERROR) log0("End Failed");
    });
    ArduinoOTA.begin();
    log0("OTA Ready");
}

void OTAClass::handle(void) {
    log0("Handling OTA");
    ArduinoOTA.handle();
}

OTAClass OTA;