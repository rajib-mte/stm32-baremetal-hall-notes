#include "stm32f4xx.h"
#include "delay.h"
#include "dhcp.h"


volatile unsigned int Ticks, DelayCount;

volatile uint32_t dhcpMillisTrack = 0;
void SysTick_Handler(void)
{ /* SysTick interrupt Handler. */
	if(Ticks==0xffffffff){ // for handling 32 bit max overflow
		Ticks = 0;
		return;
	}
	Ticks++;
	dhcpMillisTrack++;
	if(dhcpMillisTrack==1000){
		DHCP_time_handler();
		dhcpMillisTrack = 0;
	}
}

unsigned int millis(void)
{
	return Ticks;
}

void sysTickInit(void)
{
	uint32_t returnCode;
	returnCode = SysTick_Config(SystemCoreClock / AUTO_RELOAD_VALUE);
	/* Configure SysTick to generate an interrupt every millisecond */

	if (returnCode != 0)
	{	/* Check return code for errors */
		// Error Handling
	}
}

void delayms(uint32_t delay)
{
	DelayCount = millis();
	while (1)
	{
		if (millis()-DelayCount == delay)
			break;
	}
}