#include "log.h"

void logargs(char *string, ...)
{
    char buffer[256];
    va_list args;
    
    va_start(args, string);
    vsnprintf(buffer, sizeof(buffer), string, args);
    va_end(args);

    Serial.printf("[SDK] ");
    Serial.println(buffer);
}

