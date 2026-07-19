#include "delay.h"
#include "sys.h"

#include "misc.h"

static u8  fac_us=0;//us锟斤拷时锟斤拷锟斤拷锟斤拷
static u16 fac_ms=0;//ms锟斤拷时锟斤拷锟斤拷锟斤拷

//锟斤拷始锟斤拷锟接迟猴拷锟斤拷
//锟斤拷使锟斤拷ucos锟斤拷时锟斤拷,锟剿猴拷锟斤拷锟斤拷锟绞硷拷锟絬cos锟斤拷时锟接斤拷锟斤拷
//SYSTICK锟斤拷时锟接固讹拷为HCLK时锟接碉拷1/8
//SYSCLK:系统时锟斤拷
void delay_init()	 
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选锟斤拷锟解部时锟斤拷  HCLK/8
	fac_us=SystemCoreClock/8000000;	//为系统时锟接碉拷1/8  
	fac_ms=(u16)fac_us*1000;//锟斤拷ucos锟斤拷,锟斤拷锟斤拷每锟斤拷ms锟斤拷要锟斤拷systick时锟斤拷锟斤拷   
}								    

//锟斤拷时nus
//nus为要锟斤拷时锟斤拷us锟斤拷.		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //时锟斤拷锟斤拷锟�	  		 
	SysTick->VAL=0x00;        //锟斤拷占锟斤拷锟斤拷锟�
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //锟斤拷始锟斤拷锟斤拷	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//锟饺达拷时锟戒到锟斤拷   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //锟截闭硷拷锟斤拷锟斤拷
	SysTick->VAL =0X00;       //锟斤拷占锟斤拷锟斤拷锟�	 
}
//锟斤拷时nms
//注锟斤拷nms锟侥凤拷围
//SysTick->LOAD为24位锟侥达拷锟斤拷,锟斤拷锟斤拷,锟斤拷锟斤拷锟绞蔽�:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK锟斤拷位为Hz,nms锟斤拷位为ms
//锟斤拷72M锟斤拷锟斤拷锟斤拷,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//时锟斤拷锟斤拷锟�(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //锟斤拷占锟斤拷锟斤拷锟�
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //锟斤拷始锟斤拷锟斤拷  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//锟饺达拷时锟戒到锟斤拷   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //锟截闭硷拷锟斤拷锟斤拷
	SysTick->VAL =0X00;       //锟斤拷占锟斤拷锟斤拷锟�	  	    
} 

//锟斤拷时ns
void delay_s(u16 ns)
{
	u16 i;
	for(i=0;i<ns;i++)
	delay_ms(1000);
}
































