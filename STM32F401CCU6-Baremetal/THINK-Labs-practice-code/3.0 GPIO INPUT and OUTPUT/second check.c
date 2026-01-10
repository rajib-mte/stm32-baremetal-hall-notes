#include "stm32f4xx.h"

#define GPIOAEN		(1U<<0)
#define GPIOCEN		(1U<<2)

#define PA5		5
#define PC13	13

#define LED_PIN		(1U<<PA5)
#define	BTN_PIN		(1U<<PC13)



int main(void){
	
	/*Enable clock access to GPIOA and GPIOC*/
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;
	
	/*Set LED_PIN as an OUTPUt*/
	GPIOA->MODER |= (1U<<10) & ~(1U<<11);
	
	/*Set BTN_PIN as an INPUT*/
	GPIOC->MODER &= ~(1U<<26) & ~(1U<<27);
	
	while(1){
		if(GPIOC->IDR & BTN_PIN){
			GPIOA->BSRR = (1U<<PA5);
			for(int i=0; i<100; i++);
		}else{
			GPIOA->BSRR	= (1U<<PA5 + 16);
		}
		
	}
	
	
	
}
