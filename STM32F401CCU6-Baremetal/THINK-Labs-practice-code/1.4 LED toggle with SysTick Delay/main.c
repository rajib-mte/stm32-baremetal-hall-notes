#include "stm32f4xx.h"                  // Device header



int counter = 0;

int main(void){
	
	while(1){
		counter++;
		for(int i=0; i<1000; i++);
		
	}
	
}