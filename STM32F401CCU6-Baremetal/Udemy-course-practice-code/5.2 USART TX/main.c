/*APB1 bit 17 USART2
*USART2 connected to PA2
*
*
*/

#include "stm32f4xx.h"
#include "/Library/DELAY.h"

 


void USART2_Init(void);
void USART2_write(int ch);
int main(){
	USART2_Init();
	while(1){
		USART2_write('1');
		delay(100);
		USART2_write('\r');
		USART2_write('\n');
		
		delay(100);
	}
	
	
}

void USART2_Init(void){
	RCC->APB1ENR	|= 0x20000;
	RCC->AHB1ENR	|= 0x00001;
	GPIOA->AFR[0]	|= 0x00700;
	GPIOA->MODER	|= 0x00020; //set PA2 to alternate function
	
	USART2->BRR	= 0x0683; //9600 as 16MHz
	USART2->CR1	= 0x0008; //ENABLE Tx
	USART2->CR1	|= 0x2000;
	
}

void USART2_write(int ch){
	//wait while TX buffer is empty
	while(!(USART2->SR & 0x0080));
	USART2->DR = (ch & 0xFF);
	
}