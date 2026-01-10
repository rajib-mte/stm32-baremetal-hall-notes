#include "stm32f4xx.h"
#include "/Library/DELAY.h"
#include "/Library/USART2.h"

//Configure ADC CH1
int analogValue = 9;


int main(void){
	USART2_Init();
	
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0xC; //set PA! to analog mode
	
	RCC->APB2ENR |= 0x100; //Enable clok acess to ADC
	ADC1->CR2 = 0;
	ADC1->SQR3 = 1;
	ADC1->CR2 |= 1; //Enable ADC
	
	while(1){
		ADC1->CR2 |= 0x40000000;
		//wait for conversion to be complete
		while(!(ADC1->SR & 2));
		analogValue = ADC1->DR;
		printf("Analog Value: %d\r\n", analogValue);
		//delay(100);
		
	}
	
	
}