#include "stm32f4xx.h"                  // Device header



void delayMs(int d);
void SPI3_Init(void);
void SPI_Transmit(uint8_t *data, int size);
void SPI_transmit_char(uint8_t data);
void SPI_transmit_string(uint8_t *data, int size);
void SPI_Receive(uint8_t *data, int size);

uint8_t Data[10] = "Shafine";

int main()
{

   
    SPI_transmit_string(Data, 4);

    while (1)
    {
        SPI_transmit_char(0x20);
				delayMs(100);
			

    }
}






void SPI3_Init(void){
	/*GPIO Configuration*/
	RCC->AHB1ENR |= 0x01; // GPIO RCC CLK ENABLE
	GPIOA->MODER |= (0 << 20) | (1 << 21) | (0 << 22) | (1 << 23) | (0 << 24) | (1 << 25); //*/
	GPIOA->OSPEEDR |= (1 << 20) | (1 << 11) | (1 << 22) | (1 << 23) | (1 << 24) | (1 << 25); // GPIO Register very high speed
	GPIOA->AFR[0] |= (6 << 8) | (6 << 12) | (6 << 16);                                       // 0 means low register, from alternate function mapping for PC10, PC11, PC12
	
	
	/*SPI3 Configuration*/
	RCC->APB1ENR |= (1 << 15);  // Enable SPI3 clock
	SPI3->CR1 |= (1 << 0) | (1 << 1); // POLE and phase enable
	SPI3->CR1 |= (1 << 2); // master mode
	SPI3->CR1 |= (3 << 3); // BR[2:0]=011;
	SPI3->CR1 &= ~(1 << 7);  // MSB first =0; LSB first
	SPI3->CR1 |= (1 << 8) | (1 << 9); // Slave management
	SPI3->CR1 &= ~(1 << 10); // Full duplex bit 10-0
	SPI3->CR1 &= ~(1 << 11); // 8-bit data, DFF=0
	SPI3->CR2 = 0;
	
	/*SPI Enable*/
	SPI3->CR1 |= (1 << 6); // SPE=1, Peripheral enabled
	
	/*Chip select enable*/
	GPIOA->ODR &= ~(1 << 15); // PA15
	
	GPIOA->MODER |= (0 << 30) | (1 << 31); // PA15 pin in OUTPUT mode
	
}



void SPI_Transmit(uint8_t *data, int size)
{
    int i = 0;
    while (i < size)
    {
        while (!(SPI3->SR & (1 << 1))); // Wait for the TXE bit to set
        SPI3->DR = data[i];              // Load the data into the data register
        i++;
    }
    while (!(SPI3->SR & (1 << 1))); // Wait for the TXE bit to set
    while (SPI3->SR & (1 << 7));    // Wait for the BSY bit to reset
    uint8_t temp = SPI3->DR;
    temp = SPI3->SR;
}

void SPI_transmit_char(uint8_t data)
{
    while (!(SPI3->SR & (1 << 1))); // Wait for the TXE bit to set
    SPI3->DR = data;                 // Load the data into the data register
    while (!(SPI3->SR & (1 << 1))); // Wait for the TXE bit to set
    while (SPI3->SR & (1 << 7));    // Wait for the BSY bit to reset
    uint8_t temp = SPI3->DR;
    temp = SPI3->SR;
}

void SPI_transmit_string(uint8_t *data, int size)
{
    int i = 0;
    while (i < size)
    {
        while (!(SPI3->SR & (1 << 1))); // Wait for the TXE bit to set
        SPI3->DR = data[i];              // Load the data into the data register
        i++;
    }
    while (!(SPI3->SR & (1 << 1))); // Wait for the TXE bit to set
    while (SPI3->SR & (1 << 7));    // Wait for the BSY bit to reset
    uint8_t temp = SPI3->DR;
    temp = SPI3->SR;
}

void SPI_Receive(uint8_t *data, int size)
{
    while (size)
    {
        while (!(SPI3->SR & (1 << 7))); // Wait for the BSY bit to reset
        SPI3->DR = 0;                    // Send dummy data
        while (!(SPI3->SR & (1 << 0))); // Wait for RXNE to set
        *data++ = SPI3->DR;
        size--;
    }
}

void delayMs(int d){
	for(int i=0; i<d; i++){
		for(int j=100; j>0; j--);
	}
}