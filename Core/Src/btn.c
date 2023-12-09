#include "multi_button.h"
#include "main.h"
#include "usart.h"
#include "st7789.h"
#include "ui.h"

struct Button btn_x;
struct Button btn_y;
struct Button btn_a;
struct Button btn_b;

struct Button btn_left;
struct Button btn_right;
struct Button btn_up;
struct Button btn_down;

struct Button btn_l1;
struct Button btn_l2;
struct Button btn_menu;
struct Button btn_back;

static int8_t rf_ch_val_units;
static int8_t rf_ch_val_tens;

/**
 * button IDs
 */
typedef enum
{
    BTN_X = 0,
    BTN_Y,
    BTN_A,
    BTN_B,

    BTN_UP,
    BTN_DOWN,
    BTN_LEFT,
    BTN_RIGHT,

    BTN_L1,
    BTN_L2,

    BTN_BACK,
    BTN_MENU,


} ButtonIDs;

/**
 * @brief button X pressed
 * @param btn
 */
void BTN_X_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("X\r\n");
}


/**
 * @brief button Y pressed
 * @param btn
 */
void BTN_Y_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("Y\r\n");
}

/**
 * @brief button A pressed
 * @param btn
 */
void BTN_A_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("A\r\n");
    /**
     * In the setting screen,entry in the opinion
     * which is pointed by the cursor
     */
    if (uiStatus == UI_SETTINGS)
    {
        if (cursor.setting_cursor == 0)//
        {
            UI_RF_CH_Set();
        }
    }

    /**
     * In RF channel setting screen,set the channel number
     */
    else if (uiStatus == UI_RF_CH_SET)
    {
        U1_Printf("RF channel:%d\r\n", rf_ch_val_tens * 10 + rf_ch_val_units);
        ST7789_Fill(0, 35 + 25 + 26 + 10, 239, 134, BACKCOLOR);
        ST7789_WriteString(64, 35 + 25 + 26 + 10, "Set OK!", Font_16x26, FRONTCOLOR, BACKCOLOR);
    }
}


/**
 * @brief button B pressed
 * @param btn
 */
void BTN_B_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("B\r\n");
}


/**
 * @brief button UP pressed
 * @param btn
 */
void BTN_UP_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("UP\r\n");
    //In setting screen
    if (uiStatus == UI_SETTINGS)
    {
        cursor.setting_cursor--;
        if (cursor.setting_cursor < 0) cursor.setting_cursor = 0;
        ST7789_DrawFilledTriangle(5, 32 + 20 * (cursor.setting_cursor + 1), 20, 41 + 20 * (cursor.setting_cursor + 1),
                                  5, 50 + 20 * (cursor.setting_cursor + 1), BACKCOLOR);
        ST7789_DrawFilledTriangle(5, 32 + 20 * cursor.setting_cursor, 20, 41 + 20 * cursor.setting_cursor, 5,
                                  50 + 20 * cursor.setting_cursor, RED);
    }
    //In RF channel setting screen
    else if (uiStatus == UI_RF_CH_SET)
    {
        if (cursor.channel_set_cursor == 1)//cursor at units
        {
            rf_ch_val_units++;
            if (rf_ch_val_units > 9) rf_ch_val_units = 0;
            ST7789_Draw_Single_Num(96 + 20, 35 + 25, rf_ch_val_units, Font_16x26, FRONTCOLOR, BACKCOLOR);
        }
        if (cursor.channel_set_cursor == 0)//cursor at tens
        {
            rf_ch_val_tens++;
            if (rf_ch_val_tens > 8) rf_ch_val_tens = 0;
            ST7789_Draw_Single_Num(96, 35 + 25, rf_ch_val_tens, Font_16x26, FRONTCOLOR, BACKCOLOR);
        }
    }
}


/**
 * @brief button DOWN pressed
 * @param btn
 */
