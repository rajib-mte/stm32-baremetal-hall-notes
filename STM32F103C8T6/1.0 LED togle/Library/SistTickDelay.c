#include "SistTickDelay.h"




void SysTickDelayMs(int n){
	/*Reload with number of clocks per millisecond*/
	SysTick->LOAD = 16000;
	
	/*Clear current value register*/
	SysTick->VAL = 0;
	
	/*Enable Systick*/
	SysTick->CTRL = 0x5;
	
	for(int i=0; i<n; i++){
		/*Wait until the COUNT flag is set*/
		while((SysTick->CTRL & 0x10000) == 0);
	}
	SysTick->CTRL = 0;
}