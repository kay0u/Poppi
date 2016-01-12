/**
 * Uart.hpp
 * Handle UARTs (transmission/reception) for STM32F411XE
 *
 *********************************************************
 * Trois séries différentes: USART1, USART 2 et USART6
 * Pins :
 *
 * UART1: A15 (TX) A10 (RX)
 * UART2: A2 (TX) A3 (RX)
 * UART6: C6 (TX) C7 (RX)
 *
 *
 * Jaune: TX
 * Orange: RX
 */

#ifndef UART_HPP
#define UART_HPP

#include "stm32f4xx_hal.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stm32f4xx.h>

#include "ltoa.h"

#define RX_BUFFER_SIZE 64

template<uint8_t USART_ID>
class Uart {
public:
	static UART_HandleTypeDef UART;
private:

	/**
	 * Write functions : send raw strings
	 *
	 */

	template<class T>
	static inline void write(T val) {
		char buffer[10];
		ltoa(val, buffer, 10);
		write((const char *) buffer);
	}

	static inline void write(bool val) {
		(val) ? write("true") : write("false");
	}

	static inline void write(char* val) {
		HAL_UART_Transmit(&UART, (uint8_t*) val, strlen(val), 100);
	}

	static inline void write(char* val, int16_t len) {
		HAL_UART_Transmit(&UART, (uint8_t*) val, len, 100);
	}

	static inline void write(const char* val) {
		HAL_UART_Transmit(&UART, (uint8_t*) val, strlen(val), 100);
	}

	static inline void send_ln() {
		send_char('\r');
		send_char('\n');
	}

public:
	struct ring_buffer {

		ring_buffer() {
		}
		unsigned char buffer[RX_BUFFER_SIZE];
		int head;
		int tail;
	};
	static volatile ring_buffer rx_buffer_;

	enum {
		READ_TIMEOUT = 0, READ_SUCCESS = 1
	};

	enum communicationMode{
		RX = UART_MODE_RX,
		TX = UART_MODE_TX,
		RXTX = UART_MODE_TX_RX
	};
	/**
	 * Initialize the UART  : set pins, enable clocks, set uart, enable interrupt
	 *
	 */
	static inline void init(uint32_t baudrate) {
		GPIO_InitTypeDef GPIO_InitStruct;

		//General settings of pins TX/RX
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

		switch (USART_ID) {
		case 1:
			UART.Instance = USART1;

			GPIO_InitStruct.Pin = GPIO_PIN_15 | GPIO_PIN_10; // Pins A15 (TX) and A10 (RX)
			GPIO_InitStruct.Alternate = GPIO_AF7_USART1;

			__HAL_RCC_GPIOA_CLK_ENABLE();
			__HAL_RCC_USART1_CLK_ENABLE();

			NVIC_SetPriority(USART1_IRQn, 1);
			NVIC_EnableIRQ(USART1_IRQn);

			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
			break;
		case 2:
			UART.Instance = USART2;

			GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3; // Pins A2 (TX) and A3 (RX)
			GPIO_InitStruct.Alternate = GPIO_AF7_USART2;

			__HAL_RCC_GPIOA_CLK_ENABLE();
			__HAL_RCC_USART2_CLK_ENABLE();

			NVIC_SetPriority(USART2_IRQn, 1);
			NVIC_EnableIRQ(USART2_IRQn);

			HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
			break;
		case 6:
			UART.Instance = USART6;

			GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7; // Pins C6 (TX) and C7 (RX)
			GPIO_InitStruct.Alternate = GPIO_AF8_USART6;

			__HAL_RCC_GPIOC_CLK_ENABLE();
			__HAL_RCC_USART6_CLK_ENABLE();

			NVIC_SetPriority(USART6_IRQn, 1);
			NVIC_EnableIRQ(USART6_IRQn);

			HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
			break;
		}

		//UART setting
		UART.Init.BaudRate = baudrate;
		UART.Init.WordLength = UART_WORDLENGTH_8B; // octet comme taille élémentaire (standard)
		UART.Init.StopBits = UART_STOPBITS_1; // bit de stop = 1 (standard)
		UART.Init.Parity = UART_PARITY_NONE; // pas de bit de parité (standard)
		UART.Init.Mode = communicationMode::RXTX;

		if (HAL_UART_Init(&UART) != HAL_OK)
			while(1);

		__HAL_UART_ENABLE_IT(&UART, UART_IT_RXNE);
	}

