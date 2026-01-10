#include "stm32f4xx.h"                  // Device header



#define GPIOAEN			(1U<<0)
#define GPIOCEN			(1U<<2)

#define PIN5				(1U<<5)
#define PIN13				(1U<<13)

#define LED_PIN			(PIN5)
#define BTN_PIN			(PIN13)



int main(void){
		
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);
	while(1){
		GPIOA->ODR ^= LED_PIN;
		for(int i=0; i<=1000000; i++);
	}
	
	
	
	
}