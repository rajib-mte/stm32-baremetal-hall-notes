#include<stm32f4xx.h>


#define BTN1		(1U<<7)
#define BTN2		(1U<<8)

void blink(int delay);

static uint8_t digit[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
static int cnt=5;
int main(void){
	
	/*GPIOA Configuration*/
	RCC->AHB1ENR  |= (1U<<0);
	GPIOA->MODER   = 0x1555;
	GPIOA->OTYPER  = 0x00;
	GPIOA->OSPEEDR = 0x00;
	GPIOA->PUPDR   = 0x00;
	
	while(1){
		
		GPIOA->ODR = digit[cnt];
	
		if(GPIOA->IDR & BTN1){
			cnt++;
			if(cnt > 9){
				cnt = 0;
				//blink(400000);
			}
			GPIOA->ODR = digit[cnt];
		}while(GPIOA->IDR & BTN1);
		
		
		if(GPIOA->IDR & BTN2){
			cnt--;
			if(cnt<=-1){
				cnt = 0;
				//blink(400000);
			}
			GPIOA->ODR = digit[cnt];
		}while(GPIOA->IDR & BTN2);
	
		
	}
}

void blink(int delay){
		GPIOA->ODR = 0x00;
		for(int i=0; i<=delay; i++);
		GPIOA->ODR = digit[cnt];
		for(int i=0; i<=delay; i++);
		GPIOA->ODR = 0x00;
		for(int i=0; i<=delay; i++);
		GPIOA->ODR = digit[cnt];
		for(int i=0; i<=delay; i++);
		GPIOA->ODR = 0x00;
		for(int i=0; i<=delay; i++);
	
}
