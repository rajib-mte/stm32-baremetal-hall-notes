#include "stm32f4xx.h"
#include "/Library/DELAY.h"
#include "/Library/USART2.h"





void SPI2_Init(void);
uint8_t SPI2_TransmitReceive(uint8_t data);

int main(void){
	
	SPI2_Init();
	USART2_Init();
	
	while(1){
		uint8_t sendData = 100;
		uint8_t receiveData = SPI2_TransmitReceive(sendData);
		printf("Receive data from slave: %d\r\n", (int)receiveData);
		//printf("Receive data from slave:\r\n");
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
	SPI2->CR1 |= (1U<<1); //CPOL=1:
	SPI2->CR1 |= (1U<<2); //Set as a master mode:
	SPI2->CR1	|= (3U<<3); //SET baudrate for 5MHz(84/16):
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