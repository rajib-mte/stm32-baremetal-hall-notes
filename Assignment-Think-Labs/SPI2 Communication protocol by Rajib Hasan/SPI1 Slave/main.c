/************ATENTION*************

SPI1->>>>>>>>>>PA5, PA6 and PA7 for SCK, MISO, and MOSI Respectively

***********************************/

#include "stm32f4xx.h"
#include "/Library/ST32F4_DELAY.h"
#include "/Library/USART2.h"


void SPI1_Init(void);
uint8_t SPI1_TransmitReceive(uint8_t data);
int main(void){
	
	SPI1_Init();
	USART2_Init();
	while(1){
		/*Transmit and receive data*/
		uint8_t sendData = 200;
		uint8_t receiveData = SPI1_TransmitReceive(sendData);
		printf("Receive Data from Master: %d \r\n", (int)receiveData);
		SysTickDelayMs(100);
	}
	
}

void SPI1_Init(void){
	
	/*Configure GPIO for SPI1(PA5, PA6 and PA7 for SCK, MISO, and MOSI Respectively)*/
	RCC->AHB1ENR  |=(1U<<0); //Enable GPIOA clock:
	GPIOA->MODER  |= (2U<<10) |(2U<<12) |(2U<<14); //Alternate function mode for port PA5, PA6, PA7:
	GPIOA->AFR[0] |= (5U<<20) |(5U<<24)	|(5U<<28); //PA5, PA6, PA7 Alternate function selection for SPI1:
	
	/*Configure SPI1*/
	RCC->APB2ENR |= (1U<<12); //Enable SPI1 clock:
	SPI1->CR1 = 0; //Clear CR1 register:
	SPI1->CR1 |= (1U<<0); //CPHA=1:
	SPI1->CR1	|= (1U<<1); //CPOL=1:
	SPI1->CR1 &=~(1U<<2); //Set as a slave:
	SPI1->CR1	|= (3U<<3); //SET bau rate for 5MHz(84/16):
	SPI1->CR1	|= (3U<<8); //ENABLE software slave management and set internal slve select:
	
	SPI1->CR1	|= (1U<<6); // Enable SPI1
}

uint8_t SPI1_TransmitReceive(uint8_t data){
	/*Wait until transmit buffer is empty*/
	while(!(SPI1->SR & (1U<<1)));

	/*Write data to transmit buffar*/
	SPI1->DR = data;
	
	/*Wait until receive buffer is not empty*/
	while(!(SPI1->SR & (1U<<0)));
	
	return SPI1->DR;
}