#include "stm32f4xx.h"                  // Device header



#define GPIOAEN			(1U<<0)
#define GPIOBEN			(1U<<1)


#define LED1_PIN			(1<<5)
#define LED2_PIN 		(1<<6)

#define BTN1_PIN			(1<<5)
#define BTN2_PIN 			(1<<6)



int main(void){
	/*Clock access for GPIOA and GPIOB*/
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOBEN;
	
	/*GPIOA5 and GPIOA5 as an OUTPUT*/
	GPIOA->MODER |= (1U<<10)
									&~(1U<<11);
	
	GPIOA->MODER |= (1U<<12)
									&~(1U<<13);
	
	//GPIOB5 and GPIO6 as an INPUT
	GPIOB->MODER &= ~(1U<<10);
	GPIOB->MODER &= ~(1U<<11);
	
	GPIOB->MODER &= ~(1U<<12);
	GPIOB->MODER &= ~(1U<<13);
	
	
	while(1){
		
		if(GPIOB->IDR & BTN1_PIN) GPIOA->BSRR |= (1U<<5);
		else GPIOA->BSRR |= (1U<<(5+16));
		
		if(GPIOB->IDR & BTN2_PIN) GPIOA->BSRR |= (1U<<6);
		else GPIOA->BSRR |= (1U<<(6+16));
	}
	
}