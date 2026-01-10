#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"                  // Device header
#include "\Library\DELAY.h" 

void usart_tx(int ch);
int __io_putchar(int ch);

int __io_putchar(int ch){
	usart_tx(ch);
	return ch;
}
int main(){
	/*Clock access enable*/
	RCC->APB2ENR |= 0x10;
	RCC->AHB1ENR |=	0x01;
	/*GPIO A9 as a alternate function mode selection*/
	GPIOA->MODER |= 0x80000;
	GPIOA->AFR[1]	= 0x70;
	
	/*USART enable*/
	USART1->BRR = 0x683;
	USART1->CR1 = 0x2000; //USART enable
	USART1->CR1	= 0x08; //USART1 TX enbable
	
	while(1){
		printf("hello\n");
		delay(100);
		
	}
	
	
}

void usart_tx(int ch){
	while(!(USART1->SR & 0x80));
	USART1->DR = ch;
}