void BTN_DOWN_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("DOWN\r\n");
    if (uiStatus == UI_SETTINGS)
    {
        cursor.setting_cursor++;
        if (cursor.setting_cursor > 4) cursor.setting_cursor = 4;
        ST7789_DrawFilledTriangle(5, 32 + 20 * (cursor.setting_cursor - 1), 20, 41 + 20 * (cursor.setting_cursor - 1),
                                  5, 50 + 20 * (cursor.setting_cursor - 1),
                                  BACKCOLOR);
        ST7789_DrawFilledTriangle(5, 32 + 20 * cursor.setting_cursor, 20, 41 + 20 * cursor.setting_cursor, 5,
                                  50 + 20 * cursor.setting_cursor, RED);
    } else if (uiStatus == UI_RF_CH_SET)
    {
        if (cursor.channel_set_cursor == 1)
        {
            rf_ch_val_units--;
            if (rf_ch_val_units < 0) rf_ch_val_units = 9;
            ST7789_Draw_Single_Num(96 + 20, 35 + 25, rf_ch_val_units, Font_16x26, FRONTCOLOR, BACKCOLOR);
        }
        if (cursor.channel_set_cursor == 0)
        {
            rf_ch_val_tens--;
            if (rf_ch_val_tens < 0) rf_ch_val_tens = 8;
            ST7789_Draw_Single_Num(96, 35 + 25, rf_ch_val_tens, Font_16x26, FRONTCOLOR, BACKCOLOR);
        }
    }
}


/**
 * @brief button left pressed
 * @param btn
 */
void BTN_LEFT_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("LEFT\r\n");
    //In RF channel setting screen
    if (uiStatus == UI_RF_CH_SET)
    {
       /**
        *  When left or right button is pressed,change the cursor's position
        */
        if (cursor.channel_set_cursor == 0)//cursor at tens
        {
            ST7789_DrawFilledRectangle(96 + 20, 35 + 25 + 26, 16, 5, RED);
            ST7789_DrawFilledRectangle(96, 35 + 25 + 26, 16, 5, BACKCOLOR);
            cursor.channel_set_cursor = 1;
        } else if (cursor.channel_set_cursor == 1)//cursor at units
        {
            ST7789_DrawFilledRectangle(96, 35 + 25 + 26, 16, 5, RED);
            ST7789_DrawFilledRectangle(96 + 20, 35 + 25 + 26, 16, 5, BACKCOLOR);
            cursor.channel_set_cursor = 0;
        }
    }
}


/**
 * @brief button right pressed
 * @param btn
 */
void BTN_RIGHT_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("RIGHT\r\n");
    /**
     * Same as left button
     */
    if (uiStatus == UI_RF_CH_SET)
    {
        if (cursor.channel_set_cursor == 0)
        {
            ST7789_DrawFilledRectangle(96 + 20, 35 + 25 + 26, 16, 5, RED);
            ST7789_DrawFilledRectangle(96, 35 + 25 + 26, 16, 5, BACKCOLOR);
            cursor.channel_set_cursor = 1;
        } else if (cursor.channel_set_cursor == 1)
        {
            ST7789_DrawFilledRectangle(96, 35 + 25 + 26, 16, 5, RED);
            ST7789_DrawFilledRectangle(96 + 20, 35 + 25 + 26, 16, 5, BACKCOLOR);
            cursor.channel_set_cursor = 0;
        }
    }
}


/**
 * @brief button l1 pressed
 * @param btn
 */
void BTN_L1_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("L1\r\n");
}


/**
 * @brief button l2 pressed
 * @param btn
 */
void BTN_L2_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("L2\r\n");
}


/**
 * @brief button menu pressed
 * @param btn
 */
void BTN_MENU_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("MENU\r\n");
    if (uiStatus != UI_SETTINGS)
        UI_Settings();
}

/**
 * @brief button back pressed
 * @param btn
 */
void BTN_BACK_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("BACK\r\n");
}


/**
 * @brief button X double click
 * @param btn
 */
void BTN_X_PRESS_DOUBLE_Handler(void *btn)
{
    U1_Printf("X double click\r\n");
}

