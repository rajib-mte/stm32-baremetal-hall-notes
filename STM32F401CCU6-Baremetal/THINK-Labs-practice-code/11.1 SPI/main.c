/***************************************************
  _____                    _   _____   ____       _    _               _____              _   _
 |  __ \      /\          | | |_   _| |  _ \     | |  | |     /\      / ____|     /\     | \ | |
 | |__) |    /  \         | |   | |   | |_) |    | |__| |    /  \    | (___      /  \    |  \| |
 |  _  /    / /\ \    _   | |   | |   |  _ <     |  __  |   / /\ \    \___ \    / /\ \   | . ` |
 | | \ \   / ____ \  | |__| |  _| |_  | |_) |    | |  | |  / ____ \   ____) |  / ____ \  | |\  |
 |_|  \_\ /_/    \_\  \____/  |_____| |____/     |_|  |_| /_/    \_\ |_____/  /_/    \_\ |_| \_|

1. Enable SPI clock
2. Configure the Control Reginster 1 (CR1)
3. Configure the CR2

I am using the following Pins for the SPI 1:
	PA5 = CLK
	PA6 = MISO
	PA7 = MOSI
	PA4 = Slave Select
	
********************************/


#include "stm32f4xx.h"                  // Device header








int main(){
	
	
	
	while(1){
		
		
	}
	
	
}

void SPI1_Enable(void){
	/*SPI Peripharal Enable*/
	SPI1->CR1 |= (1U<<6);
}

void SPI1_Disable(void){
	/*SPI Periapheral disable*/
	SPI1->CR1 &=~(1U<<6);
}

void CS_Enable(void){
	/*GPIOA4 LOW*/
	GPIOA->ODR &=~(1U<<4);
}

void CS_Disable(void){
	/*GPIOA4 HIGH*/
	GPIOA->ODR |= (1U<<4);
}


void gpio_config(void){
	/*Access GPIO clock*/
	RCC->AHB1ENR |= (1U<<0);
	
	/*Alternate functions mode select for PA4, PA5, PA6, PA7:*/
	GPIOA->MODER |= (2<<10) |(2<<12) |(2<<14);
	
	/*GPIOA4 as an output mode for chip select*/
	GPIOA->MODER |= (1U<<8);
	GPIOA->MODER &=~(1U<<9);
	
	/*HIGH speed select for PA4, PA5, PA6, PA7*/
	GPIOA->OSPEEDR |= (3<<8) |(3<<10) |(3<<12) |(3<<14);
	
	/*The GPIOA(PA5, PA6, PA7) as a alternate function mode for SPI_1*/
	GPIOA->AFR[0] |= (5<<16);
	GPIOA->AFR[0] |= (5<<20);
	GPIOA->AFR[0] |= (5<<24);
	GPIOA->AFR[0] |= (5<<28);
}

void spi_config(void){
	
	/*Enable SPI1 clock*/
	RCC->AHB2ENR |= (1U<<12);
	
	/*Clock polarity(CPOL=1) and clock phase(CPHA=1)*/
	SPI1->CR1 |= (1U<<0) |(1U<<1);
	
	/*Enable Master Mode*/
	SPI1->CR1 |= (1U<<2);
	
	/*BR = 011: fpclk/16, pclk2 = 80MHz, SPI clk = 5MHz*/
	SPI1->CR1 |= (3<<3);
	
	/*Enable MSB*/
	SPI1->CR1 &=~(1U<<7);
	
	/*SSM=1, SSi=1 : Software slave menagement*/
	SPI1->CR1 |= (1U<<8) |(1U<<9);
	
	/*Full-Duplex mode enable*/
	SPI1->CR1 &=~(1U<<10);
	
	/* 8bit Data formate*/
	SPI1->CR1 &=~(1U<<11);
	
	/*Control registor reset*/
	SPI1->CR2 = 0x00;
}








/*******SPI Recive data*******/
void spi_receive(uint8_t *data, int size){
	/*******Steps to follow*********
	1. wait for the bsy bit reset in status register
	2. Send some dummy data before reading the DATA
	3. Wait for RXNE bit to set in the status register
	4. Read data from Data Register
	*******************************/
	
	while(size){
		/*Wait for BSY bit reset*/
		while(((SPI1->SR) & (1<<7)));
		
		/*Send dummy data*/
		SPI1->DR = 0;
		
		/*Wait for buffer is not empty*/
		while(!((SPI1->SR) & (1<<0)));
		*data++ = (SPI1->DR);
		size--;
	}
	
}









