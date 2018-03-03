//
// Created by Aaron Russo on 19/02/2018.
//

#ifndef ESP8266_LOGLOG_H
#define ESP8266_LOGLOG_H

#define logLevel0
#define BAUD_RATE 115200


#ifdef logLevel0
#define log0(a) (Serial.println(a))
#define log00(a, b) (Serial.println(a, b))
#define log1(a)
#define log2(a)
#elif defined logLevel1
#define log0(a) (Serial.println(a))
#define log00(a, b) (Serial.println(a, b))
#define log1(a) (Serial.println(a))
#define log2(a)
#elif defined logLevel2
#define log0(a) (Serial.println(a))
#define log00(a, b) (Serial.println(a, b))
#define log1(a) (Serial.println(a))
#define log2(a) (Serial.println(a))
#else
#define log0(a)
#define log1(a)
#define log2(a)
#endif

class LogLog{
public:
    void begin(void);
};

extern LogLog logger;

#endif //ESP8266_LOGLOG_H
