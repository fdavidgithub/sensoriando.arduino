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
 
#ifdef DEBUG_SENSORIANDO
Serial.print("[Epoch2Time] ");Serial.println(epoch);
Serial.println(dt->tm_year);
#endif
    
   dt->tm_year = dt->tm_year+1870;
   dt->tm_mon = dt->tm_mon+1;

}

void genname(char *namedevice, uint8_t *mac)
{
    for (int i=0; i<sizeof(mac); i++) {
        sprintf(namedevice, "%s%02X", namedevice, mac[i]);
    }
    
#ifdef DEBUG_SENSORIANDO
    Serial.print("[DEBUG SENSORIANDO] ");
    Serial.println(namedevice);
#endif
}


/* 
 * Public functions
 */
byte sensoriandoInit(SensoriandoObj *obj, uint8_t *mac)
{
    byte res;
    char namedevice[30] = BROKER_CLIENTNAME;

    genname(namedevice, mac);

    obj->setServer(BROKER, BROKER_PORT);  
    res = obj->connect(namedevice, BROKER_USER, BROKER_PASSWD);

    return res;
}

byte sensoriandoReconnect(SensoriandoObj *obj, uint8_t *mac) 
{
    char namedevice[30] = BROKER_CLIENTNAME;

    if ( !obj->connected() ) {
        genname(namedevice, mac);

#ifdef DEBUG_SENSORIANDO
        Serial.print("Attempting MQTT connection...");
#endif
        if ( obj->connect(namedevice, BROKER_USER, BROKER_PASSWD)) {
#ifdef DEBUG_SENSORIANDO
            Serial.println("Broker Connected");
#endif
        } else {
#ifdef DEBUG_SENSORIANDO
            Serial.print("failed, rc=");
            Serial.print(obj->state());
#endif      
        }
    }

    return obj->connected();
}

byte sensoriandoSendValue(SensoriandoObj *obj, SensoriandoParser *sensoring)
{
    char payload[ARRAY_LEN], topic[ARRAY_LEN];
    char svalue[16];
    struct tm dt;
    byte res;

    float2string(sensoring->value, svalue);

    if ( sensoring->dt ) {
        epoch2time(sensoring->dt, &dt);
        sprintf(payload, "{\"dt\":\"%04d%02d%02d%02d%02d%02d\", \"value\":%s}", \
                        dt.tm_year, dt.tm_mon, dt.tm_mday, \
                     dt.tm_hour, dt.tm_min, dt.tm_sec, \
                     svalue);   
    } else {
        sprintf(payload, "{\"value\":%s}", svalue);      
    }

    sprintf(topic, "%s/%d", sensoring->uuid, sensoring->id);

    res = obj->publish(topic, payload);   

#ifdef DEBUG_SENSORIANDO
Serial.print("[DEBUG_SENSORIANDO] ");
Serial.println(topic);
Serial.println(payload);
#endif

    return res;
}


byte sensoriandoSendDatetime(SensoriandoObj *obj, SensoriandoParser *sensoring)
{
    char payload[ARRAY_LEN], topic[ARRAY_LEN];
    struct tm dt;
    byte res;

    if ( sensoring->dt ) {
        epoch2time(sensoring->dt, &dt);
        sprintf(payload, "{\"dt\":\"%04d%02d%02d%02d%02d%02d\", \"value\":%ld}", \
                  dt.tm_year, dt.tm_mon, dt.tm_mday, \
                  dt.tm_hour, dt.tm_min, dt.tm_sec, \
                  sensoring->dt);   
    } else {
        sprintf(payload, "{\"value\":%ld}", sensoring->dt);       
    }

    if ( ! sensoring->id ) {
        sensoring->id = SYSTEM_RTC;
    }

    sprintf(topic, "%s/%d", sensoring->uuid, sensoring->id);

    res = obj->publish(topic, payload);

#ifdef DEBUG_SENSORIANDO
Serial.println(topic); Serial.println(payload);
#endif

    return res;
}

byte sensoriandoSendStorage(SensoriandoObj *obj, SensoriandoParser *sensoring)
{
    char payload[ARRAY_LEN], topic[ARRAY_LEN];
    char svalue[16];
    struct tm dt;
    byte res;

    float2string(sensoring->value, svalue);

    if ( sensoring->dt ) {
        epoch2time(sensoring->dt, &dt);
        sprintf(payload, "{\"dt\":\"%04d%02d%02d%02d%02d%02d\", \"value\":%s}", \
                  dt.tm_year, dt.tm_mon, dt.tm_mday, \
                  dt.tm_hour, dt.tm_min, dt.tm_sec, \
                  svalue);   
    } else {
        sprintf(payload, "{\"value\":%s}", svalue);        
    }

    if ( ! sensoring->id ) {
        sensoring->id = SYSTEM_STORAGE;
    }

    sprintf(topic, "%s/%d", sensoring->uuid, sensoring->id);

    res = obj->publish(topic, payload);

#ifdef DEBUG_SENSORIANDO
Serial.println(sensoring->value);
Serial.println(topic); Serial.println(payload);
#endif

    return res;
}

byte sensoriandoSendMessage(SensoriandoObj *obj, SensoriandoParser *sensoring)
{
    char payload[ARRAY_LEN], topic[ARRAY_LEN];
    struct tm dt;
    byte res;

    if ( sensoring->dt ) {
        epoch2time(sensoring->dt, &dt);
        sprintf(payload, "{\"dt\":\"%04d%02d%02d%02d%02d%02d\", \"value\":\"%s\"}", \
                    dt.tm_year, dt.tm_mon, dt.tm_mday, \
                    dt.tm_hour, dt.tm_min, dt.tm_sec, \
                    sensoring->msg);   
    } else {
        sprintf(payload, "{\"value\":\"%s\"}", sensoring->msg);         
    }

    if ( ! sensoring->id ) {
        sensoring->id = SYSTEM_MESSAGE;
    }

    sprintf(topic, "%s/%d", sensoring->uuid, sensoring->id);

    res =  obj->publish(topic, payload);

#ifdef DEBUG
Serial.println(topic); Serial.println(payload);
#endif

    return res;
}

