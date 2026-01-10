#include "stm32f4xx.h" // Device header

#define VREF 3.3f      // Reference voltage (assuming 3.3V)
#define ADC_MAX 4095    // Maximum ADC value for 12-bit resolution

// Function to initialize ADC
void ADC_Init(void) {
    // Enable clock for GPIOA and ADC1
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // Configure PA1 as analog mode
    GPIOA->MODER |= GPIO_MODER_MODER1;

    // ADC configuration
    ADC1->CR1 = 0;  // Disable ADC
    ADC1->CR2 = ADC_CR2_ADON;  // Turn on ADC (ADON bit)
    ADC1->SQR3 = 1;  // Select channel 1

    // You might need additional configuration here (e.g., sampling time, resolution)
}

// Function to convert ADC value to voltage
float adcToVoltage(uint16_t adcValue) {
    return (adcValue * VREF) / ADC_MAX;
}

// Function to perform ADC conversion
void performADCConversion(void) {
    // Start ADC conversion
    ADC1->CR2 |= ADC_CR2_SWSTART;

    // Wait for a short delay (adjust as needed based on your application)
    for (volatile int i = 0; i < 1000; ++i)
        __NOP();  // Use __NOP() as a simple delay, replace with proper delay function if available

    // Wait for conversion to complete
    while (!(ADC1->SR & ADC_SR_EOC));
}

int main(void) {
    // Initialize ADC
    ADC_Init();

    int analogValue;
    float voltage;

    while (1) {
        // Perform ADC conversion
        performADCConversion();

        // Read ADC value
        analogValue = ADC1->DR;

        // Convert ADC value to voltage
        voltage = adcToVoltage(analogValue);

        // Add your application logic here

    } // Missing closing brace here
}