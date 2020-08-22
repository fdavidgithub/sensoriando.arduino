/*
 * Description
 */
#ifndef SENSORIANDO_H
#define SENSORIANDO_H

#include <Arduino.h>
#include <RTClib.h>

#ifndef SENSORIANDODATA_H
    #include "sensoriandoData.h"
#endif

/*
 * MACROS
 */
//#define DEBUG

#define MESSAGE_ID      2   //id for message on Sensoriando
#define TIME_ID         1   //id for time rtc on Sensoriando
#define STORAGE_ID      12  //id for storage on Sensoriando

#define BROKER          "broker.sensoriando.com.br"
#define BROKER_UUID     "27c36465-7356-4fe7-b726-cf619a9a22f0"
#define BROKER_PORT     1883

/*
 * prototypes
 */
void sensoriandoSendValue(DateTime, float, int, char*, char*);
void sensoriandoSendDatetime(DateTime, long, char*, char*);
void sensoriandoSendStorage(DateTime, float, char*, char*);
void sensoriandoSendMessage(DateTime, char*, char*, char*); 

#endif

