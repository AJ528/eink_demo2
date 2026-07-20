
#include "sysclk.h"

#include "gpio.h"

//EPD
#include "display_epd.h"
#include "Display_EPD_W21.h"


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

extern uint32_t _vector_table_offset;

int main(void)
{
  SCB->VTOR = (uint32_t)(&_vector_table_offset);  // set the vector table offset
  enable_cycle_count();

  GPIO_init();
	sysclk_init();

	EPD_Init(); //Full screen update initialization.

	EPD_whitescreen_white();

	EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.

	while(1);
}	


static inline void enable_cycle_count(void)
{
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CYCCNT = 0;
  DWT->LSUCNT = 0;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk | DWT_CTRL_LSUEVTENA_Msk;
}