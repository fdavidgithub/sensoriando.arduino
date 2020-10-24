/*
 * Description
 */
#ifndef SENSORIANDO_H
#define SENSORIANDO_H

#include <Arduino.h>
#include <time.h>

#ifndef SENSORIANDODATA_H
    #include "sensoriandoData.h"
#endif

/*
 * MACROS
 */
#define DEBUG


#define BROKER          "broker.sensoriando.com.br"
#define BROKER_PORT     1883

/*
 * prototypes
 */
void sensoriandoSendValue(SensoriandoParser *, char*, char *);
void sensoriandoSendDatetime(SensoriandoParser *, char*, char *);
void sensoriandoSendStorage(SensoriandoParser *, char*, char*);
void sensoriandoSendMessage(SensoriandoParser *, char*, char*); 

#endif

