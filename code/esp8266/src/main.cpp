//
// Created by Aaron Russo on 17/02/2018.
//

#include <Arduino.h>
#include <LogLog.h>
#include <OS.h>
#include <Firmware.h>

void setup() {
    logger.begin();
    OS.boot();
    OS.onDataReceived([](char *data) {
        firmwareRxHandler(data);
    });
    firmwareInit();
}

void loop() {
    firmwareExec();
    OS.transmission(firmwareTxHandler());
    OS.shutdown(firmwareSleepInterval());
}

/*
 * > BOOT <
 * 1A - Check if first start ever (also might want to check esp boot flag), fresh flashed. [YES -> Next | NO -> 1D]
 * 2A - Create web prompt ask wifi ssid, wifi password and device name.
 * 3A - Try to join network, success? [YES -> Next | NO -> 2A]
 * 4A - Store wifi ssid and password.
 * 5A - Download and write custom firmware, reset. [-> 1A]
 *
 * > WIFI CONNECTION <
 * 1B - Is CYA flag set? [NO -> Next | Yes -> 5B]
 * 2B - Load wifi ssid and password, attempt connection, success? [NO -> Next | YES -> 9B]
 * 3B - Reached maximum number of attempts? [No -> Next | Yes -> 5B]
 * 4B - Handle connection error if possible (maybe save for cya?) and store attempts counter. [-> 9C]
 * 5B - Is connection critical? (e.g. Beacon transmission needed?) [Yes -> Next | No -> 8B]
 * 6B - Go in Access Point Mode for 1 Minute, reset beacon timeout, request help from Base Station.
 * 7B - Did we get a solution from Base Station? [NO -> Next | Yes -> 2B]
 * 8B - CYA, set CYA flag if reset. [-> 3D]
 * 9B - Ok, reset CYA flag if set. [-> 6C]
 *
 * > WIFI TRANSMISSION AND RECEPTION <
 * 1C - Is availability beacon needed (elapsed time from last beacon). [Yes -> Next | No -> 3C]
 * 2C - Include beacon with transmission packet.
 * 3C - If needed, include task data with transmission packet.
 * 4C - If available, append buffered packets.
 * 5C - Is transmission needed by beacon or task? [Yes -> 1B | No -> 3D]
 * 6C - Transmit data packet.
 * 7C - Do we have to receive an answer from base station? [Yes -> Next | No -> 3D]
 * 8C - Wait 2 seconds, and handle received packets.
 * 9C - Store any other data if needed (eg transmission packet on connection error) and goodbye. [-> 3D]
 *
 * > CUSTOM FIRMWARE <
 * 1D - Execute assigned task, maximum time allowed 15 seconds (preemptable?). - Custom Firmware dependant
 * 2D - Handle data transmission. [-> 1C]
 * 3D - Deep sleep some time. - Time defined by Custom Firmware (maximum allowed is beacon time) [-> 1A]
 *
 */