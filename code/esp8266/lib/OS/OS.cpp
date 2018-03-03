//
// Created by Aaron Russo on 21/02/2018.
//

#include "OS.h"
#include <LogLog.h>
#include <Arduino.h>
#include <FileSystem.h>
#include <Firmware.h>
#include <Ticker.h>
#include <OTA.h>
#include <ESP.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <Beacon.h>
#include <WiFiUdp.h>

void OSClass::boot(void) {
    log0("");
    log0("Starting boot procedure...");
    flash.init(MEM_HUGE);
    this->beacon.init();
    if (!WiFi.SSID()) {
        log0("No WiFi credentials saved.");
        this->createWiFiPrompt();
    } else {
        log0("Found WiFi credentials!");
    }
    OTA.init();
    this->disconnect();
}

void OSClass::createWiFiPrompt(void) {
    log0("Creating WiFi prompt");
    WiFiManager wifiManager;
    wifiManager.autoConnect();
    if (!WiFi.isConnected()) {
        log0("Connection fail! Rebooting...");
        delay(5000);
        ESP.reset();
    }
}

bool OSClass::hasFirmware(void) {
    return HAS_FIRMWARE;
}

void OSClass::connect(void) {
    log0("Connect");
    WiFi.setPhyMode(WIFI_PHY_MODE_11B);
    WiFi.setOutputPower(0);
    WiFi.mode(WIFI_STA);
    WiFi.begin();
}

void OSClass::disconnect(void) {
    log0("Disconnect");
    WiFi.disconnect(true);
}

/*
 * Data is a char pointer
 * First bit of first byte tells if receive is needed
 * The other bits of the first byte are the size of the data packet to transmit
 */
void OSClass::transmission(char *data) {
    char dataSize = *data >> 1;
    bool receiveNeeded, beaconNeeded = this->beacon.isNeeded();
    receiveNeeded = beaconNeeded || (*data & 1);
    if (beaconNeeded || dataSize) {
        log0("Transmission needed");
        this->connect();
        this->transmit(data, dataSize);
        if (receiveNeeded) {
            log0("Receive needed");
            this->receive();
        }
        this->disconnect();
    }
}

void OSClass::transmit(char *data, char dataSize) {
    uint8 beaconData;
    this->udp.beginPacket(UDP_IP_TX, UDP_PORT_TX);
    beaconData = (uint8) this->beacon.isNeeded();
    this->udp.write(beaconData);
    while (dataSize > 0) {
        data += 1;
        this->udp.write(data);
        dataSize -= 1;
    }
    this->udp.endPacket();
    if (beaconData) {
        this->beacon.setAsSent();
    }
}

void OSClass::receive(void) {
    int packetSize;
    this->canWaitUDP = true;
    this->receiveTimeout.attach(2, this->brakeReceive);
    udp.begin(UDP_PORT_RX);
    while (this->canWaitUDP) {
        packetSize = this->udp.parsePacket();
        if (packetSize) {
            log0("Received udp data");
            this->brakeReceive();
            this->udp.read(this->incomingUDP, UDP_RECEIVE_PACKET_SIZE);
            this->taskCallback(this->incomingUDP);
        }
    }
}

void OSClass::brakeReceive(void) {
    log0("Braking receive link");
    this->canWaitUDP = false;
    this->receiveTimeout.detach();
}

void OSClass::onDataReceived(r_callback_t f) {
    this->taskCallback = f;
}

/*
 * Time in milliseconds
 */
void OSClass::shutdown(uint32 sleepTime) {
    this->beacon.saveElapsedTime();
    if (sleepTime > BEACON_PERIOD) {
        ESP.deepSleep(sleepTime, WAKE_NO_RFCAL);
    }
}

OSClass OS;
