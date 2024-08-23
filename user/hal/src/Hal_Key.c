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

#include    "Hal_Key.h"
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
void Hal_Key_Init(void)
{
  gpio_init_type  gpio_init_struct;
  
  gpio_default_para_init(&gpio_init_struct);
  
  /*   ��������1   */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init_struct.gpio_pins = IO_MAGKEY;
  gpio_init(PT_MAGKEY, &gpio_init_struct);
  
  /*   ��������1   */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init_struct.gpio_pins = IO_MAGKEY2;
  gpio_init(PT_MAGKEY2, &gpio_init_struct);

  /*   ��������1   */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init_struct.gpio_pins = IO_LDR1KEY;
  gpio_init(PT_LDR1KEY, &gpio_init_struct);

  /*   ��������2   */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init_struct.gpio_pins = IO_LDR2KEY;
  gpio_init(PT_LDR2KEY, &gpio_init_struct);
  
  /*   �㸲����   */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_pins = IO_FALLDOWNKEY;
  gpio_init(PT_FALLDOWNKEY, &gpio_init_struct);  
  
  /*   ����SOS����   */
  gpio_init_struct.gpio_pins = IO_SOSKEY;
  gpio_init(PT_SOSKEY, &gpio_init_struct); 

 
}

/*----------------------------------------------------------------------------
�������ƣ� Hal_Get_SOSKey_State
���������� ��ȡ����SOS����״̬
��������� 1 ����   
           0 ����
----------------------------------------------------------------------------*/
uint8_t Hal_Get_SOSKey_State(void)
{
  if(gpio_input_data_bit_read(PT_SOSKEY,IO_SOSKEY))          //��������
      return 0;
  else
      return 1;
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Exit_SOS_Init
���������� ����SOS�����ⲿ�ж��߳�ʼ��
----------------------------------------------------------------------------*/
void Hal_Exit_SOS_Init(void)
{ 
  exint_init_type exint_init_struct;

  scfg_exint_line_config(EXINT_PORT_SOSKEY, EXINT_PIN_SOSKEY);

  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_select = EXINT_LINE_SOSKEY;
  exint_init_struct.line_polarity = EXINT_TRIGGER_FALLING_EDGE;
  exint_init(&exint_init_struct);
	exint_flag_clear(EXINT_LINE_SOSKEY);
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(EXINT_IRQn_SOSKEY, 1, 0);
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Exit_SOS_Deinit
���������� ����SOS�����ⲿ�ж���ʧ
----------------------------------------------------------------------------*/
void Hal_Exit_SOS_Deinit(void)
{ 
	gpio_init_type gpio_init_struct;
  
  exint_reset();
  nvic_irq_disable(EXINT_IRQn_SOSKEY);		//������������ͻ�����²���Ҫ�Ĺض�
  
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pins = IO_SOSKEY;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(PT_SOSKEY, &gpio_init_struct);
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Get_MagKey_State
���������� ��ȡ�Ÿ�Ӧ����״̬
��������� 1 �дŸ�Ӧ   ���� 
           0 �޴Ÿ�Ӧ	δ����
----------------------------------------------------------------------------*/
uint8_t Hal_Get_Mag1Key_State(void)
{
  if(gpio_input_data_bit_read(PT_MAGKEY,IO_MAGKEY))          //��������
      return 0;
  else
      return 1;
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Exit_MagKey_Init
���������� ��������1�ⲿ�ж��߳�ʼ��		//��Ҫ�˶��ж������Դ
----------------------------------------------------------------------------*/
void Hal_Exit_Mag1Key_Init(void)
{ 
  exint_init_type exint_init_struct;

  scfg_exint_line_config(EXINT_PORT_MAGKEY, EXINT_PIN_MAGKEY);

  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_select = EXINT_LINE_MAGKEY;
  exint_init_struct.line_polarity = EXINT_TRIGGER_FALLING_EDGE;
  exint_init(&exint_init_struct);
  exint_flag_clear(EXINT_LINE_MAGKEY);
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(EXINT_IRQn_MAGKEY, 1, 0);
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Exit_MagKey_Deinit
���������� ��������1�ⲿ�ж���ʧ��		//��Ҫ�˶��ж������Դ
----------------------------------------------------------------------------*/
void Hal_Exit_Mag1Key_Deinit(void)
{ 
	gpio_init_type gpio_init_struct;
  
  exint_reset();
  nvic_irq_disable(EXINT_IRQn_MAGKEY);
  
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pins = IO_MAGKEY;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(PT_MAGKEY, &gpio_init_struct);
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Get_MagKey2_State
���������� ��ȡ�Ÿ�Ӧ����2״̬
��������� 1 �дŸ�Ӧ   
           0 �޴Ÿ�Ӧ
----------------------------------------------------------------------------*/
uint8_t Hal_Get_Mag2Key_State(void)
{
  if(gpio_input_data_bit_read(PT_MAGKEY2,IO_MAGKEY2))          //��������
      return 0;
  else
      return 1;
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Exit_MagKey2_Init
���������� ��������2�ⲿ�ж��߳�ʼ��		//��Ҫ�˶��ж������Դ
----------------------------------------------------------------------------*/
void Hal_Exit_Mag2Key_Init(void)
{ 
  exint_init_type exint_init_struct;

  scfg_exint_line_config(EXINT_PORT_MAGKEY2, EXINT_PIN_MAGKEY2);

  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_select = EXINT_LINE_MAGKEY2;
  exint_init_struct.line_polarity = EXINT_TRIGGER_FALLING_EDGE;
  exint_init(&exint_init_struct);
  exint_flag_clear(EXINT_LINE_MAGKEY2);
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(EXINT_IRQn_MAGKEY2, 1, 0);
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Exit_MagKey2_Deinit
���������� ��������2�ⲿ�ж���ʧ��		//��Ҫ�˶��ж������Դ
----------------------------------------------------------------------------*/
void Hal_Exit_Mag2Key_Deinit(void)
{ 
	gpio_init_type gpio_init_struct;
  
  exint_reset();
  nvic_irq_disable(EXINT_IRQn_MAGKEY2);
  
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pins = IO_MAGKEY2;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(PT_MAGKEY2, &gpio_init_struct);
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Get_LDR1Key_State
���������� ��ȡ����1����״̬
��������� 0 ��ͨ����   
           1 δ��ͨδ����
----------------------------------------------------------------------------*/
uint8_t Hal_Get_LDR1Key_State(void)
{
  if(gpio_input_data_bit_read(PT_LDR1KEY,IO_LDR1KEY))          //��������
      return 0;
  else
      return 1;
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Exit_LDR1Key_Init
���������� ����1�����ⲿ�ж��߳�ʼ��		//��Ҫ�˶��ж������Դ
----------------------------------------------------------------------------*/
void Hal_Exit_LDR1Key_Init(void)
{ 
  exint_init_type exint_init_struct;

  scfg_exint_line_config(EXINT_PORT_LDR1KEY, EXINT_PIN_LDR1KEY);

  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_select = EXINT_LINE_LDR1KEY;
  exint_init_struct.line_polarity = EXINT_TRIGGER_FALLING_EDGE;
  exint_init(&exint_init_struct);
  exint_flag_clear(EXINT_LINE_LDR1KEY);
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(EXINT_IRQn_LDR1KEY, 1, 0);
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Exit_LDR1Key_Deinit
���������� ����1�����ⲿ�ж���ʧ��		//��Ҫ�˶��ж������Դ
----------------------------------------------------------------------------*/
void Hal_Exit_LDR1Key_Deinit(void)
{ 
	gpio_init_type gpio_init_struct;
  
  exint_reset();
  nvic_irq_disable(EXINT_IRQn_LDR1KEY);
  
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pins = IO_LDR1KEY;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(PT_MAGKEY, &gpio_init_struct);
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Get_LDR2Key_State
���������� ��ȡ����2����״̬
��������� 1 ��ͨ����   
           0 δ��ͨδ����
----------------------------------------------------------------------------*/
uint8_t Hal_Get_LDR2Key_State(void)
{
  if(gpio_input_data_bit_read(PT_LDR2KEY,IO_LDR2KEY))          //��������
      return 0;
  else
      return 1;
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Exit_LDR2Key_Init
���������� ����2�����ⲿ�ж��߳�ʼ��		//��Ҫ�˶��ж������Դ
----------------------------------------------------------------------------*/
void Hal_Exit_LDR2Key_Init(void)
{ 
  exint_init_type exint_init_struct;

  scfg_exint_line_config(EXINT_PORT_LDR2KEY, EXINT_PIN_LDR2KEY);

  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_select = EXINT_LINE_LDR2KEY;
  exint_init_struct.line_polarity = EXINT_TRIGGER_FALLING_EDGE;
  exint_init(&exint_init_struct);
  exint_flag_clear(EXINT_LINE_LDR2KEY);
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(EXINT_IRQn_LDR2KEY, 1, 0);		//���ͻEXINT_LINE_MAGKEY2
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Exit_LDR2Key_Deinit
���������� ����2�����ⲿ�ж���ʧ��		//��Ҫ�˶��ж������Դ
----------------------------------------------------------------------------*/
void Hal_Exit_LDR2Key_Deinit(void)
{ 
	gpio_init_type gpio_init_struct;
  
  exint_reset();
  nvic_irq_disable(EXINT_IRQn_LDR2KEY);
  
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pins = IO_LDR2KEY;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(PT_MAGKEY2, &gpio_init_struct);
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Get_FalldownKey_State
���������� ��ȡ����FalldownKey����״̬
��������� 0 δ��ͨ��δ�㸲  
           1 ��ͨ���㸲 
----------------------------------------------------------------------------*/
uint8_t Hal_Get_FalldownKey_State(void)
{
  if(gpio_input_data_bit_read(PT_FALLDOWNKEY,IO_FALLDOWNKEY))          //��������
      return 0;
  else
      return 1;
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Exit_FalldownKey_Init
���������� �㸲�����ⲿ�ж��߳�ʼ��		//��Ҫ�˶��ж������Դ
----------------------------------------------------------------------------*/
void Hal_Exit_FalldownKey_Init(void)
{ 
  exint_init_type exint_init_struct;

  scfg_exint_line_config(EXINT_PORT_FALLDOWNKEY, EXINT_PIN_FALLDOWNKEY);
	
  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_select = EXINT_LINE_FALLDOWNKEY;
  exint_init_struct.line_polarity = EXINT_TRIGGER_FALLING_EDGE;
  exint_init(&exint_init_struct);
	exint_flag_clear(EXINT_LINE_FALLDOWNKEY);
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(EXINT_IRQn_FALLDOWNKEY, 1, 0);
}
/*----------------------------------------------------------------------------
�������ƣ� Hal_Exit_FalldownKey_Deinit
���������� �㸲�����ⲿ�ж���ʧ��		//��Ҫ�˶��ж������Դ
----------------------------------------------------------------------------*/
void Hal_Exit_FalldownKey_Deinit(void)
{ 
	gpio_init_type gpio_init_struct;
  
  exint_reset();
  nvic_irq_disable(EXINT_IRQn_FALLDOWNKEY);
  
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pins = IO_FALLDOWNKEY;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(PT_FALLDOWNKEY, &gpio_init_struct);
}



void EXINT0_IRQHandler(void)
{
  if(exint_interrupt_flag_get(EXINT_LINE_SOSKEY) != RESET)
  {
    exint_flag_clear(EXINT_LINE_SOSKEY);
  }
  if(exint_interrupt_flag_get(EXINT_LINE_MAGKEY) != RESET)
  {
    exint_flag_clear(EXINT_LINE_MAGKEY);
  }

  
}
//û����
void EXINT1_IRQHandler(void)
{
  if(exint_interrupt_flag_get(EXINT_LINE_1) != RESET)
  {
    exint_flag_clear(EXINT_LINE_1);
  }
}
void EXINT2_IRQHandler(void)
{
  if(exint_interrupt_flag_get(EXINT_LINE_LDR1KEY) != RESET)
  {
    exint_flag_clear(EXINT_LINE_LDR1KEY);
  }
}

void EXINT9_5_IRQHandler(void)
{
  if(exint_interrupt_flag_get(EXINT_LINE_FALLDOWNKEY) != RESET)
  {
    exint_flag_clear(EXINT_LINE_FALLDOWNKEY);
  }
	
	
	
	
}

void EXINT15_10_IRQHandler(void)
{
  if(exint_interrupt_flag_get(EXINT_LINE_SOSKEY) != RESET)
  {
    exint_flag_clear(EXINT_LINE_SOSKEY);
  }
  if(exint_interrupt_flag_get(EXINT_LINE_LDR2KEY) != RESET)
  {
    exint_flag_clear(EXINT_LINE_LDR2KEY);
  }	
  if(exint_interrupt_flag_get(EXINT_LINE_MAGKEY2) != RESET)
  {
    exint_flag_clear(EXINT_LINE_MAGKEY2);
  }		
	
}

