/*
GPIOA = APB2 = 2bit


*/

#include "stm32f10x.h"                  // Device header
#include "/Library/DELAY.h"




int main(){
	RCC->APB2ENR |= (1U<<2); //GPIOA clock access
	
	/*GPOA0 as OUTPUT mode speed 100 MHz*/
	GPIOA->CRL |=(1U<<0);
	GPIOA->CRL &=~(1U<<1);
	/*GPIOA0 as a Push pull mode*/
	GPIOA->CRL &=~ (3U<<2);
	//GPIOA->CRL &=~(1U<<3);
	
	/*GPIOA1 as a input MODE*/
	GPIOA->CRL &=~(3<<4);
	//GPIOA->CRL &=~(1U<<5);
	
	GPIOA->CRL &=~(1U<<6);
	GPIOA->CRL |= (1U<<7);
	
	
	
	while(1){
		
		if(GPIOA->IDR & (1U<<1)){
			GPIOA->ODR |= (1U<<0);
			delay(10);
		}else{
			GPIOA->ODR &=~(1U<<0);
			delay(10);
		}
	}
}