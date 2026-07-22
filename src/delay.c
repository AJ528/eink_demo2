#include "delay.h"
// #include "sys.h"

// #include "misc.h"

#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_utils.h"

#include "stm32f1xx.h"

#include <stdint.h>


static uint8_t  fac_us=0;
static uint16_t fac_ms=0;

void delay_init()	 
{
	SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;

	fac_us=SystemCoreClock/8000000;

	fac_ms=(uint16_t)fac_us*1000;
}								    
    								   
void delay_us(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us;
	SysTick->VAL=0x00; 
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL =0X00;
}

void delay_ms(uint16_t nms)
{	 		  	  
	uint32_t temp;		   
	SysTick->LOAD=(uint32_t)nms*fac_ms;
	SysTick->VAL =0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL =0X00;  
} 

//锟斤拷时ns
void delay_s(uint16_t ns)
{
	// uint16_t i;
	// for(i=0;i<ns;i++)
	// delay_ms(1000);
	LL_mDelay(1000 * ns);
}































