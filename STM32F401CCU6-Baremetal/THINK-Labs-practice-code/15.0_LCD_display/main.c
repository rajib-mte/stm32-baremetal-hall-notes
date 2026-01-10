#include "stm32f4xx_hal.h"

// LCD control pins
#define RS_PIN GPIO_PIN_0
#define E_PIN GPIO_PIN_1
#define DATA_PORT GPIOA

// Function prototypes
void LCD_Command(uint8_t command);
void LCD_Data(uint8_t data);
void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_WriteString(const char* str);

int main(void) {
    HAL_Init();
    SystemClock_Config();

    // Initialize the HAL Library
    HAL_InitTick(0); // Set the HAL time base to 1ms

    // Initialize GPIO and LCD
    __HAL_RCC_GPIOA_CLK_ENABLE();
    LCD_Init();

    // Clear the LCD and set the cursor to the first row
    LCD_Clear();
    LCD_SetCursor(0, 0);

    // Display a message on the LCD
    LCD_WriteString("Hello, STM32!");

    while (1) {
        // Your main code here
    }
}

void LCD_Command(uint8_t command) {
    HAL_GPIO_WritePin(DATA_PORT, RS_PIN, GPIO_PIN_RESET); // RS = 0 for command
    HAL_GPIO_WritePin(DATA_PORT, E_PIN, GPIO_PIN_SET);     // Enable high
    HAL_GPIO_WritePort(DATA_PORT, command);               // Send command
    HAL_GPIO_WritePin(DATA_PORT, E_PIN, GPIO_PIN_RESET);   // Enable low
    HAL_Delay(2); // Adjust the delay based on your LCD datasheet
}

void LCD_Data(uint8_t data) {
    HAL_GPIO_WritePin(DATA_PORT, RS_PIN, GPIO_PIN_SET);   // RS = 1 for data
    HAL_GPIO_WritePin(DATA_PORT, E_PIN, GPIO_PIN_SET);    // Enable high
    HAL_GPIO_WritePort(DATA_PORT, data);                 // Send data
    HAL_GPIO_WritePin(DATA_PORT, E_PIN, GPIO_PIN_RESET);  // Enable low
    HAL_Delay(2); // Adjust the delay based on your LCD datasheet
}

void LCD_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configure data pins (D0-D7) as output
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
                          GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DATA_PORT, &GPIO_InitStruct);

    // Configure RS and E pins as output
    GPIO_InitStruct.Pin = RS_PIN | E_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DATA_PORT, &GPIO_InitStruct);

    // Initialize LCD in 8-bit mode
    HAL_Delay(50); // Wait for the LCD to power up
    LCD_Command(0x38); // 8-bit, 2 lines, 5x8 font
    LCD_Command(0x0E); // Display ON, cursor ON
    LCD_Command(0x01); // Clear display
    HAL_Delay(2); // Delay after clear display
}

void LCD_Clear(void) {
    LCD_Command(0x01); // Clear display
    HAL_Delay(2);       // Delay after clear display
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t position = row * 0x40 + col; // Calculate position for 2x16 LCD
    LCD_Command(0x80 | position);        // Set cursor position
}

void LCD_WriteString(const char* str) {
    while (*str != '\0') {
        LCD_Data(*str);
        str++;
    }
}
