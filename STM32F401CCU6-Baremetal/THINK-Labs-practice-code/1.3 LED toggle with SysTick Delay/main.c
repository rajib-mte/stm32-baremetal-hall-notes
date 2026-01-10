#include "stm32f4xx.h"


int main(void){
	
	/*GPIPA5 congiguration*/
	RCC->AHB1ENR |= (1U<<0);
	
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);
	
	/*GPIPC congiguration*/
	RCC->AHB1ENR |= (1U<<2);
	GPIOA->MODER |= (1U<<26);
	GPIOA->MODER &=~(1U<<27);
	
	
	
	while(1){
		GPIOA->ODR ^= (1U<<5);
		GPIOA->ODR ^= (1U<<13);
				
	}
	
}

