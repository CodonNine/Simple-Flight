//
// Created by YU-XIAO on 2023/12/9.
//

#ifndef UI_H
#define UI_H

#define BACKCOLOR   WHITE
#define FRONTCOLOR  BLACK


/**
 * Screen status
 */
typedef enum
{
    UI_HOME=0,
    UI_SETTINGS,
    UI_RF_CH_SET,
    UI_RF_PWR_SET,
    UI_RF_BAUD_SET,
    UI_PID_SET
}UI_Status;


typedef struct
{
    int8_t setting_cursor;          //cursor in setting screen
    uint8_t channel_set_cursor;     //cursor in RF channel setting screen
}Cursors;

extern Cursors cursor;
extern UI_Status uiStatus;
void UI_Home();
void UI_Settings();
void UI_RF_CH_Set();
#endif //UI_H
