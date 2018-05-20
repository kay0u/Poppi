#ifndef UART_DEF_HPP
#define UART_DEF_HPP

#include <stm32f411xe.h>
#include <stm32f4xx_hal.h>
#include <Useful.h>
#include "Uart.hpp"
/**
 * Initialisation of USART number
 *
 */
UART_HandleTypeDef u;
template<> UART_HandleTypeDef Uart<1>::UART = u;
template<> UART_HandleTypeDef Uart<2>::UART = u;
template<> UART_HandleTypeDef Uart<6>::UART = u;


/**
 * Interrupt service routines definitions
 *
 */

#ifdef __cplusplus
extern "C" {
#endif
void USART1_IRQHandler(void) {
	uint32_t c;

	if (USART_SR_RXNE & USART1->SR)                     // Read Data Reg Not Empty ?
	{
		c = USART1->DR & 0xFF;                           // read Data Register
		
		USART1->SR &= ~USART_FLAG_RXNE;                 // clear interrupt
		
		osMessagePut(Uart<1>::xQueueR, c, 0);
	}
	else if (USART_SR_TXE & USART1->SR)                 // Transmit Data Reg Empty ?
	{
		osEvent ev = osMessageGet(Uart<1>::xQueueT, 0);
		if (ev.status == osEventMessage)
			USART1->DR = ev.value.v;
		else
			USART1->CR1 &= ~USART_CR1_TXEIE;
	}
}

void USART2_IRQHandler(void) {
	uint32_t c;

	if (USART_SR_RXNE & USART2->SR)                     // Read Data Reg Not Empty ?
	{
		c = USART2->DR & 0xFF;                           // read Data Register
		
		USART2->SR &= ~USART_FLAG_RXNE;                 // clear interrupt

		osMessagePut(Uart<2>::xQueueR, c, 0);
	}
	else if (USART_SR_TXE & USART2->SR)                 // Transmit Data Reg Empty ?
	{
		osEvent ev = osMessageGet(Uart<2>::xQueueT, 0);
		if (ev.status == osEventMessage)
			USART2->DR = ev.value.v;
		else
			USART2->CR1 &= ~USART_CR1_TXEIE;
	}
}

void USART6_IRQHandler(void) {
	uint32_t c;

	if (USART_SR_RXNE & USART6->SR)                     // Read Data Reg Not Empty ?
	{
		c = USART6->DR & 0xFF;                            // read Data Register
		
		USART6->SR &= ~USART_FLAG_RXNE;                    // clear interrupt
		
		osMessagePut(Uart<6>::xQueueR, c, 0);
	}
	else if (USART_SR_TXE & USART6->SR)                 // Transmit Data Reg Empty ?
	{
		osEvent ev = osMessageGet(Uart<6>::xQueueT, 0);
		if (ev.status == osEventMessage)
			USART6->DR = ev.value.v;
		else
			USART6->CR1 &= ~USART_CR1_TXEIE;
	}
}
#ifdef __cplusplus
}
#endif

#endif  /* UART_DEF_HPP */
