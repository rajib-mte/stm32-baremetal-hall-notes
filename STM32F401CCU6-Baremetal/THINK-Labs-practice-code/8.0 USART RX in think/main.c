#include "stm32f4xx.h"                  // Device header
#include "DELAY.h"






static uint8_t i;
uint8_t usart_read();
int main(){
	/*configure GPIOA5 pin as output*/
	RCC->AHB1ENR |= (1U<<0);
	GPIOA->MODER |= (1U<<10);
	
	RCC->APB2ENR |= 0x10;
	GPIOA->MODER |= 0x200000;
	GPIOA->AFR[1] |= 0x07;
	USART1->BRR |= 0x683;
	USART1->CR1 |= 0x2000;
	USART1->CR1 |= 0x04;
	
	while(1){
		i = usart_read();
		GPIOA->ODR |= (1U<<5);
		delay(100);
		
		/*
		if(i == 'H'){
			GPIOA->ODR = (1U<<5);
		}
		*/
		
	}
	
	
}


uint8_t usart_read(){
	while(!(USART1->SR & 0x020)){}
	USART1->DR;
	
}

