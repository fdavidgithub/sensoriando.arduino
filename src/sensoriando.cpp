#include "sensoriando.h"

/*
 * If you have ever tried to use sprintf() on an Arduino (on ESP it work) 
 * to convert from a float to a string, the function will most likely return a ?.
 *
 * sprintf(msg, "{\"dt\":\"%04d%02d%02d%02d%02d%02d\", \"value\":%f}", \
 *                   dt.year(), dt.month(), dt.day(), \
 *                   dt.hour(), dt.minute(), dt.second(), \
 *                   value);   
 */
void sensoriandoSendValue(DateTime dt, float value_sensor, int id_sensor, char* msg, char* topic)
{
    char svalue[16];
    dtostrf(value_sensor, 8, 2, svalue);

    sprintf(msg, "{\"dt\":\"%04d%02d%02d%02d%02d%02d\", \"value\":%s}", \
                    dt.year(), dt.month(), dt.day(), \
                    dt.hour(), dt.minute(), dt.second(), \
                    svalue);   
    sprintf(topic, "%s/%d", BROKER_UUID, id_sensor);

#ifdef DEBUG
Serial.println(topic); Serial.println(msg);
#endif
}

void sensoriandoSendDatetime(DateTime dt, long value_dt, char* msg, char* topic)
{
    sprintf(msg, "{\"dt\":\"%04d%02d%02d%02d%02d%02d\", \"value\":%ld}", \
                  dt.year(), dt.month(), dt.day(), \
                  dt.hour(), dt.minute(), dt.second(), \
                  value_dt);   
    sprintf(topic, "%s/%d", BROKER_UUID, TIME_ID);

#ifdef DEBUG
Serial.println(topic); Serial.println(msg);
#endif
}

void sensoriandoSendStorage(DateTime dt, float value, char* msg, char* topic)
{
    char svalue[16];
    dtostrf(value, 8, 2, svalue);

    sprintf(msg, "{\"dt\":\"%04d%02d%02d%02d%02d%02d\", \"value\":%s}", \
                  dt.year(), dt.month(), dt.day(), \
                  dt.hour(), dt.minute(), dt.second(), \
                  svalue);   
    sprintf(topic, "%s/%d", BROKER_UUID, STORAGE_ID);

#ifdef DEBUG
Serial.println(topic); Serial.println(msg);
#endif
}

void sensoriandoSendMessage(DateTime dt, char* msg, char* topicmsg, char* topic)
{
    sprintf(topicmsg, "{\"dt\":\"%04d%02d%02d%02d%02d%02d\", \"value\":\"%s\"}", \
                    dt.year(), dt.month(), dt.day(), \
                    dt.hour(), dt.minute(), dt.second(), \
                    msg);   
    sprintf(topic, "%s/%d", BROKER_UUID, MESSAGE_ID);

#ifdef DEBUG
Serial.println(topic); Serial.println(topicmsg);
#endif
}

