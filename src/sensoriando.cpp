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
byte sensoriandoInit(SensoriandoObj *obj)
{
    byte res;
    
    obj->setServer(BROKER, BROKER_PORT);  
    res = obj->connect("Sensoriando", BROKER_USER, BROKER_PASSWD);
    return res;
}

byte sensoriandoReconnect(SensoriandoObj *obj) 
{
    if ( !obj->connected() ) {
#ifdef DEBUG_MQTT
        Serial.print("Attempting MQTT connection...");
#endif
        if ( obj->connect("Sensoriando", BROKER_USER, BROKER_PASSWD)) {
#ifdef DEBUG_MQTT
            Serial.println("Broker Connected");
#endif

        } else {
#ifdef DEBUG_MQTT
            Serial.print("failed, rc=");
            Serial.print(obj->state());
#endif      
        }
    }

    return obj->connected();
}

void sensoriandoSendValue(SensoriandoObj *obj, SensoriandoParser *sensoring)
{
    char payload[ARRAY_LEN], topic[ARRAY_LEN];
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

    obj->publish(topic, payload);   
}

void sensoriandoSendDatetime(SensoriandoObj *obj, SensoriandoParser *sensoring)
{
    char payload[ARRAY_LEN], topic[ARRAY_LEN];
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

    obj->publish(topic, payload);
}

void sensoriandoSendStorage(SensoriandoObj *obj, SensoriandoParser *sensoring)
{
    char payload[ARRAY_LEN], topic[ARRAY_LEN];
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

    obj->publish(topic, payload);
}

void sensoriandoSendMessage(SensoriandoObj *obj, SensoriandoParser *sensoring)
{
    char payload[ARRAY_LEN], topic[ARRAY_LEN];
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

    obj->publish(topic, payload);
}

