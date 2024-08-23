/*************************************************************************
*  	�ļ�����:  	Hal_KeyLed.c
*  	�ļ�����:  	������ʼ����LED��ʼ����������⡢LED����
*  	��ʷ��¼:
*  	����ʱ��:  	2024-05-09
*  	������:  	������
*  	�޸�ʱ��:
*	�޸���:
*   ����:
*************************************************************************/

/*************************************************************************
ͷ�ļ���������
*************************************************************************/
#include    "at32f435_437_gpio.h"
#include    "at32f435_437_scfg.h"

#include    "Hal_Led.h"
/************************************************************************
�궨��
*************************************************************************/

/*************************************************************************
�ڲ��ṹ��ö�١�������Ƚṹ����
*************************************************************************/

/*************************************************************************
�ڲ���̬��������

ȫ�ֱ�������

extern �ⲿ��������

*************************************************************************/

/*************************************************************************
��̬��������

extern �ⲿ��������
*************************************************************************/

/*************************************************************************
��������
*************************************************************************/
/*----------------------------------------------------------------------------
�������ƣ� Hal_Key_Init
���������� ������ʼ��
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
�������ƣ� Hal_Led_Init
���������� LED��ʼ��
----------------------------------------------------------------------------*/
void Hal_Led_Init(void)
{
  gpio_init_type  gpio_init_struct;
     
  gpio_default_para_init(&gpio_init_struct);
  /*   ������1   */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_init_struct.gpio_pins = IO_LED_BAT1;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(PT_LED_BAT1, &gpio_init_struct);
  /*   ������2   */
  gpio_init_struct.gpio_pins = IO_LED_BAT2;
  gpio_init(PT_LED_BAT2, &gpio_init_struct);
  /*   ������3  */
  gpio_init_struct.gpio_pins = IO_LED_BAT3;
  gpio_init(PT_LED_BAT3, &gpio_init_struct);
  /*   ������4   */
  gpio_init_struct.gpio_pins = IO_LED_BAT4;
  gpio_init(PT_LED_BAT4, &gpio_init_struct);
  
  /*   ���ϵ�   */
  gpio_init_struct.gpio_pins = IO_LED_ERROR;
  gpio_init(PT_LED_ERROR, &gpio_init_struct);
  
  LED_ERLED_DIS();
  LED_BAT1_DIS();
  LED_BAT2_DIS();
  LED_BAT3_DIS();
  LED_BAT4_DIS();
}

/*----------------------------------------------------------------------------
�������ƣ� Heartbeat_BAT1_Led
���������� ����1����
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
�������ƣ� Heartbeat_BAT2_Led
���������� ����2����
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
�������ƣ� Heartbeat_BAT3_Led
���������� ����3����
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
�������ƣ� Heartbeat_BAT4_Led
���������� ����4����
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
�������ƣ� Hal_Bat_Led_Display_Enable
���������� ������ʾLEDʹ��
��������� u8LedNum  Ҫ��ʾ��LED
           u8Enable  ʹ��
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
�������ƣ� Hal_Error_Led_Display_Enable
���������� �澯��ʾLEDʹ��
��������� u8Enable  ʹ��
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
�������ƣ� Hal_Bat_Led_Heartbeat
���������� ������ʾLED��
��������� u8LedNum  Ҫ��˸��LED
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


