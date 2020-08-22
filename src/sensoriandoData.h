/*
 * Description
 */
#ifndef SENSORIANDODATA_H
#define SENSORIANDODATA_H

#include <Arduino.h>

/*
 * MACROS
 */
#define STX 0x02    //start of text
#define ETX 0x03    //end of text

/*
 * GlobalVariables
 */
typedef struct _SensorDatum {
    byte stx;
    int id;
    float value;
    byte etx;
} SensoriandoSensorDatum;

/*
 * Prototypes
 */
int8_t sensoriandoGenCrc(int8_t *);

#endif
