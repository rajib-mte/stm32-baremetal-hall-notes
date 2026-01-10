#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"

#define GPIOAEN					(1U<<0)
#define UART2EN					(1U<<17)

#define CR1_TE					(1U<<3)
#define CR1_UE					(1U<<13)
#define SR_TXE					(1U<<7)

#define SYS_FREQ				16000000
#define APB1_CLK				SYS_FREQ

#define UART_BAUDRATE			115200


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void 