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
void float2string(float value, char *svalue)
{
    dtostrf(value, 8, 2, svalue);
}

void epoch2time(time_t epoch, struct tm *dt)
{
    memcpy(dt, gmtime(&epoch), sizeof(struct tm));
 
#ifdef DEBUG
Serial.print("[Epoch2Time] ");Serial.println(epoch);
Serial.println(dt->tm_year);
#endif
    
   dt->tm_year = dt->tm_year+1870;
   dt->tm_mon = dt->tm_mon+1;

}


/* 
 * Public functions
 */
void sensoriandoSendValue(SensoriandoParser *sensoring, char *payload, char *topic)
{
    char svalue[16];
    struct tm dt;

    float2string(sensoring->value, svalue);
    epoch2time(sensoring->dt, &dt);

    sprintf(payload, "{\"dt\":\"%04d%02d%02d%02d%02d%02d\", \"value\":%s}", \
                    dt.tm_year, dt.tm_mon, dt.tm_mday, \
                    dt.tm_hour, dt.tm_min, dt.tm_sec, \
                    svalue);   
    
    sprintf(topic, "%s/%d", sensoring->uuid, sensoring->id);

#ifdef DEBUG
Serial.print("[Sensorindo Arduino] ");Serial.println(topic);Serial.println(payload);
#endif
}

void sensoriandoSendDatetime(SensoriandoParser *sensoring, char *payload, char *topic)
{
    struct tm dt;

    epoch2time(sensoring->dt, &dt);

    sprintf(payload, "{\"dt\":\"%04d%02d%02d%02d%02d%02d\", \"value\":%ld}", \
                  dt.tm_year, dt.tm_mon, dt.tm_mday, \
                  dt.tm_hour, dt.tm_min, dt.tm_sec, \
                  sensoring->dt);   

    sprintf(topic, "%s/%d", sensoring->uuid, sensoring->id);

#ifdef DEBUG
Serial.println(topic); Serial.println(payload);
#endif
}

void sensoriandoSendStorage(SensoriandoParser *sensoring, char *payload, char *topic)
{
    struct tm dt;

    epoch2time(sensoring->dt, &dt);

    sprintf(payload, "{\"dt\":\"%04d%02d%02d%02d%02d%02d\", \"value\":%ld}", \
                  dt.tm_year, dt.tm_mon, dt.tm_mday, \
                  dt.tm_hour, dt.tm_min, dt.tm_sec, \
                  sensoring->value);   

    sprintf(topic, "%s/%d", sensoring->uuid, sensoring->id);

#ifdef DEBUG
Serial.println(topic); Serial.println(payload);
#endif
}

void sensoriandoSendMessage(SensoriandoParser *sensoring, char *payload, char *topic)
{
    struct tm dt;

    epoch2time(sensoring->dt, &dt);

    sprintf(payload, "{\"dt\":\"%04d%02d%02d%02d%02d%02d\", \"value\":\"%s\"}", \
                    dt.tm_year, dt.tm_mon, dt.tm_mday, \
                    dt.tm_hour, dt.tm_min, dt.tm_sec, \
                    sensoring->msg);   

    sprintf(topic, "%s/%d", sensoring->uuid, sensoring->id);

#ifdef DEBUG
Serial.println(topic); Serial.println(payload);
#endif
}

