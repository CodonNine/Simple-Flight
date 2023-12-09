#include "st7789.h"
#include "ui.h"

UI_Status uiStatus;
Cursors cursor;

/**
 * @brief Home screen
 */
void UI_Home()
{
    ST7789_WriteString(0,0,"Welcome to",Font_16x26,FRONTCOLOR,BACKCOLOR);
    uiStatus=UI_HOME;
}


/**
 * @brief Setting screen
 */
void UI_Settings()
{
    ST7789_Fill_Color(BACKCOLOR);
    ST7789_WriteString(56,5,"Settings",Font_16x26,FRONTCOLOR,BACKCOLOR);
    ST7789_DrawFilledTriangle(5,32,20,41,5,50,RED);//Using a triangle as the cursor

    //some opinions
    ST7789_WriteString(25,33,"RF channel set",Font_11x18,FRONTCOLOR,BACKCOLOR);
    ST7789_WriteString(25,33+20,"RF power set",Font_11x18,FRONTCOLOR,BACKCOLOR);
    ST7789_WriteString(25,33+20*2,"RF baudRate set",Font_11x18,FRONTCOLOR,BACKCOLOR);
    ST7789_WriteString(25,33+20*3,"Flight PID set",Font_11x18,FRONTCOLOR,BACKCOLOR);
    uiStatus=UI_SETTINGS;//change the status
}


/**
 * @brief RF channel setting screen
 */
void UI_RF_CH_Set()
{
    ST7789_Fill_Color(BACKCOLOR);
    ST7789_WriteString(0,5,"RF channel set",Font_16x26,FRONTCOLOR,BACKCOLOR);
    ST7789_WriteString(0,35,"Set a channel:0--80",Font_11x18,FRONTCOLOR,BACKCOLOR);

    //The default channel is 55
    ST7789_WriteString(96,35+25,"5",Font_16x26,FRONTCOLOR,BACKCOLOR);//channel value tens
    ST7789_WriteString(96+20,35+25,"5",Font_16x26,FRONTCOLOR,BACKCOLOR);//channel value uints
    ST7789_DrawFilledRectangle(96,35+25+26,16,5,RED);
    ST7789_WriteString(8,35+25+26+10,"Press A to set",Font_16x26,FRONTCOLOR,BACKCOLOR);
    uiStatus=UI_RF_CH_SET;//change the status
}