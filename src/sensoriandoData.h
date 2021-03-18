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
#define CMD_UPD     0x21    //update param in module
#define CMD_PAIR    0x22    //start pairing

#define UUID_LEN    37      //36 byte UUID + 1


/*
 * GlobalVariables
 */
typedef struct _Sensoriando {
    char uuid[UUID_LEN];
    time_t dt;
    float value;
    char msg[256];
    int id;
} SensoriandoParser;

typedef struct _SensorDatum {
/*
 * syn | stx  | uuid | id      | value | dt        | etx
 * -----------------------------------------------------
 * SYN | STX  | char | 0~65536 | float | timestamp | ETX
 */
    char uuid[UUID_LEN];  //36 bits
    float value;    //32 bits
    time_t dt;      //32 bits
    uint16_t id;
    uint8_t stx;
    uint8_t etx;
} __attribute__((packed, aligned(1))) SensoriandoSensorDatum;

typedef struct _WifiCommandResult {
/*
 * syn | stx | cmd   | res   | etx
 * -------------------------------
 * SYN | STX | 0~255 | 0~255 | ETX
 */
    uint8_t stx;
    uint8_t cmd;
    uint8_t res;
    uint8_t etx;
} __attribute__((packed, aligned(1))) SensoriandoWifiCommandResult;

typedef struct _WifiCommandInit {
/*
 * syn | stx | cmd      | param     | etx
 * --------------------------------------
 * SYN | STX | CMD_INIT | unixtime  | ETX
 */
    time_t param;       //32 bits
    uint8_t stx;
    uint8_t cmd;
    uint8_t etx;
} __attribute__((packed, aligned(1))) SensoriandoWifiCommandInit;


/*
 * Prototypes
 */
int8_t sensoriandoGenCrc(int8_t *);

#endif
