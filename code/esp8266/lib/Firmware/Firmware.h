//
// Created by Aaron Russo on 23/02/2018.
//
// Include your custom firmware here.
// A firmware must define 4 functions
// firmwareInit, firmwareExec, firmwareTxHandle(int*), int* firmwareRxHandle(), EXECUTION_INTERVAL_US
//
// Example:
// #include <Boiler.h>
//

//
///////////////////////////////////////////////

#ifndef ESP8266_FIRMWARE_H
#define ESP8266_FIRMWARE_H

#if defined(firmwareInit) && \
    defined(firmwareExec) && \
    defined(firmwareTxHandler) && \
    defined(firmwareRxHandler) && \
    defined(EXECUTION_INTERVAL_US)
#define HAS_FIRMWARE true
#else
#define HAS_FIRMWARE false
#define firmwareInit()
#define firmwareExec()
#define firmwareTxHandler() NULL
#define firmwareRxHandler(a)
#define firmwareSleepInterval() 0
#endif

#endif //ESP8266_FIRMWARE_H
