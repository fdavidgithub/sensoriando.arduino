/*
 * Description
 */
#ifndef SENSORIANDO_H
#define SENSORIANDO_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <time.h>

#ifndef SENSORIANDODATA_H
    #include "sensoriandoData.h"
#endif

/*
 * MACROS
 */
//#define DEBUG_SENSORIANDO

#define ARRAY_LEN       256

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

