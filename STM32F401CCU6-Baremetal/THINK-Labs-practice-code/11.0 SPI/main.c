/*
SPI1_SCK = PA5
SPI1_MISO = PA6
SPI1_MOSI = PA7

SPI1 = APB2
GPIOA = AHB1

*/

#include "stm32f4xx.h"
#include "/Library/DELAY.h"
#include "/Library/USART2.h"






void spi1_gpio_config(void);

int main(){
	
	while(1){
		
		
		
		
	}
	
	
}


void spi1_gpio_config(void){
		/*Clock access for GPIOA*/
		RCC->AHB1ENR |= (1U<<0);
		
		/*GPIOA Alternat function mode selection*/
		GPIOA->MODER |= (2<<10) | (2<<12) | (2<<14);
	
		/*GPIOA port SPEED configuration*/
		GPIOA->OSPEEDR |= (2<<10) | (2<<12) | (2<<14);
	
		/*GPIOA alternate function mode*/
		GPIOA->AFR[0] |= (5<<20) | (5<<24) | (5<<28);
	
		/*GPIOA4 as an output for SS*/
		GPIOA->MODER |= (1U<<8);
		GPIOA->MODER &=~(1U<<9);
		
}

void spi1_config(void){
	/*SPI1 clck access*/
	RCC->APB2ENR |= (1U<<12);
	
	/*SPI1 CPOL CPHA enable*/
	SPI1->CR1 |= (1U<<0) | (1U<<1);
	
	/*SPI1 as a master mode*/
	SPI1->CR1 |= (1U<<2);
	
	/*SPI1 buad rate set as 5MHz*/
	SPI1->CR1 |= (3<<3);
	
	/*MSB set*/
	SPI1->CR1 &=~(1U<<7);
	
	/*Internal */
	SPI1->CR1 |= (1U<<8) | (1U<<9);
	
	/*Full douplex mode enable*/
	SPI1->CR1 &=~(1U<<10);
	/*data formate as 8bit*/
	SPI1->CR1 &=~(1U<<11);
	
	/*CR2 reset all*/
	SPI1->CR2 = 0;
}


void spi1_enable(void){
	/*SPI1 enable*/
	SPI1->CR1 |= (1U<<16);
}

void spi1_disable(void){
	/*SPI1 Disable*/
	SPI1->CR1 &=~(1U<<16);
	
}

void cs_enable(){
	/**/
	GPIOA->ODR |= (1U<<4);
	
}

void cs_disable(void){
	/**/
		`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`	`
}
	
	
	
