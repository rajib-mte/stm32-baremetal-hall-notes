#include "stm32f4xx.h"
#include "D:\ProgramingHub\Stm32 resourceHub\Library\Delay\DELAY.h"

void usart_tx(int ch);
int main(){
	/*Clock access enable for USART1 and GPIOA*/
		RCC->APB2ENR |= 0x10;
		RCC->AHB1ENR |= 0x01;
		
		GPIOA->MODER  |= 0x80000;
		GPIOA->AFR[1] |= 0x70;
		
		USART1->BRR   |= 0x0683; //Set Baudrate
		USART1->CR1		|= 0x08;//Tx enable
		USART1->CR1		|= 0x2000; //USART1 enable
	while(1){
		
		usart_tx('R');
		delay(100);
	}
	
}


void usart_tx(int ch){
	while(!(USART1->SR & 0x80));
	USART1->DR = (ch);
}
