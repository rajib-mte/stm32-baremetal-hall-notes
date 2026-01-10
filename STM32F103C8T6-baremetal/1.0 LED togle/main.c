#include "stm32f10x.h"


int main(void){
	
	RCC->APB2ENR = (1<<2);
	//configrure pin3 on PORTC
	GPIOA->CRL |=(1U<<0) | (1U<<1); //output as 50MHz
	//pin13 as output
	GPIOA->CRL &=~ (1U<<2); //General purpose output
	GPIOA->CRL &=~ (1U<<3);
	
	
	while(1){
		GPIOA->ODR |= (1U<<0);
		for(int i=0; i<1000; i++);
		GPIOA->ODR &=~ (1U<<0);
		for(int i=0; i<1000; i++);
	
	}
}

