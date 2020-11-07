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

#define BROKER          "broker.sensoriando.com.br"
#define BROKER_PORT     1883
#define BROKER_USER     "fdavid"
#define BROKER_PASSWD   "12345678"

typedef PubSubClient SensoriandoObj;


/*
 * prototypes
 */
byte sensoriandoInit(SensoriandoObj *);
byte sensoriandoReconnect(SensoriandoObj *);
 
void sensoriandoSendValue(SensoriandoObj *, SensoriandoParser *);
void sensoriandoSendDatetime(SensoriandoObj *, SensoriandoParser *);
void sensoriandoSendStorage(SensoriandoObj *, SensoriandoParser *);
void sensoriandoSendMessage(SensoriandoObj *, SensoriandoParser *);

#endif

