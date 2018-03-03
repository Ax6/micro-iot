//
// Created by Aaron Russo on 21/02/2018.
//

#ifndef ESP8266_BOOT_H
#define ESP8266_BOOT_H

#include <functional>
#include <WiFiUdp.h>
#include <Beacon.h>
#include <Ticker.h>

#define UDP_IP_TX "192.168.1.155"
#define UDP_PORT_TX 3555
#define UDP_PORT_RX 3556
#define UDP_RECEIVE_PACKET_SIZE 255

typedef void(*r_callback_t)(char *);

typedef enum {
    TIME_FROM_LAST_BEACON = 0,
    DATA0 = 2
} fileAddress;

typedef enum {
    BEACON_TIME
} kernelAddress;

class OSClass {
private:
    WiFiUDP udp;
    Beacon beacon;
    Ticker receiveTimeout;
    char incomingUDP[UDP_RECEIVE_PACKET_SIZE];
    bool canWaitUDP;

    r_callback_t taskCallback;

    void transmit(char *data, char dataSize);

    void receive(void);

    void brakeReceive(void);

public:
    void boot(void);

    void createWiFiPrompt(void);

    bool hasFirmware(void);

    void onDataReceived(r_callback_t f);

    void shutdown(uint32);

    void transmission(char *data);

    void connect();

    void disconnect();
};

extern OSClass OS;


#endif //ESP8266_BOOT_H
