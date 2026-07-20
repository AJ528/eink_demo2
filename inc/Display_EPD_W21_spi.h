#ifndef _DISPLAY_EPD_W21_SPI_
#define _DISPLAY_EPD_W21_SPI_
#include "stm32f1xx.h"
#include "stm32f1xx_ll_gpio.h"


#define EPD_W21_MOSI_0	LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_10)
#define EPD_W21_MOSI_1	LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_10)

#define EPD_W21_CLK_0	LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_9)
#define EPD_W21_CLK_1	LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_9)

#define EPD_W21_CS_0	LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_8)
#define EPD_W21_CS_1	LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_8)

#define EPD_W21_DC_0	LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_15)
#define EPD_W21_DC_1	LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_15)

#define EPD_W21_RST_0	LL_GPIO_ResetOutputPin(GPIOE, LL_GPIO_PIN_14)
#define EPD_W21_RST_1	LL_GPIO_SetOutputPin(GPIOE, LL_GPIO_PIN_14)

#define isEPD_W21_BUSY LL_GPIO_IsOutputPinSet(GPIOE, LL_GPIO_PIN_13) // for solomen solutions


void SPI_Write(unsigned char value);
void EPD_W21_WriteDATA(unsigned char datas);
void EPD_W21_WriteCMD(unsigned char command);
void EPD_GPIO_Init(void);

#endif  //#ifndef _MCU_SPI_H_


