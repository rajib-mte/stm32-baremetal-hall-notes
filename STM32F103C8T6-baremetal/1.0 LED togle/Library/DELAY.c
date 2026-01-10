#include "DELAY.h"
void delay(uint32_t ms) {
    volatile uint32_t i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 2000; j++); // Adjust as needed
}