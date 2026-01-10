#include "stm32f4xx.h"






void I2C_2_Init(void);
void I2C_2_Start(void);
void I2C_Stop(void);
void I2C_Write(uint8_t data);
void I2C_Address(uint8_t Address);
void I2C_WriteMulti(uint8_t *data, uint8_t size);
void I2C_Read(uint8_t Address, uint8_t *buffer, uint16x2_t size);


int main(void){
	
	
	
	I2C_2_Init();
	while(1){
		I2C_2_Start();
		I2C_Address(0x27);
		I2C_WriteMulti("Hello THINK", 11);
		I2C_Stop();
	}
	
}



void I2C_2_Init(void){
	/*****I2C_PIN****
		SCL = PB10
		SDA = PB15
	****************/
	
	/*Clock access for I2C_2 & GPIOB*/
	RCC->APB1ENR |= (1U<<22);
	RCC->AHB1ENR |= (1U<<1);
	
	/*Configure the I2C2 pins for Alternate functions*/
	GPIOB->MODER 		|= (2U<<20) | (2U<<30); //GPIOB10 and GPIOB15 as alternate mode
	GPIOB->OTYPER 	|= (1U<<10) | (1U<<30); //GPIoB10 and GPIOB15 as output open drain
	GPIOB->OSPEEDR 	|= (3U<<20) |	(3U<<30); //High Speed for GPIOB10 and GPIOB15 pin
	GPIOB->PUPDR		|= (1U<<20) | (1U<<30); //GPIOB10 and GPIOB15 as a pull up 
	GPIOB->AFR[1] 	|= (4<<10)	| (4U<<15); //AF4 for GPIB10 and GPIOB15
	
	/*Reset the I2C*/
	I2C2->CR1 |= (1U<<15);
	I2C2->CR1 &=~(1U<<15);
	
	/*Program the peripheral input clock in I2C_CR2 register in Order to generate corret timmings*/
	I2C2->CR2 |= (45U<<0); //PCLK1 Frequency in MHz
	
	/*Configure the clock control registers*/
	I2C2->CCR = (16<<0);
	
	/*configure the rise time register*/
	I2C2->TRISE = 17U; 
	
	/*Program the i2c cr1 register to enable the peripheral*/
	I2C2->CR1 |= (1U<<0); //Enable I2C
}



void I2C_2_Start(void){
	
	/*Enable the ACK*/
	I2C2->CR1 |= (1U<<10); //
	
	/*Generate Start*/
	I2C2->CR1 |= (1U<<8);
	
	/*Wait for SB bit to set*/
	while(!(I2C2->SR1 & (1<<0))); 
	
}

void I2C_Stop(void){
	
	/*Stop I2C2*/
	I2C2->CR1 |= (1U<<9);
	
}

void I2C_Write(uint8_t data){
	
	/*Wait for TXE bit set*/
	while(!(I2C2->SR1 & (1U<<7)));
	I2C2->DR = data;
	
	/*Wait for BTF bit set*/
	while(!(I2C2->SR1 & (1U<<2)));
}

void I2C_Address(uint8_t Address){
	
	/*Send the address*/
	I2C2->DR = Address;
	
	/*Wait for ADDR bit to set*/
	while(!(I2C2->SR1 & (1U<<1)));
	
	/*read SR1 and SR2 to clear the ADDR bit*/
	uint8_t temp = I2C2->SR1 | I2C2->SR2;
	
}

void I2C_WriteMulti(uint8_t *data, uint8_t size){
	
	/*Wait for TXE bit to Set*/
	while(!(I2C2->SR1 & (1<<7)));
	while(size){
		/*Wati for TXE bit to set*/
		while (!(I2C2->SR1 & (1<<7)));
		
		/*Send data*/
		I2C2->DR = (uint32_t)*data++;
		size--;
	}
	
	/*Wait for BTF to set*/
	while(!(I2C2->SR1 & (1<<2))); 
	
}

void I2C_Read(uint8_t Address, uint8_t *buffer, uint16x2_t size){
	
	int remaining = size;
	
	/*****Step 1******/
	if(size == 1){
		
		/***********Step 1-a ************/
		/*Send the Address*/
		I2C2->DR = Address;
		
		/*Wait for ADDR bit to set*/
		while(!(I2C2->SR1 & (1U<<1)));
		
		/************* STEP 1-b ***********/
		/*Clear the ACK bit*/
		I2C2->CR1 &=~(1U<<10);
		
		/*read SR1 and SR2 to clear the ADDR bit EV6 condition*/
		uint8_t temp = I2C2->SR1 | I2C2->SR2;
		
		/*Stop I2C*/
		I2C1->CR1 |= (1U<<9);
		
		
		/********Step 1-d********/
		/*read the data from the DATA Register*/
		buffer[size-remaining] = I2C2->DR;
		
	/*** STEP 2 ***/
	}else{
		/******STEP 2-a ***/
		/*Send the address*/
		I2C2->DR = Address;
		
		/*Wait for ADDR bit to set*/
		while(!(I2C2->SR1 & (1U<<1)));
		
		/**** STEP 2-b *****/
		/*Read SR1 and SR2 to clear the ADDR bit*/
		uint8_t temp = I2C2->SR1 | I2C2->SR2;
		
		while(remaining>2){
			/****** Step 2-C *****/
			/*wait for RxEN to set*/
			while(!(I2C2->SR1 & (1U<<6)));
			
			/****Step 2-D ******/
			/*Copy the data into the buffer*/
			buffer[size-remaining] = I2C2->DR;
			
			/****Step 2-E *****/
			/*Set the ACK bit to acknowledge teh data recived*/
			I2C2->CR1 |= (1U<<10);
			
			remaining--;
		}
		
		/*Read the SECOND LAST BYTE*/
		/*Wait for RxNE to set*/
		while(!(I2C2->SR1 & (1<<6)));
		buffer[size-remaining] = I2C2->DR;
		
		/***** Step 2-f *****/
		/*Clear the ACK bit*/
		I2C2->CR1 &=~(1U<<10);
		
		/****STep 2-g****/
		/*Stop I2C*/
		I2C2->CR1 |= (1U<<9);
		
		remaining--;
		
		/******Read the last BYTE********/
		/*Wait for RxNE to set*/
		while(!(I2C2->SR1 & (1U<<6)));
		
		/*Copy the data into the buffer*/
		buffer[size-remaining] = I2C2->DR; 
	}
	
	
}