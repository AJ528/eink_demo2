#ifndef _DISPLAY_EPD_W21_H_
#define _DISPLAY_EPD_W21_H_


#define EPD_WIDTH   800 
#define EPD_HEIGHT  480
#define EPD_ARRAY  EPD_WIDTH*EPD_HEIGHT/8  


//Full screen update display
void EPD_Init(void); 
void EPD_DeepSleep(void);


#endif



