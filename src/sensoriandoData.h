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
/*
 * stx  | id      | value | etx
 * ----------------------------
 * STX  | 0~65536 | float | ETX
 */
    float value;
    uint16_t id;
    uint8_t stx;
    uint8_t etx;
} SensoriandoSensorDatum;

typedef struct _WifiCommand {
/*
 * stx  | cmd  | etx
 * -----------------
 * STX | 0~255 | ETX
 */
    uint8_t stx;
    uint8_t cmd;               //Command/Status
    uint8_t etx;
} SensoriandoWifiCommand;


/*
 * Prototypes
 */
//int8_t sensoriandoGenCrc(int8_t *);

#endif
