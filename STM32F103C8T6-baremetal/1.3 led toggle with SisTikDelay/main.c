#include "stm32f10x.h"                  // Device header
#include "/Library/STM32F1_DELAY.h"




int main(void){
	
	RCC->APB2ENR = (1<<2);
	GPIOA->CRL = 0x33333333U; //output as 50MHz
	GPIOA->CRH = 0x3U; //output as 50MHz
	

	
	
	while(1){
		int i=0;
		int d=20;
		for(int j=0; j<3; j++){
			for(i; i<7; i++){
				GPIOA->ODR |= (1U<<i);
				SisTickDelayMs(d);
				GPIOA->ODR &=~ (1U<<i);
				SisTickDelayMs(d);
			}
			for(i; i>=0; i--){
				GPIOA->ODR |= (1U<<i);
				SisTickDelayMs(d);
				GPIOA->ODR &=~ (1U<<i);
				SisTickDelayMs(d);
			}
		}
		for(i; i<7; i++){
				GPIOA->ODR |= (1U<<i);
				SisTickDelayMs(100);
				GPIOA->ODR &=~ (1U<<i);
				SisTickDelayMs(100);
			}
		for(i; i>=0; i--){
			GPIOA->ODR |= (1U<<i);
			SisTickDelayMs(100);
			GPIOA->ODR &=~ (1U<<i);
			SisTickDelayMs(100);
		}
	}
}