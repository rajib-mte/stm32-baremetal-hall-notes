#include "stm32f4xx.h"
#include "/Library/USART2.h"
#include "/Library/ST32F4_DELAY.h"









int main(void){
	
	
	
	while(1){
		
		
		
	}
}


void i2c_Init(void){
	
	RCC->AHB1ENR |= (1U<<1);
	RCC->APB1ENR |= (1U<<21);
	
	/*PB8 and PB9 use alternate function*/
	GPIOB->MODER &=~(1U<<16);
	GPIOB->MODER |= (1U<<17);
	GPIOB->MODER &=~(1U<<18);
	GPIOB->MODER |= (1U<<19);
	
	/*Set alternate function as i2c*/
	GPIOB->AFR[1] |= (1U<<2);
	GPIOB->AFR[1] |= (1U<<6);
	
	/*Set as open-drain*/
	GPIOB->OTYPER |= (1U<<8);
	GPIOB->OTYPER |= (1U<<9);
	
	/*I2C Config*/
	I2C1->CR1			|= (1U<<15);
	I2C1->CR1			&=~(1U<<15);
	
	
	
}