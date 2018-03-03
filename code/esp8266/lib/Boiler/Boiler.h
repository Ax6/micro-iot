//
// Created by Aaron Russo on 23/02/2018.
//

#ifndef ESP8266_BOILER_H
#define ESP8266_BOILER_H

#define firmwareInit() boiler.init()
#define firmwareExec() boiler.exec()
#define firmwareTxHandler() boiler.transmissionHandler()
#define firmwareRxHandler(a) boiler.receiverHandler(a)
#define firmwareSleepInterval() 600000 //10 Minutes

class Boiler {
public:
    void init(void);
    bool exec(void);
    char* transmissionHandler(void);
    bool receiverHandler(int*);
};

extern Boiler boiler;

#endif //ESP8266_BOILER_H
