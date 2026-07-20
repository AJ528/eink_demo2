#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"

//Delay Functions
void delay_xms(unsigned int xms)
{
	unsigned int i;
	while(xms--)
	{
		i=8000;
		while(i--);
	}
}

////////////////////////////////////E-paper demo//////////////////////////////////////////////////////////
//Busy function
void lcd_chkstatus(void)
{ 
  while(1)
  {	 //=0 BUSY
     if(isEPD_W21_BUSY==1) break;
  }  
}
//Full screen update initialization
void EPD_Init(void)
{
	EPD_W21_RST_0;  // Module reset   
	delay_xms(10);//At least 10ms delay 
	EPD_W21_RST_1;
	delay_xms(10); //At least 10ms delay 

	EPD_W21_WriteCMD(0x01);			//POWER SETTING
	EPD_W21_WriteDATA (0x07);
	EPD_W21_WriteDATA (0x07);    //VGH=20V,VGL=-20V
	EPD_W21_WriteDATA (0x3f);		//VDH=15V
	EPD_W21_WriteDATA (0x3f);		//VDL=-15V

	//Enhanced display drive(Add 0x06 command)
	EPD_W21_WriteCMD(0x06);			//Booster Soft Start 
	EPD_W21_WriteDATA (0x17);
	EPD_W21_WriteDATA (0x17);   
	EPD_W21_WriteDATA (0x28);		
	EPD_W21_WriteDATA (0x17);	

	EPD_W21_WriteCMD(0x04); //POWER ON
	delay_xms(100);  
	lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal

	EPD_W21_WriteCMD(0X00);			//PANNEL SETTING
	EPD_W21_WriteDATA(0x1F);   //KW-3f   KWR-2F	BWROTP 0f	BWOTP 1f

	EPD_W21_WriteCMD(0x61);        	//tres			
	EPD_W21_WriteDATA (0x03);		//source 800
	EPD_W21_WriteDATA (0x20);
	EPD_W21_WriteDATA (0x01);		//gate 480
	EPD_W21_WriteDATA (0xE0);  

	EPD_W21_WriteCMD(0X15);		
	EPD_W21_WriteDATA(0x00);		

	EPD_W21_WriteCMD(0X50);			//VCOM AND DATA INTERVAL SETTING
	EPD_W21_WriteDATA(0x10);
	EPD_W21_WriteDATA(0x07);

	EPD_W21_WriteCMD(0X60);			//TCON SETTING
	EPD_W21_WriteDATA(0x22);
	
}
//////////////////////////////Display Update Function///////////////////////////////////////////////////////


//Deep sleep function
void EPD_DeepSleep(void)
{  	
		EPD_W21_WriteCMD(0X50);  //VCOM AND DATA INTERVAL SETTING			
		EPD_W21_WriteDATA(0xf7); //WBmode:VBDF 17|D7 VBDW 97 VBDB 57		WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7	

		EPD_W21_WriteCMD(0X02);  	//power off
	  lcd_chkstatus();          //waiting for the electronic paper IC to release the idle signal 	
	  EPD_W21_WriteCMD(0X07);  	//deep sleep
		EPD_W21_WriteDATA(0xA5);
}

