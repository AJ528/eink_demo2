#include "delay.h"
#include "sys.h"

#include "misc.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//锟斤拷锟绞癸拷锟絬cos,锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷头锟侥硷拷锟斤拷锟斤拷.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos 使锟斤拷	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//锟斤拷锟斤拷锟斤拷只锟斤拷学习使锟矫ｏ拷未锟斤拷锟斤拷锟斤拷锟斤拷锟缴ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟轿猴拷锟斤拷途
//ALIENTEK STM32锟斤拷锟斤拷锟斤拷
//使锟斤拷SysTick锟斤拷锟斤拷通锟斤拷锟斤拷模式锟斤拷锟接迟斤拷锟叫癸拷锟斤拷
//锟斤拷锟斤拷delay_us,delay_ms
//锟斤拷锟斤拷原锟斤拷@ALIENTEK
//锟斤拷锟斤拷锟斤拷坛:www.openedv.com
//锟睫革拷锟斤拷锟斤拷:2012/9/2
//锟芥本锟斤拷V1.5
//锟斤拷权锟斤拷锟叫ｏ拷锟斤拷锟斤拷鼐锟斤拷锟�
//Copyright(C) 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟接科硷拷锟斤拷锟睫癸拷司 2009-2019
//All rights reserved
//********************************************************************************
//V1.2锟睫革拷说锟斤拷
//锟斤拷锟斤拷锟斤拷锟叫讹拷锟叫碉拷锟矫筹拷锟斤拷锟斤拷循锟斤拷锟侥达拷锟斤拷
//锟斤拷止锟斤拷时锟斤拷准确,锟斤拷锟斤拷do while锟结构!

//V1.3锟睫革拷说锟斤拷
//锟斤拷锟斤拷锟剿讹拷UCOSII锟斤拷时锟斤拷支锟斤拷.
//锟斤拷锟绞癸拷锟絬cosII,delay_init锟斤拷锟皆讹拷锟斤拷锟斤拷SYSTICK锟斤拷值,使之锟斤拷ucos锟斤拷TICKS_PER_SEC锟斤拷应.
//delay_ms锟斤拷delay_us也锟斤拷锟斤拷锟斤拷锟斤拷锟絬cos锟侥革拷锟斤拷.
//delay_us锟斤拷锟斤拷锟斤拷ucos锟斤拷使锟斤拷,锟斤拷锟斤拷准确锟饺很革拷,锟斤拷锟斤拷要锟斤拷锟斤拷没锟斤拷占锟矫讹拷锟斤拷亩锟绞憋拷锟�.
//delay_ms锟斤拷ucos锟斤拷,锟斤拷锟皆碉拷锟斤拷OSTimeDly锟斤拷锟斤拷,锟斤拷未锟斤拷锟斤拷ucos时,锟斤拷锟斤拷锟斤拷delay_us实锟斤拷,锟接讹拷准确锟斤拷时
//锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷始锟斤拷锟斤拷锟斤拷,锟斤拷锟斤拷锟斤拷锟斤拷ucos之锟斤拷delay_ms锟斤拷锟斤拷锟斤拷时锟侥筹拷锟斤拷,选锟斤拷OSTimeDly实锟街伙拷锟斤拷delay_us实锟斤拷.

//V1.4锟睫革拷说锟斤拷 20110929
//锟睫革拷锟斤拷使锟斤拷ucos,锟斤拷锟斤拷ucos未锟斤拷锟斤拷锟斤拷时锟斤拷,delay_ms锟斤拷锟叫讹拷锟睫凤拷锟斤拷应锟斤拷bug.
//V1.5锟睫革拷说锟斤拷 20120902
//锟斤拷delay_us锟斤拷锟斤拷ucos锟斤拷锟斤拷锟斤拷锟斤拷止锟斤拷锟斤拷ucos锟斤拷锟絛elay_us锟斤拷执锟叫ｏ拷锟斤拷锟杰碉拷锟铰碉拷锟斤拷时锟斤拷准锟斤拷
////////////////////////////////////////////////////////////////////////////////// 	 
static u8  fac_us=0;//us锟斤拷时锟斤拷锟斤拷锟斤拷
static u16 fac_ms=0;//ms锟斤拷时锟斤拷锟斤拷锟斤拷
#ifdef OS_CRITICAL_METHOD 	//锟斤拷锟絆S_CRITICAL_METHOD锟斤拷锟斤拷锟斤拷,说锟斤拷使锟斤拷ucosII锟斤拷.
//systick锟叫断凤拷锟斤拷锟斤拷,使锟斤拷ucos时锟矫碉拷
void SysTick_Handler(void)
{				   
	OSIntEnter();		//锟斤拷锟斤拷锟叫讹拷
    OSTimeTick();       //锟斤拷锟斤拷ucos锟斤拷时锟接凤拷锟斤拷锟斤拷锟�               
    OSIntExit();        //锟斤拷锟斤拷锟斤拷锟斤拷锟叫伙拷锟斤拷锟叫讹拷
}
#endif

