//
// Created by Aaron Russo on 24/02/2018.
//

#ifndef ESP8266_CONNECTION_H
#define ESP8266_CONNECTION_H

#include <c_types.h>

#define BEACON_PERIOD 3600000 //1 hour (Millis time)

class Beacon {
private:
    uint32 savedElapsedTime;

    uint32 getElapsedTime(void);

    uint32 millisSinceReset = 0;

public:

    void init(void);

    bool isNeeded(void);

    uint32 readSavedElapsedTime(void);

    void saveElapsedTime(void);

    void reset(void);

    void setAsSent(void);
};

#endif //ESP8266_CONNECTION_H
