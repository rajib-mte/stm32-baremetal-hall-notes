#include "stm32f4xx.h"
#include "/Library/USART2.h"
#include "/Library/ST32F4_DELAY.h"









void pa1_adc_Init(void);
void start_conversion(void);
uint32_t adc_read(void);
uint32_t value;

int main(void){
	
	
	pa1_adc_Init();
	
	while(1){
		
		start_conversion();
		
		value = adc_read();
		SysTickDelayMs(100);
	}
	
	
}



void pa1_adc_Init(void){
	
	/******configure the ADC GPIO pin********/
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= (1U<<0);
	
	/* Set the mode of A1 to analog mode*/
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);
	
	/*****Configure the ADC module****/
	/*Enable clock access to ADC*/
	RCC->APB2ENR |= (1U<<8);
	
	/*Conversion sequence start*/
	ADC1->SQR3 = (1U<<0);
	
	/*Conversion sequence lenth*/
	ADC1->SQR1 |= 0x00;
	
	/*Enable ADC module*/
	ADC1->CR2 |= (1U<<0);
	
}


void start_conversion(void){
	/*ADC start conversion*/
	ADC1->CR2 |= (1<<30);
}

uint32_t adc_read(void){
	
	/*wait for conversion to be complete*/
	while(!(ADC1->SR & (1U<<1)));
	
	/*read converted result*/
	return (ADC1->DR);
}