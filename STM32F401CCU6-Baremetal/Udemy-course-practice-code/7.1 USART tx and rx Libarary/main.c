#include "stm32f4xx.h"
#include "/Library/DELAY.h"
#include "/Library/USART2.h"




int main(){
	USART2_Init();
	while(1){
		int i=0;
		for(i; i<=100; i++){
			printf("Counter: %d\r\n", i);
			delay(10);
		}
		
	}
	
}