uint8_t read_button_GPIO(uint8_t button_id)
{
    // you can share the GPIO read function with multiple Buttons
    switch (button_id)
    {
        //Button X|Y|A|B
        case BTN_X:
            return HAL_GPIO_ReadPin(K_X_GPIO_Port, K_X_Pin);
            break;
        case BTN_Y:
            return HAL_GPIO_ReadPin(K_Y_GPIO_Port, K_Y_Pin);
            break;
        case BTN_A:
            return HAL_GPIO_ReadPin(K_A_GPIO_Port, K_A_Pin);
            break;
        case BTN_B:
            return HAL_GPIO_ReadPin(K_B_GPIO_Port, K_B_Pin);
            break;


        case BTN_UP:
            return HAL_GPIO_ReadPin(K_UP_GPIO_Port, K_UP_Pin);
            break;
        case BTN_DOWN:
            return HAL_GPIO_ReadPin(K_DOWN_GPIO_Port, K_DOWN_Pin);
            break;
        case BTN_LEFT:
            return HAL_GPIO_ReadPin(K_L_GPIO_Port, K_L_Pin);
            break;
        case BTN_RIGHT:
            return HAL_GPIO_ReadPin(K_R_GPIO_Port, K_R_Pin);
            break;


            //Btn L1&L2
        case BTN_L1:
            return HAL_GPIO_ReadPin(K_L1_GPIO_Port, K_L1_Pin);
            break;
        case BTN_L2:
            return HAL_GPIO_ReadPin(K_L2_GPIO_Port, K_L2_Pin);
            break;

            //Btn BACK&MENU
        case BTN_MENU:
            return HAL_GPIO_ReadPin(K_MENU_GPIO_Port, K_MENU_Pin);
            break;
        case BTN_BACK:
            return HAL_GPIO_ReadPin(K_BACK_GPIO_Port, K_BACK_Pin);
        default:
            return 0;
            break;
    }
}

void My_Button_Init()
{
    button_init(&btn_x, read_button_GPIO, 0, BTN_X);
    button_attach(&btn_x, PRESS_DOWN, BTN_X_PRESS_DOWN_Handler);
    button_attach(&btn_x, DOUBLE_CLICK, BTN_X_PRESS_DOUBLE_Handler);
    button_start(&btn_x);

    button_init(&btn_y, read_button_GPIO, 0, BTN_Y);
    button_attach(&btn_y, PRESS_DOWN, BTN_Y_PRESS_DOWN_Handler);
    button_start(&btn_y);

    button_init(&btn_a, read_button_GPIO, 0, BTN_A);
    button_attach(&btn_a, PRESS_DOWN, BTN_A_PRESS_DOWN_Handler);
    button_start(&btn_a);

    button_init(&btn_b, read_button_GPIO, 0, BTN_B);
    button_attach(&btn_b, PRESS_DOWN, BTN_B_PRESS_DOWN_Handler);
    button_start(&btn_b);

    button_init(&btn_up, read_button_GPIO, 0, BTN_UP);
    button_attach(&btn_up, PRESS_DOWN, BTN_UP_PRESS_DOWN_Handler);
    button_start(&btn_up);

    button_init(&btn_down, read_button_GPIO, 0, BTN_DOWN);
    button_attach(&btn_down, PRESS_DOWN, BTN_DOWN_PRESS_DOWN_Handler);
    button_start(&btn_down);

    button_init(&btn_left, read_button_GPIO, 0, BTN_LEFT);
    button_attach(&btn_left, PRESS_DOWN, BTN_LEFT_PRESS_DOWN_Handler);
    button_start(&btn_left);

    button_init(&btn_right, read_button_GPIO, 0, BTN_RIGHT);
    button_attach(&btn_right, PRESS_DOWN, BTN_RIGHT_PRESS_DOWN_Handler);
    button_start(&btn_right);

    button_init(&btn_l1, read_button_GPIO, 0, BTN_L1);
    button_attach(&btn_l1, PRESS_DOWN, BTN_L1_PRESS_DOWN_Handler);
    button_start(&btn_l1);

    button_init(&btn_l2, read_button_GPIO, 0, BTN_L2);
    button_attach(&btn_l2, PRESS_DOWN, BTN_L2_PRESS_DOWN_Handler);
    button_start(&btn_l2);

    button_init(&btn_menu, read_button_GPIO, 0, BTN_MENU);
    button_attach(&btn_menu, PRESS_DOWN, BTN_MENU_PRESS_DOWN_Handler);
    button_start(&btn_menu);

    button_init(&btn_back, read_button_GPIO, 0, BTN_BACK);
    button_attach(&btn_back, PRESS_DOWN, BTN_BACK_PRESS_DOWN_Handler);
    button_start(&btn_back);
}