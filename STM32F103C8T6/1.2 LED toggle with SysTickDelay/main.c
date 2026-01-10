#include "stm32f10x.h"                  // Device header
#include "D:\STM32\STM32 Blue Pill-STM32F103C8T6\Code\1.2 LED toggle with SysTickDelay\sysTick
int main(void){
	
	RCC->APB2ENR = (1<<2);
	//configrure pin3 on PORTC
	GPIOA->CRL |=(1U<<0) | (1U<<1); //output as 50MHz
	//pin13 as output
	GPIOA->CRL &=~ (1U<<2); //General purpose output
	GPIOA->CRL &=~ (1U<<3);
	
	
	while(1){
		GPIOA->ODR |= (1U<<0);
		SysTickDelayMs(1000);
		GPIOA->ODR &=~ (1U<<0);
		SysTickDelayMs(1000);
	
	}
}
