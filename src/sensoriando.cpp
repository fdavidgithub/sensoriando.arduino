#include "sensoriando.h"
//#define DEBUG

void sensoriandoSendValue(DateTime dt, float value_sensor, int id_sensor, char* msg, char* topic)
{
    sprintf(msg, "{\"dt\":\"%04d%02d%02d%02d%02d%02d\", \"value\":%f}", \
                    dt.year(), dt.month(), dt.day(), \
                    dt.hour(), dt.minute(), dt.second(), \
                    value_sensor);   
    sprintf(topic, "%s/%d", UUID, id_sensor);

#ifdef DEBUG
Serial.println(topic); Serial.println(msg);
#endif
}

void sensoriandoSendDatetime(DateTime dt, int value_dt, char* msg, char* topic)
{
    sprintf(msg, "{\"dt\":\"%04d%02d%02d%02d%02d%02d\", \"value\":%d}", \
                  dt.year(), dt.month(), dt.day(), \
                  dt.hour(), dt.minute(), dt.second(), \
                  value_dt);   
    sprintf(topic, "%s/%d", UUID, TIME_ID);

#ifdef DEBUG
Serial.println(topic); Serial.println(msg);
#endif
}

void sensoriandoSendMessage(DateTime dt, char *msg, char* topicmsg, char* topic)
{
    sprintf(topicmsg, "{\"dt\":\"%04d%02d%02d%02d%02d%02d\", \"value\":\"%s\"}", \
                    dt.year(), dt.month(), dt.day(), \
                    dt.hour(), dt.minute(), dt.second(), \
                    msg);   
    sprintf(topic, "%s/%d", UUID, MESSAGE_ID);

#ifdef DEBUG
Serial.println(topic); Serial.println(topicmsg);
#endif
}

