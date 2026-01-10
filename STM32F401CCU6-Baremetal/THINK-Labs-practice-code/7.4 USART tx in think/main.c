#include "stm32f4xx.h"                  // Device header
#include "delay.h"

void usart_tx(int ch);
int main(){
	RCC->AHB1ENR |= 0x01;
	RCC->APB2ENR |= 0x10; //uart1 RCC
	GPIOA->MODER |= 0x80000; //PA9 alter fucntion mode
	GPIOA->AFR[1] |= 0x70; //Alter function maping for PA9
	USART1->BRR |= 0x0683; //Baud Rate
	USART1->CR1 |= 0x200; //Usart Enable
	USART1->CR1 |= 0x8; // USART Tx enable TE
	
	while(1){

	char string[13] = "Rajib Hasan";
	for(int i=0; i<sizeof(string); i++){
		usart_tx(string[i]);
		delay(50);
	}

	usart_tx(' ');
	delay(1000);
	}
	

}



void usart_tx(int ch){
	while(!(USART1->SR & 0x0080)); //tx data empty not equal
	USART1->DR = (ch);
	
	
}



