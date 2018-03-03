//
// Created by Aaron Russo on 19/02/2018.
//

#ifndef ESP8266_OTA_H
#define ESP8266_OTA_H


class OTAClass {
public:
    void init(void);
    void handle(void);
};

extern OTAClass OTA;


#endif //ESP8266_OTA_H
