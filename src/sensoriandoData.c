#include "sensoriandoData.h"

int8_t sensoriandoGenCrc(int8_t *stream)
{
    uint8_t crc = 0xff;
    size_t i, j, len;

    for (len=0; len<sizeof(stream);len++) {
        if (stream[len] == ETX) {
            break;
        }
    }
    
    for (i = 0; i < len; i++) {
        crc ^= stream[i];
        
        for (j = 0; j < 8; j++) {
            if ((crc & 0x80) != 0)
                crc = (uint8_t)((crc << 1) ^ 0x31);
            else
                crc <<= 1;
        }
    }
    
    return crc;
}


