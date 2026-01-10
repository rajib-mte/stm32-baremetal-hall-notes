#include "stm32f4xx.h"
#include "/Library/DELAY.h"


void USART2_Init(void);
char USART2_read(void);
void LED_play(int value);

int main(){
	RCC->AHB1ENR |= 0x0001;
	GPIOA->MODER |= 0x0400;
	USART2_Init();
	char ch;
	while(1){
		  ch = USART2_read();
		LED_play(ch);
		
	}
	
}


void USART2_Init(void){
	
	RCC->AHB1ENR	|= 0x00001;	//ENABLE GPIOA clock for RX
	RCC->APB1ENR	|= 0x20000; //Enable USART2 clock access
	
	/*Configure PA3 as USART Rx*/
	GPIOA->AFR[0] |= 0x7000;	//ALT7 for USART2
	GPIOA->MODER	|= 0X0080;	//Enable Alternate function PA3
	
	/*Configure USART2 module*/
	USART2->BRR	 = 0x0683; //i9600 baudrate @16MHz
	USART2->CR1  = 0x0004; //Enable Rx
	USART2->CR1	|= 0x2000;	//ENABLE USART2
}


char USART2_read(void){
	while(!(USART2->SR & 0x0020));
	return USART2->DR;
}


void LED_play(int value){
	value %= 16;
	for(; value>0; value--){
			GPIOA->BSRR = 0x000020; //Turn on LED
			delay(500);
			GPIOA->BSRR = 0x200000;
			delay(500);
	}
	delay(400);
}