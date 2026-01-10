#include "stm32f4xx.h"




void i2c_Init(void);
void i2c_write_single(uint8_t device_address, uint16_t data);
int main(void){
	
	
	while(1){
		
		
		
	}
	
	
	
	
}







void i2c_Init(void){
	
	/*I2C-2: SCL=PB10>>>>SDA=PB11*/
	
	/*GPIO pin configuration*/
	/*GPIOB clock access enable*/
	RCC->AHB1ENR |= (1U<<2);
	
	/*Set PB10 and PB11 mode to alternate function mode*/
	GPIOB->MODER |= (2U<<20) |(2U<<22);
	
	/*set output type of PB10 and PB11 to open-drain*/
	GPIOB->OTYPER |= (1U<<10);
	GPIOB->OTYPER |= (1U<<11);
	
	/***********I2C2 configuration***************/
	/*I2C as a alternate function mode*/
	GPIOB->AFR[0] |= (8U<<10) |(8U<<11); //SCL and SDA respectively
	
	/*I2C2 clock access enable*/
	RCC->APB1ENR |= (1U<<22);
	/*Reset I2C module*/
	I2C2->CR1 = 0x8000; //software reset
	/*Release the reset*/
	I2C2->CR1 &=~0x8000;
	/*Enable clock stretching*/
	I2C2->CR1 &=~ 0x80;
	/*Disable General Call*/
	I2C2->CR1 &=~0x40;
	/*Set source clock speed*/
	I2C2->CR2 |= 16;
	/*Set I2C to standard mode, 100kHz clock*/
	I2C2->CCR = 400; //STnadard mode: 100khz clock
	/*output max rise*/
	I2C2->TRISE = 17;
	/*Enable I2C module*/
	I2C2->CR1 = 0x0001;
}


void i2c_write_single(uint8_t device_address, uint8_t uint16_t data){
	
	uint32_t temp;
	/*wait while BUSY flage is set*/
	while(I2C2->SR1 & (0x02));
	
	I2C2->CR1 |= I2C_CR1_START; //genearatie start condition
	while(!(I2C1->SR1 & I2C_SR1_SB)); //start condition generate
	
	/*read SR1*/
	I2C2->SR1;
	I2C2->DR = (device_address<<1 | 0); //write slave address
	while(!(I2C2->SR1 & I2C_SR1_ADDR)); //send address
	temp = I2C2->SR2;
	
	/*address to write to*/
	I2C2->DR = mem_address;
	
	/*TX enable*/
	while(!(I2C2->SR1 & 1U<<7);
	
	/*I2C2 stop generation*/
	I2C2->CR1 |= (1U<<9);
	
	/*
	}	
}