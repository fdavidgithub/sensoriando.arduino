/*
 * Description
 */
#ifndef SDK_H
#define SDK_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <time.h>
#include "log.h"
#include "sensoriandoData.h"


/*
 * MACROS
 */
//#define DEBUG_SDK

#ifdef DEBUG_SDK
#define LOGGER_SDK(string, ...)       logargs(string, ##__VA_ARGS__)
#else
#define LOGGER_SDK(string, ...)       do {} while(0)
#endif

#define ARRAY_LEN           256

#define BROKER              "broker.sensoriando.com.br"
#define BROKER_PORT         1883
#define BROKER_USER         "fdavid"
#define BROKER_PASSWD       "12345678"
#define BROKER_CLIENTNAME   "Sensoriando"

#define SYSTEM_RTC          1
#define SYSTEM_STORAGE      2
#define SYSTEM_MESSAGE      3

typedef PubSubClient SensoriandoObj;


/*
 * prototypes
 */
byte sensoriandoInit(SensoriandoObj *, uint8_t *);
byte sensoriandoReconnect(SensoriandoObj *, uint8_t *);
 
byte sensoriandoSendValue(SensoriandoObj *, SensoriandoParser *);
byte sensoriandoSendDatetime(SensoriandoObj *, SensoriandoParser *);
byte sensoriandoSendStorage(SensoriandoObj *, SensoriandoParser *);
byte sensoriandoSendMessage(SensoriandoObj *, SensoriandoParser *);

#endif