//锟斤拷始锟斤拷锟接迟猴拷锟斤拷
//锟斤拷使锟斤拷ucos锟斤拷时锟斤拷,锟剿猴拷锟斤拷锟斤拷锟绞硷拷锟絬cos锟斤拷时锟接斤拷锟斤拷
//SYSTICK锟斤拷时锟接固讹拷为HCLK时锟接碉拷1/8
//SYSCLK:系统时锟斤拷
void delay_init()	 
{

#ifdef OS_CRITICAL_METHOD 	//锟斤拷锟絆S_CRITICAL_METHOD锟斤拷锟斤拷锟斤拷,说锟斤拷使锟斤拷ucosII锟斤拷.
	u32 reload;
#endif
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选锟斤拷锟解部时锟斤拷  HCLK/8
	fac_us=SystemCoreClock/8000000;	//为系统时锟接碉拷1/8  
	 
#ifdef OS_CRITICAL_METHOD 	//锟斤拷锟絆S_CRITICAL_METHOD锟斤拷锟斤拷锟斤拷,说锟斤拷使锟斤拷ucosII锟斤拷.
	reload=SystemCoreClock/8000000;		//每锟斤拷锟接的硷拷锟斤拷锟斤拷锟斤拷 锟斤拷位为K	   
	reload*=1000000/OS_TICKS_PER_SEC;//锟斤拷锟斤拷OS_TICKS_PER_SEC锟借定锟斤拷锟绞憋拷锟�
							//reload为24位锟侥达拷锟斤拷,锟斤拷锟街�:16777216,锟斤拷72M锟斤拷,约锟斤拷1.86s锟斤拷锟斤拷	
	fac_ms=1000/OS_TICKS_PER_SEC;//锟斤拷锟斤拷ucos锟斤拷锟斤拷锟斤拷时锟斤拷锟斤拷锟劫碉拷位	   
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//锟斤拷锟斤拷SYSTICK锟叫讹拷
	SysTick->LOAD=reload; 	//每1/OS_TICKS_PER_SEC锟斤拷锟叫讹拷一锟斤拷	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//锟斤拷锟斤拷SYSTICK    
#else
	fac_ms=(u16)fac_us*1000;//锟斤拷ucos锟斤拷,锟斤拷锟斤拷每锟斤拷ms锟斤拷要锟斤拷systick时锟斤拷锟斤拷   
#endif
}								    

#ifdef OS_CRITICAL_METHOD	//使锟斤拷锟斤拷ucos
//锟斤拷时nus
//nus为要锟斤拷时锟斤拷us锟斤拷.		    								   
void delay_us(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;	//LOAD锟斤拷值	    	 
	ticks=nus*fac_us; 			//锟斤拷要锟侥斤拷锟斤拷锟斤拷	  		 
	tcnt=0;
	told=SysTick->VAL;        	//锟秸斤拷锟斤拷时锟侥硷拷锟斤拷锟斤拷值
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;//锟斤拷锟斤拷注锟斤拷一锟斤拷SYSTICK锟斤拷一锟斤拷锟捷硷拷锟侥硷拷锟斤拷锟斤拷锟酵匡拷锟斤拷锟斤拷.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;//时锟戒超锟斤拷/锟斤拷锟斤拷要锟接迟碉拷时锟斤拷,锟斤拷锟剿筹拷.
		}  
	}; 									    
}
//锟斤拷时nms
//nms:要锟斤拷时锟斤拷ms锟斤拷
void delay_ms(u16 nms)
{	
	if(OSRunning==TRUE)//锟斤拷锟給s锟窖撅拷锟斤拷锟斤拷锟斤拷	    
	{		  
		if(nms>=fac_ms)//锟斤拷时锟斤拷时锟斤拷锟斤拷锟絬cos锟斤拷锟斤拷锟斤拷时锟斤拷锟斤拷锟斤拷 
		{
   			OSTimeDly(nms/fac_ms);//ucos锟斤拷时
		}
		nms%=fac_ms;				//ucos锟窖撅拷锟睫凤拷锟结供锟斤拷么小锟斤拷锟斤拷时锟斤拷,锟斤拷锟斤拷锟斤拷通锟斤拷式锟斤拷时    
	}
	delay_us((u32)(nms*1000));	//锟斤拷通锟斤拷式锟斤拷时,锟斤拷时ucos锟睫凤拷锟斤拷锟斤拷锟斤拷锟斤拷.
}
#else//锟斤拷锟斤拷ucos时
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
#endif
































