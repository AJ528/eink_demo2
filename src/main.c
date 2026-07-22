
#include "sysclk.h"

#include "gpio.h"

//EPD
#include "display_epd.h"
#include "Display_EPD_W21.h"
#include "demo_images.h"

#include "delay.h"
#include "stm32f1xx_ll_utils.h"


#include "stm32f1xx.h"

//Tips//
/*
1.Flickering is normal when EPD is performing a full screen update to clear ghosting from the previous image so to ensure better clarity and legibility for the new image.
2.There will be no flicker when EPD performs a partial update.
3.Please make sue that EPD enters sleep mode when update is completed and always leave the sleep mode command. Otherwise, this may result in a reduced lifespan of EPD.
4.Please refrain from inserting EPD to the FPC socket or unplugging it when the MCU is being powered to prevent potential damage.)
5.Re-initialization is required for every full screen update.
6.When porting the program, set the BUSY pin to input mode and other pins to output mode.
*/

static inline void enable_cycle_count(void);
static void standard_demo(void);

extern uint32_t _vector_table_offset;

int main(void)
{
  SCB->VTOR = (uint32_t)(&_vector_table_offset);  // set the vector table offset
  enable_cycle_count();

  GPIO_init();
	sysclk_init();

  // delay_init();

  // standard_demo();

	EPD_Init(); //Full screen update initialization.

  // EPD_WhiteScreen_White();
	EPD_whitescreen_white();

	EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.


	while(1);
}	


static void standard_demo(void)
{
  EPD_Init(); //Full screen update initialization.
  EPD_WhiteScreen_White(); //Clear screen function.
  EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
  delay_s(4); //Delay for 2s.	
  /************Full display(3s)*******************/
  EPD_Init(); //Full screen update initialization.
  EPD_WhiteScreen_ALL(gImage_1); //To Display one image using full screen update.
  EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
  delay_s(4); //Delay for 2s.	
    
  /************Fast update mode(1.5s)*******************/
  EPD_Init_Fast(); //Fast update initialization.
  EPD_WhiteScreen_ALL_Fast(gImage_2); //To display one image using fast update.
  EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
  delay_s(4); //Delay for 2s.	
  /************4 Gray update mode(2s)*******************/
  EPD_Init_4G(); //Fast update initialization.
  EPD_WhiteScreen_ALL_4G(gImage_4G1); //To display one image using fast update.
  EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
  delay_s(4); //Delay for 2s.	

//Partial update demostration.
//Partial update demo support displaying a clock at 5 locations with 00:00.  If you need to perform partial update more than 5 locations, please use the feature of using partial update at the full screen demo.
//After 5 partial update, implement a full screen update to clear the ghosting caused by partial update.
//////////////////////Partial update time demo/////////////////////////////////////
  EPD_Init(); //Electronic paper initialization.	
  EPD_SetRAMValue_BaseMap(gImage_basemap); //Please do not delete the background color function, otherwise it will cause unstable display during partial update.
  EPD_Init_Part(); //Pa update initialization.
  for(uint32_t i=0;i<6;i++)
  {
    EPD_Dis_Part_Time(240,180,Num[1],Num[0],gImage_numdot,Num[0],Num[i],5,104,48); //x,y,DATA-A~E,Resolution 48*104              		
  }				
  EPD_DeepSleep();  //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
  delay_s(4); //Delay for 2s.	
  EPD_Init(); //Full screen update initialization.
  EPD_WhiteScreen_White(); //Clear screen function.
  EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.
  delay_s(4); //Delay for 2s.	
}

static inline void enable_cycle_count(void)
{
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CYCCNT = 0;
  DWT->LSUCNT = 0;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk | DWT_CTRL_LSUEVTENA_Msk;
}