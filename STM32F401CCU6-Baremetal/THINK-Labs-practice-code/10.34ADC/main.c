#include "stm32f4xx.h" // Device header
#include "/Library/USART2.h"
#include "/Library/ST32F4_DELAY.h"


#define VREF 3.3f  // Reference voltage (assuming 3.3V)
#define ADC_MAX 4095  // Maximum ADC value for 12-bit resolution

// Function to initialize ADC
void ADC_Init(void) {
    // Enable clock for GPIOA and ADC1
    RCC->AHB1ENR |= 0x01;
    RCC->APB2ENR |= (1<<8);

    // Configure PA1 as analog mode
    GPIOA->MODER |= (1<<0)|(1<<1);

    // ADC configuration
    ADC1->CR1 = 0;  // Disable ADC
    ADC1->CR2 = 1;  // Turn on ADC
    ADC1->SQR3 = 1;  // Select channel 1
}

// Function to convert ADC value to voltage
float adcToVoltage(uint16_t adcValue) {
    return (adcValue * VREF) / ADC_MAX;
}

int main(void) {
    // Initialize ADC
    ADC_Init();
		USART2_Init();

    int analogValue;
    float voltage;

    while (1) {
        // Start ADC conversion
        ADC1->CR2 |= ADC_CR2_SWSTART;

        // Wait for conversion to complete
        while (!(ADC1->SR & ADC_SR_EOC));
        analogValue = ADC1->DR; // Read ADC value
        voltage = adcToVoltage(analogValue); // Convert ADC value to voltage
				printf("Voltage: %d \r\n", analogValue);
				SysTickDelayMs(100);

	}
}