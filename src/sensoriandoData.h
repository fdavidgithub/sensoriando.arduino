/*
 * Description
 */
#ifndef SENSORIANDODATA_H
#define SENSORIANDODATA_H

#include <Arduino.h>


/*
 * MACROS
 */
#define STX         0x02    //start of text
#define ETX         0x03    //end of text
#define ACK         0x06    //acknowledge
#define NAK         0x15    //negative acknowledge
#define SYN         0x16    //synchronous idle

#define CMD_INIT    0x20    //check module is init

/*
 * GlobalVariables
 */
typedef struct _SensorDatum {
    byte stx;
    int id;
    float value;
    byte etx;
} SensoriandoSensorDatum;

typedef struct _WifiCommand {
    byte stx;
    byte cmd;               //Command/Status
    byte etx;
} SensoriandoWifiCommand;


/*
 * Prototypes
 */
//int8_t sensoriandoGenCrc(int8_t *);

#endif
