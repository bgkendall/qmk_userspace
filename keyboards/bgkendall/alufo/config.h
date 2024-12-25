#pragma once

#define SERIAL_USART_HALF_DUPLEX
#define SERIAL_USART_DRIVER      SD2
#define SERIAL_USART_TX_PAL_MODE 1
#define SERIAL_USART_TX_PIN      A2
#define SERIAL_USART_RX_PIN      A3

#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 1
#define WS2812_PWM_PAL_MODE 6
#define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM1_UP