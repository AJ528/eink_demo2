#include "Display_EPD_W21_spi.h"

#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"

//E-paper GPIO initialization
void EPD_GPIO_Init(void)
{
	LL_GPIO_InitTypeDef  GPIO_InitStructure;	
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOE);
	  				     	
	 //CS-->PD8   SCK-->PD9  SDO--->PD10 
	GPIO_InitStructure.Pin = LL_GPIO_PIN_8|LL_GPIO_PIN_9|LL_GPIO_PIN_10;		//Port configuration
	GPIO_InitStructure.Mode = LL_GPIO_MODE_OUTPUT; 		 			
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Init(GPIOD, &GPIO_InitStructure);	  			
	 // D/C--->PE15	   RES-->PE14
	GPIO_InitStructure.Pin = LL_GPIO_PIN_14|LL_GPIO_PIN_15;		//Port configuration
	GPIO_InitStructure.Mode = LL_GPIO_MODE_OUTPUT; 		 			
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;		 		
	LL_GPIO_Init(GPIOE, &GPIO_InitStructure);	  				     			
	// BUSY--->PE13
	GPIO_InitStructure.Pin  = LL_GPIO_PIN_13;
	GPIO_InitStructure.Mode = LL_GPIO_MODE_INPUT;	//Pull up input
	GPIO_InitStructure.Pull = LL_GPIO_PULL_UP;
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
 	LL_GPIO_Init(GPIOE, &GPIO_InitStructure);				//Initialize GPIO
	
	 //LED 
	GPIO_InitStructure.Pin = LL_GPIO_PIN_12;		//Port configuration
	GPIO_InitStructure.Mode = LL_GPIO_MODE_OUTPUT; 		 			
	GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;		 		
	LL_GPIO_Init(GPIOE, &GPIO_InitStructure);
}



//SPI write byte
void SPI_Write(unsigned char value)
{				   			 
	unsigned char i;
  EPD_W21_CLK_0;  
	for(i=0;i<8;i++)
	{ 
		if(value&0x80)
		  EPD_W21_MOSI_1 ;
		else
		  EPD_W21_MOSI_0 ;
		EPD_W21_CLK_1;  
	  EPD_W21_CLK_0;  
		value=value<<1;
  }
}

//SPI write command
void EPD_W21_WriteCMD(unsigned char command)
{
	EPD_W21_CS_0;
	EPD_W21_DC_0;  // D/C#   0:command  1:data
	SPI_Write(command);
	EPD_W21_CS_1;
}
//SPI write data
void EPD_W21_WriteDATA(unsigned char datas)
{
	EPD_W21_CS_0;
	EPD_W21_DC_1;  // D/C#   0:command  1:data
	SPI_Write(datas);
	EPD_W21_CS_1;
}






