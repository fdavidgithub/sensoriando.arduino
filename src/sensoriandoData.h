/*
 * Description
 */
#ifndef SENSORIANDODATA_H
#define SENSORIANDODATA_H

#include <stdint.h>
#include <time.h>


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
 * stx  | id      | value | dt        | etx
 * ----------------------------------------
 * STX  | 0~65536 | float | timestamp | ETX
 */
    float value;    //32 bits
    time_t dt;      //32 bits
    uint16_t id;
    uint8_t stx;
    uint8_t etx;
} SensoriandoSensorDatum;

typedef struct _WifiCommandResult {
/*
 * stx | cmd   | res   | etx
 * -------------------------
 * STX | 0~255 | 0~255 | ETX
 */
    uint8_t stx;
    uint8_t cmd;
    uint8_t res;
    uint8_t etx;
} SensoriandoWifiCommandResult;

typedef struct _WifiCommandInit {
/*
 * stx | cmd      | param     | etx
 * --------------------------------
 * STX | CMD_INIT | unixtime  | ETX
 */
    time_t param;       //32 bits
    uint8_t stx;
    uint8_t cmd;
    uint8_t etx;
    uint8_t padding;    //ignore, memory layout for 32 bits architecture
} SensoriandoWifiCommandInit;


/*
 * Prototypes
 */
int8_t sensoriandoGenCrc(int8_t *);

#endif
