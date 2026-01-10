#include "stm32f4xx.h"
#include "/Library/USART2.h"
#include "/Library/ST32F4_DELAY.h"









int main(void){
	
	
	
	
	
	while(1){
		
		
		SysTickDelayMs(100);
		
		
	}
	
	
	
}




void I2C_Init(void){
	
	/*GIPA clock access anable*/
	RCC->AHB1ENR |= 0x02;
	/*Set PB6 and PB7 mode to alternate function mode*/
	GPIOB->MODER |= (2U<<12); /*SET mode for PB6*/
	GPIOB->MODER |= (2U<<14); /*SET mode for PB7*/
	
	GPIOB->AFR[0] |= (4<<24); /*PB6*/
	GPIOB->AFR[0] |= (4<<28); /*BB7*/
	/*SCL and SDA respectively*/
	/*Set outpu type of PB6 and PB7 to open-drain*/
	GPIOB->OTYPER |= (1U<<6);
	GPIOB->OTYPER |= (1U<<7);
	
	/*I2C Configuration*/
	RCC->APB1ENR |= 0x200000; //Enable I2C clock
	/*Reset I2C module*/
	I2C1->CR1 = 0x8000; //software reset
	/*Release the reset*/
	I2C1->CR1 &=~0x8000;
	/*Enable clock stretching*/
	I2C1->CR1 &=~ 0x80;
	/*Disable General Call*/
	I2C1->CR1 &=~0x40;
	/*Set source clock speed*/
	I2C1->CR2 |= 16;
	/*Set I2C to standard mode, 100kHz clock*/
	I2C1->CCR = 400; //STnadard mode: 100khz clock
	/*output max rise*/
	I2C1->TRISE = 17;
	/*Enable I2C module*/
	I2C1->CR1 = 0x0001;
	
}


void I2C_write_single(uint8_t device_address, uint8_mem_address, uint16_t data){
	
	uint32_t temp;
	/*wait while BUSY flage is set*/
	while(I2C1->SR1 & (0x02));
	
	I2C1->CR1 |= I2C_CR1_START; //genearatie start condition
	while(!(I2C1->SR1 & I2C_SR1_SB)); //start condition generate
	
	/*read SR1*/
	I2C1->SR1;
	I2C1->DR = (device_address<<1 | 0); //write slave address
	while(!(I2C1->SR1 & I2C_SR1_ADDR)); //send address
	temp = I2C1->SR2;
	}	
}