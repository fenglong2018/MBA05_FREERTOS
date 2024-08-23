/*************************************************************************
*  	文件名称:  	Hal_KeyLed.c
*  	文件描述:  	按键初始化、LED初始化、按键检测、LED驱动
*  	历史记录:
*  	创建时间:  	2024-05-09
*  	创建人:  	江昌钤
*  	修改时间:
*	修改人:
*   描述:
*************************************************************************/

/*************************************************************************
头文件引用声明
*************************************************************************/
#include    "at32f435_437_gpio.h"
#include    "at32f435_437_scfg.h"

#include    "Hal_Led.h"
/************************************************************************
宏定义
*************************************************************************/

/*************************************************************************
内部结构、枚举、公用体等结构声明
*************************************************************************/

/*************************************************************************
内部静态变量定义

全局变量定义

extern 外部变量声明

*************************************************************************/

/*************************************************************************
静态函数声明

extern 外部函数声明
*************************************************************************/

/*************************************************************************
函数定义
*************************************************************************/
/*----------------------------------------------------------------------------
函数名称： Hal_Key_Init
具体描述： 按键初始化
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
函数名称： Hal_Led_Init
具体描述： LED初始化
----------------------------------------------------------------------------*/
void Hal_Led_Init(void)
{
  gpio_init_type  gpio_init_struct;
     
  gpio_default_para_init(&gpio_init_struct);
  /*   电量灯1   */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_init_struct.gpio_pins = IO_LED_BAT1;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(PT_LED_BAT1, &gpio_init_struct);
  /*   电量灯2   */
  gpio_init_struct.gpio_pins = IO_LED_BAT2;
  gpio_init(PT_LED_BAT2, &gpio_init_struct);
  /*   电量灯3  */
  gpio_init_struct.gpio_pins = IO_LED_BAT3;
  gpio_init(PT_LED_BAT3, &gpio_init_struct);
  /*   电量灯4   */
  gpio_init_struct.gpio_pins = IO_LED_BAT4;
  gpio_init(PT_LED_BAT4, &gpio_init_struct);
  
  /*   故障灯   */
  gpio_init_struct.gpio_pins = IO_LED_ERROR;
  gpio_init(PT_LED_ERROR, &gpio_init_struct);
  
  LED_ERLED_DIS();
  LED_BAT1_DIS();
  LED_BAT2_DIS();
  LED_BAT3_DIS();
  LED_BAT4_DIS();
}

/*----------------------------------------------------------------------------
函数名称： Heartbeat_BAT1_Led
具体描述： 电量1心跳
----------------------------------------------------------------------------*/
void Heartbeat_BAT1_Led(void)
{
	uint8_t state_led = 0;
  state_led = gpio_output_data_bit_read(PT_LED_BAT1,IO_LED_BAT1);
  if(state_led)
  {
      gpio_bits_write(PT_LED_BAT1,IO_LED_BAT1,FALSE);
  }
  else
  {
      gpio_bits_write(PT_LED_BAT1,IO_LED_BAT1,TRUE);
  }
}
/*----------------------------------------------------------------------------
函数名称： Heartbeat_BAT2_Led
具体描述： 电量2心跳
----------------------------------------------------------------------------*/
void Heartbeat_BAT2_Led(void)
{
	uint8_t state_led = 0;
  state_led = gpio_output_data_bit_read(PT_LED_BAT2,IO_LED_BAT2);
  if(state_led)
  {
      gpio_bits_write(PT_LED_BAT2,IO_LED_BAT2,FALSE);
  }
  else
  {
      gpio_bits_write(PT_LED_BAT2,IO_LED_BAT2,TRUE);
  }
}

/*----------------------------------------------------------------------------
函数名称： Heartbeat_BAT3_Led
具体描述： 电量3心跳
----------------------------------------------------------------------------*/
void Heartbeat_BAT3_Led(void)
{
	uint8_t state_led = 0;
  state_led = gpio_output_data_bit_read(PT_LED_BAT3,IO_LED_BAT3);
  if(state_led)
  {
      gpio_bits_write(PT_LED_BAT3,IO_LED_BAT3,FALSE);
  }
  else
  {
      gpio_bits_write(PT_LED_BAT3,IO_LED_BAT3,TRUE);
  }
}
/*----------------------------------------------------------------------------
函数名称： Heartbeat_BAT4_Led
具体描述： 电量4心跳
----------------------------------------------------------------------------*/
void Heartbeat_BAT4_Led(void)
{
	uint8_t state_led = 0;
  state_led = gpio_output_data_bit_read(PT_LED_BAT4,IO_LED_BAT4);
  if(state_led)
  {
      gpio_bits_write(PT_LED_BAT4,IO_LED_BAT4,FALSE);
  }
  else
  {
      gpio_bits_write(PT_LED_BAT4,IO_LED_BAT4,TRUE);
  }
}
/*----------------------------------------------------------------------------
函数名称： Hal_Bat_Led_Display_Enable
具体描述： 电量显示LED使能
输入参数： u8LedNum  要显示的LED
           u8Enable  使能
----------------------------------------------------------------------------*/
void Hal_Bat_Led_Display_Enable(uint8_t u8LedNum,uint8_t u8Enable)
{
    if(u8LedNum == 1)
    {
        if(u8Enable)
            LED_BAT1_EN();
        else
            LED_BAT1_DIS();
    }
    else if(u8LedNum == 2)
    {
        if(u8Enable)
            LED_BAT2_EN();
        else
            LED_BAT2_DIS();
    }
    else if(u8LedNum == 3)
    {
        if(u8Enable)
            LED_BAT3_EN();
        else
            LED_BAT3_DIS();
    }
    else if(u8LedNum == 4)
    {
        if(u8Enable)
            LED_BAT4_EN();
        else
            LED_BAT4_DIS();
    }
    else
        return;
}
/*----------------------------------------------------------------------------
函数名称： Hal_Error_Led_Display_Enable
具体描述： 告警显示LED使能
输入参数： u8Enable  使能
----------------------------------------------------------------------------*/
void Hal_Error_Led_Display_Enable(uint8_t u8Enable)
{
  uint8_t state_led = 0;
  state_led = gpio_output_data_bit_read(PT_LED_ERROR,IO_LED_ERROR);
  if(u8Enable)
  {
    if(!state_led)
    {
      LED_ERLED_EN();
    }
  }
  else
  {
    if(state_led)
    {
      LED_ERLED_DIS();
    }
  } 
}
/*----------------------------------------------------------------------------
函数名称： Hal_Bat_Led_Heartbeat
具体描述： 电量显示LED闪
输入参数： u8LedNum  要闪烁的LED
----------------------------------------------------------------------------*/
void Hal_Bat_Led_Heartbeat(uint8_t u8LedNum)
{
    if(u8LedNum == 1)
        Heartbeat_BAT1_Led();
    else if(u8LedNum == 2)
        Heartbeat_BAT2_Led();
    else if(u8LedNum == 3)
        Heartbeat_BAT3_Led();
    else if(u8LedNum == 4)
        Heartbeat_BAT4_Led();
    else
        return;
}


