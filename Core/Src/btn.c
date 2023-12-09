#include "multi_button.h"
#include "main.h"
#include "usart.h"

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


void BTN_X_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("X\r\n");
}

void BTN_Y_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("Y\r\n");
}

void BTN_A_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("A\r\n");
}

void BTN_B_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("B\r\n");
}

void BTN_UP_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("UP\r\n");
}

void BTN_DOWN_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("DOWN\r\n");
}

void BTN_LEFT_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("LEFT\r\n");
}

void BTN_RIGHT_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("RIGHT\r\n");
}

void BTN_L1_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("L1\r\n");
}

void BTN_L2_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("L2\r\n");
}

void BTN_MENU_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("MENU\r\n");
}

void BTN_BACK_PRESS_DOWN_Handler(void *btn)
{
    U1_Printf("BACK\r\n");
}

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