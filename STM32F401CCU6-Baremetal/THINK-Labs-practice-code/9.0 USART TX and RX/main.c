#include "stm32f4xx.h"
#include "\User Library\DELAY.h"

#define USART1EN		(1U<<4)
#define GPIOAEN		(1U<<0)




#define LED 		5
static uint8_t i;
uint8_t usart_read();
void usart_tx(int data);
int main(){
	/*Configure GPIOA5 for LED state*/
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10) &~(1U<<11);
	
	/******Configre USART******/
	RCC->APB2ENR 	|= USART1EN;	//clock access enbable
	
	GPIOA->MODER	|= 0x280000;	//GPIOA9 as alternate function mode for Tx and Rx
	GPIOA->AFR[1]	|= 0x770;			//GPIOA9 alternate function mode
	USART1->BRR		|= 0x683;			//9600 baudrate slection
	USART1->CR1		|= 0x20C;			//enabel Rx and Tx and USART
	
	

	
	while(1){
		
		i = usart_read();
		if(i == '1') GPIOA->ODR |= (1U<<LED);
		if(i == '0') GPIOA->ODR &=~(1U<<LED);
		usart_tx(i);
		delay(100);
		
	}
}

void usart_tx(int data){
	while(!(USART1->SR & 0x80));
	USART1->DR = data;
	
}

uint8_t usart_read(){
	while(!(USART1->SR & 0x020)){}
	return USART1->DR;
}