	static inline void changeCommunicationMode(communicationMode mode)
	{
		UART.Init.Mode = mode;
		if (HAL_UART_Init(&UART) != HAL_OK)
			while(1);
	}
	/**
	 * Base function to send only one byte
	 *
	 */
	static inline void send_char(unsigned char c) {
		HAL_UART_Transmit(&UART, (uint8_t*) c, 1, 100);
	}

	/**
	 * Availability of data in the buffer
	 *
	 */
	static inline bool available(void) {
		return (RX_BUFFER_SIZE + rx_buffer_.head - rx_buffer_.tail)
				% RX_BUFFER_SIZE;
	}

	/**
	 * Read one byte from the ring buffer with a timeout (~ in ms)
	 *
	 */
	static inline uint8_t read_char(unsigned char &byte, uint16_t timeout = 0) {
		uint16_t i = 0;
		uint8_t j = 0;

		// Hack for timeout
		if (timeout > 0)
			timeout *= 26;

		while (!available()) {
			if (timeout > 0) {
				if (i > timeout)
					return READ_TIMEOUT;
				if (j == 0)
					i++;
				j++;
			}
		}

		byte = rx_buffer_.buffer[rx_buffer_.tail];
		rx_buffer_.tail = (rx_buffer_.tail + 1) % RX_BUFFER_SIZE;

		return READ_SUCCESS;
	}

	/**
		 * Read one byte from the ring buffer with a timeout (~ in ms)
		 *
		 */
		static inline uint8_t read_char(char &byte, uint16_t timeout = 0) {
			uint16_t i = 0;
			uint8_t j = 0;

			// Hack for timeout
			if (timeout > 0)
				timeout *= 26;

			while (!available()) {
				if (timeout > 0) {
					if (i > timeout)
						return READ_TIMEOUT;
					if (j == 0)
						i++;
					j++;
				}
			}

			byte = rx_buffer_.buffer[rx_buffer_.tail];
			rx_buffer_.tail = (rx_buffer_.tail + 1) % RX_BUFFER_SIZE;

			return READ_SUCCESS;
		}

	/**
	 * Store one byte in the ring buffer
	 *
	 */
	static inline void store_char(unsigned char c) {
		int i = (rx_buffer_.head + 1) % RX_BUFFER_SIZE;
		if (i != rx_buffer_.tail) {
			rx_buffer_.buffer[rx_buffer_.head] = c;
			rx_buffer_.head = i;
		}
	}


	template<class T>
	static inline void print(T val, int16_t len) {
		write(val, len);
	}

	static inline void printf(const char *format, ...)
	{
		va_list args;
		va_start(args, format);
		char buffer[64];
		vsnprintf(buffer, 64, format, args);
		write(buffer);
		va_end(args);
	}

	__attribute__((format(printf, 1, 0)))
	static inline void printfln(const char *format, ...)
	{
		va_list args;
		va_start(args, format);
		char buffer[64];
		vsnprintf(buffer, 64, format, args);
		write(buffer);
		write("\r");
		va_end(args);
	}

	template<class T>
	static inline uint8_t read(T &val, uint16_t timeout = 0) {
		static char buffer[20];
		uint8_t status = read(buffer, timeout);
		val = atol(buffer);

		return status;
	}

	static inline uint8_t read(float &val, uint16_t timeout = 0) {
		static char buffer[20];
		uint8_t status = read(buffer, timeout);
		val = atof(buffer);

		return status;
	}

	static inline uint8_t read(char* string, uint16_t timeout = 0) {
		static unsigned char buffer;
		uint8_t i = 0;

		do {
			if (read_char(buffer, timeout) == READ_TIMEOUT)
				return READ_TIMEOUT;

			if (i == 0 && buffer == '\r') {
				return READ_SUCCESS;
			}

			if (i == 0 && buffer == '\n') {
				continue;
			}

			string[i] = static_cast<char>(buffer);
			i++;
		} while (string[i - 1] != '\r');

		string[i - 1] = '\0';

		return READ_SUCCESS;
	}

};

template<uint8_t ID>
volatile typename Uart<ID>::ring_buffer Uart<ID>::rx_buffer_;

#endif  /* UART_HPP */

