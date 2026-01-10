
#include "stm32f4xx.h"
#include <stdio.h>
#include "/Library/DELAY.h"

void USART2_Init(void);
int USART2_write(int ch);
int USART2_read(void);
int fgetc(FILE *f);
int fputc(int c, FILE *f);


int main(){
	//unsigned char str[100];
	USART2_Init();
	//printf("Hello from the side\r\n");
	//printf(stdout, "test for sdtout\r\n");
	//printf(stderr, "test for stderr\r\n");
	printf("hellow world from\n");
	delay(2000);
	int n;
	char str[100];
	
	while(1){
		//int n=1;
		//for(int i=n; i<=100; i++){
		//printf("Counter: %d\r\n", i);
		//delay(100);
		printf("\r\nHow old are you? : ");
		scanf("%d", &n);
		printf("Your age is : %d\r\n" , n);
		printf("Enter your first name:");
		gets(str);
		printf("Your first name is : %s\r\n", str);
		
	}
	
	
}


void USART2_Init(void){
	RCC->AHB1ENR	|= 1;
	RCC->APB1ENR	|= 0x20000;
	
	GPIOA->AFR[0]	|= 0x07700;
	GPIOA->MODER	|= 0x000A0;	//ENABLE Tx and Rx
	
	USART2->BRR	= 0x00116; //9600 baud @16MHz
	USART2->CR1	= 0x0000C; //ENABLE Tx and Rx
	USART2->CR1 |= 0x2000;
	
}

int USART2_write(int ch){
	//wait for Tx buffer empty
	while(!(USART2->SR & 0x0080));
	USART2->DR = (ch& 0xFF);
	return ch;
}

int USART2_read(void){
	//wait for tx buffer empty
	while(!(USART2->SR & 0x0020));
	return USART2->DR;
	
}

 //struct __FILE{int handle;};
 FILE __stdin  = {0};
 FILE __stdout = {1};
 FILE __stderr = {2};


int fgetc(FILE *f){
	int c;
	c = USART2_read();
	if(c == '\r'){
		USART2_write(c);
		c = '\n';
	}
	USART2_write(c);
	return c;
}

int fputc(int c, FILE *f){
	return USART2_write(c);
	
} 