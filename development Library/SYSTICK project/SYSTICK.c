#include "stm32f4xx.h"                  // Device header



#define SYSTICK_LOAD		(16000000)
#define CTRL_ENABLE			(1U<<0)
#define CTRL_CLKSRC			(1U<<2)
#define CTRL_COUNTFLAG		(1U<<16)


void systicDelayMs(int delay){
	/*Reload with number of clock per milli second*/
	SysTick->LOAD = SYSTICK_LOAD;
	/*Clear SisTick current value register*/
	SysTick->VAL = 0;
	/*Enable SysTick and select internal clk src*/
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;
	
	for(int i=0; i<delay; i++){
		/*wait until the COUNTERFLAG is set*/
		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0);
		
	}
	SysTick->CTRL = 0; 
	
	
	
}