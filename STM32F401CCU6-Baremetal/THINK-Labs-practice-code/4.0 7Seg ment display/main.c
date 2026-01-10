#include "stm32f4xx.h"

// Define segment patterns for digits 0-9
const uint16_t digitPatterns[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

// Function to display a digit on a specific 7-segment display
void displayDigit(uint8_t digit, uint8_t segmentMask) {
    GPIOA->BSRR = 0xFFFF; // Clear the segments
    GPIOA->BSRR = ((uint32_t)digitPatterns[digit] << 0) | (uint32_t)segmentMask;
}

void delay(volatile uint32_t count) {
    for (; count != 0; count--);
}

int main(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable the clock for GPIOA

    GPIOA->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0; // Set PA0-PA3 as output

    while (1) {
        // Display digit 0 on the first 7-segment display
        displayDigit(0, GPIO_BSRR_BS0 | GPIO_BSRR_BS1 | GPIO_BSRR_BS2 | GPIO_BSRR_BS3);

        delay(1000000); // Delay for a while

        // Display digit 1 on the second 7-segment display
        displayDigit(1, GPIO_BSRR_BS0 | GPIO_BSRR_BS1 | GPIO_BSRR_BS2 | GPIO_BSRR_BS3);

        delay(1000000); // Delay for a while
    }
}
