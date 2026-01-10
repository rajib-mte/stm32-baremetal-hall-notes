#include "stm32f4xx.h"
#include "/Library/ST32F4_DELAY.h"
#include "/Library/USART2.h"
/********USAR2****************
			Tx = A2
			Rx = A3
baudrate = 115200
*****************************/

#define GPIOAEN				(1U<<0)
#define ADC1EN				(1U<<8)
#define ADC_CH1				(1U<<0)
#define ADC_SEQ_LEN_1	(0x00)
#define CR2_ADON			(1U<<0)
#define CR2_SWSTART		(1U<<30)
#define SR_EOC				(1U<<1)

void PA1_ADC_Init(void);
void start_conversion(void);
uint32_t adc_read(void);

uint32_t analogValue;

int main(void){
	
	USART2_Init();
	PA1_ADC_Init();
	
	printf("Welcom to DC Volt meter\r\n");
	printf("Develop by Rajib Hasan\r\n");
	printf("B.Sc in Mechatronics engineering at World University\r\n");
	delay(2000);
	
	while(1){
		start_conversion();
		
		analogValue = adc_read();
		//float volt = analogValue*(3.3/4096.0);
		
		printf("value : %.2fV\r\n", analogValue);
		delay(100);
		
	}
	
}


void PA1_ADC_Init(void){
	/***Configure the ADC GPIO pin***/
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;
	
	/*Set the mode of PA1 to analog mode*/
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);
	
	/***Configure the ADC module***/
	/*Enable clock access to ADC*/
	RCC->APB2ENR |= ADC1EN;
	
	/*Conversion sequence start*/
	ADC1->SQR3	= ADC_CH1;
	
	/*Conversion sequence lenth*/
	ADC1->SQR1	= ADC_SEQ_LEN_1;
	
	/*Enable Adc module*/
	ADC1->CR2 |= CR2_ADON;
}


void start_conversion(void){
	/*Start conversion*/
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void){
	/*wati for converison to be complete*/
	while(!(ADC1->SR & SR_EOC));
	
	/*REad converted result*/
	return (ADC1->DR);

}