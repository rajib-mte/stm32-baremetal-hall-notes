
#ifndef DHT11_H
#define DHT11_H

#include "main.h"

/* DHT11 data structure */
typedef struct
{
    uint8_t humidity;
    uint8_t temperature;
} DHT11_Data_t;

/* Function prototypes */
void DHT11_Init(void);

uint8_t DHT11_ReadData(DHT11_Data_t *data);

#endif
