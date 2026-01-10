/************ATENTION*************
Clock speed = 1MHz
Data size = 8bit
clock polorarity = LOW (0);
clock phase = 1;
SPI2->>>>>>>>>>PB13, PB14, PB15 for SCK, MISO, MOSI Respectivly

***********************************/

#include "stm32f4xx.h"
#include "/Library/ST32F4_DELAY.h"
#include "/Library/USART2.h"
#include <string.h>


void SPI2_Init(void);
uint8_t SPI2_TransmitReceive(uint8_t data);
void SPI2_receive(uint8_t *data, int size);

int main(void){
	
	SPI2_Init();
	USART2_Init();
	
	while(1){
		uint8_t sendData = 100;
		SysTickDelayMs(100);
		
	}
	
}

void SPI2_Init(void){
	
	/* Configure GPIO for SPI2 : PB13, PB14, PB15 for SCK, MISO, MOSI Respectivly*/
	RCC->AHB1ENR =  (1U<<1); //Enable GPIOB clock:
	GPIOB->MODER	  |= (2U<<26) |(2U<<28) |(2U<<30); //PB13, PA14, PB15 as a alternate fucntion mode:
	//GPIOB->OSPEEDR	|= (2U<<26) |(2U<<28) |(2U<<30); //PB13, PA14, PB15 port output HIGH speed:
	GPIOB->AFR[1] 	|= (5U<<20) |(5U<<24)	|(5U<<28); //
	
	
	/****Configure SPI2 module******/
	RCC->APB1ENR |= (1U<<14); //Enable SPI2 clock
	
	SPI2->CR1 = 0;
	SPI2->CR1 |=  (1U<<0); //CPHA=1:
	SPI2->CR1 &= (1U<<1); //CPOL=0:
	SPI2->CR1 |= (1U<<2); //Set as a master mode:
	SPI2->CR1	|= (2U<<3); //SET baudrate for 1MHz(8/8):
	SPI2->CR1	|= (3U<<8); //ENABLE software slave management and set internal slv select:
	
	SPI2->CR1	|= (1U<<6); //ENABLE SPI2:
	
	SPI2->CR2 = 0;
}

uint8_t SPI2_TransmitReceive(uint8_t data){
	
	/*Wait until transmit buffer is empty*/
	while(!(SPI2->SR & (1U<<1)));
	
	/*Write data to transmit bufer*/
	SPI2->DR = data;
	
	/*Wait until receive buffer is not emty*/
	while(!(SPI2->SR & (1U<<0)));
	
	/*Read data from receive buffer*/
	return SPI2->DR;
}

void SPI2_receive(uint8_t *data, int size){
	
	while(size){
		/*wait for BSY bit reset*/
		while(((SPI2->SR) & (1<<7)));
		/*Send dummy data*/
		SPI2->DR = 0;
		/*wait for buffer is not empty*/
		while(!(((SPI2->SR) & (1<<0))));
		*data++ = (SPI2->DR);
		size--;
		
	}
	
}