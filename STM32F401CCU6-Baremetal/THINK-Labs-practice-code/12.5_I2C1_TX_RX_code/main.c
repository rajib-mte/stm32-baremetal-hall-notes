#include "stm32f4xx.h"



#define slave address 0x68
#define reg_addree 0x02
uint8_t i2c_data_buff2[10];

/*********************
	SCL = PB6
	SDA + PB7
*********************/




int main(void){
	
	while(1){
		
		
		
	}
}



void i2c_init(void){
	/**********GPIOB Config*********/
	/*Enable clock access GPIOB*/
	RCC->AHB1ENR |= 0x02;
	
	/*Set PB6 and PB7 mode to alternate function mode*/
	GPIOB->MODER |= (2U<<12) |(2U<<14);
	
	GPIOB->AFR[0] |= (4U<<24) |(4U<<28);
	
	/*Set output type of PB6 and PB7 to open-drain mode*/
	GPIOB->OTYPER |= (1U<<6) |(1U<<7);
	
	/********I2C1 Config***********/
	/*Clock access enable for I2C1*/
	RCC->APB1ENR |= (1U<<21);
	
	/*Reset I2C1 module*/
	I2C1->CR1 = (1U<<15);
	
	/*release Reset*/
	I2C1->CR1 &=~(1U<<15);
	
	/*Enable clock stretching*/
	I2C1->CR1 &=~(1U<<7);
	
	/*Disable general call*/
	I2C1->CR1 &=~(1U<<6);
	
	/*Set souce clock speed*/
	I2C1->CR2 |= 16;
	
	/*set i2c clock speed*/
	I2C1->CR2 |= 16;
	
	/*Set i2c to standard mode, 100kHz clock*/
	I2C1->CCR = 400;
	
	/*output max rise***/
	I2C1->TRISE = 17;
	
	
	
	
}