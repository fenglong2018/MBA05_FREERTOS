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

#include    "Hal_Key.h"
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
void Hal_Key_Init(void)
{
  gpio_init_type  gpio_init_struct;
  
  gpio_default_para_init(&gpio_init_struct);
  
  /*   磁吸按键1   */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init_struct.gpio_pins = IO_MAGKEY;
  gpio_init(PT_MAGKEY, &gpio_init_struct);
  
  /*   磁吸按键1   */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init_struct.gpio_pins = IO_MAGKEY2;
  gpio_init(PT_MAGKEY2, &gpio_init_struct);

  /*   光敏开关1   */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init_struct.gpio_pins = IO_LDR1KEY;
  gpio_init(PT_LDR1KEY, &gpio_init_struct);

  /*   光敏开关2   */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init_struct.gpio_pins = IO_LDR2KEY;
  gpio_init(PT_LDR2KEY, &gpio_init_struct);
  
  /*   倾覆开关   */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
	gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_pins = IO_FALLDOWNKEY;
  gpio_init(PT_FALLDOWNKEY, &gpio_init_struct);  
  
  /*   侧面SOS开关   */
  gpio_init_struct.gpio_pins = IO_SOSKEY;
  gpio_init(PT_SOSKEY, &gpio_init_struct); 

 
}

/*----------------------------------------------------------------------------
函数名称： Hal_Get_SOSKey_State
具体描述： 获取侧面SOS开关状态
输出参数： 1 按下   
           0 弹开
----------------------------------------------------------------------------*/
uint8_t Hal_Get_SOSKey_State(void)
{
  if(gpio_input_data_bit_read(PT_SOSKEY,IO_SOSKEY))          //按键输入
      return 0;
  else
      return 1;
}
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_SOS_Init
具体描述： 侧面SOS开关外部中断线初始化
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
函数名称： Hal_Exit_SOS_Deinit
具体描述： 侧面SOS开关外部中断线失
----------------------------------------------------------------------------*/
void Hal_Exit_SOS_Deinit(void)
{ 
	gpio_init_type gpio_init_struct;
  
  exint_reset();
  nvic_irq_disable(EXINT_IRQn_SOSKEY);		//可能与其他冲突，导致不必要的关断
  
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type  = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pins = IO_SOSKEY;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(PT_SOSKEY, &gpio_init_struct);
}
/*----------------------------------------------------------------------------
函数名称： Hal_Get_MagKey_State
具体描述： 获取磁感应开关状态
输出参数： 1 有磁感应   吸合 
           0 无磁感应	未吸合
----------------------------------------------------------------------------*/
uint8_t Hal_Get_Mag1Key_State(void)
{
  if(gpio_input_data_bit_read(PT_MAGKEY,IO_MAGKEY))          //按键输入
      return 0;
  else
      return 1;
}
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_MagKey_Init
具体描述： 磁吸开关1外部中断线初始化		//需要核对中断相关资源
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
函数名称： Hal_Exit_MagKey_Deinit
具体描述： 磁吸开关1外部中断线失能		//需要核对中断相关资源
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
函数名称： Hal_Get_MagKey2_State
具体描述： 获取磁感应开关2状态
输出参数： 1 有磁感应   
           0 无磁感应
----------------------------------------------------------------------------*/
uint8_t Hal_Get_Mag2Key_State(void)
{
  if(gpio_input_data_bit_read(PT_MAGKEY2,IO_MAGKEY2))          //按键输入
      return 0;
  else
      return 1;
}
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_MagKey2_Init
具体描述： 磁吸开关2外部中断线初始化		//需要核对中断相关资源
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
函数名称： Hal_Exit_MagKey2_Deinit
具体描述： 磁吸开关2外部中断线失能		//需要核对中断相关资源
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
函数名称： Hal_Get_LDR1Key_State
具体描述： 获取光敏1开关状态
输出参数： 0 导通开盖   
           1 未导通未开盖
----------------------------------------------------------------------------*/
uint8_t Hal_Get_LDR1Key_State(void)
{
  if(gpio_input_data_bit_read(PT_LDR1KEY,IO_LDR1KEY))          //按键输入
      return 0;
  else
      return 1;
}
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_LDR1Key_Init
具体描述： 光敏1开关外部中断线初始化		//需要核对中断相关资源
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
函数名称： Hal_Exit_LDR1Key_Deinit
具体描述： 光敏1开关外部中断线失能		//需要核对中断相关资源
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
函数名称： Hal_Get_LDR2Key_State
具体描述： 获取光敏2开关状态
输出参数： 1 导通开盖   
           0 未导通未开盖
----------------------------------------------------------------------------*/
uint8_t Hal_Get_LDR2Key_State(void)
{
  if(gpio_input_data_bit_read(PT_LDR2KEY,IO_LDR2KEY))          //按键输入
      return 0;
  else
      return 1;
}
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_LDR2Key_Init
具体描述： 光敏2开关外部中断线初始化		//需要核对中断相关资源
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
  nvic_irq_enable(EXINT_IRQn_LDR2KEY, 1, 0);		//与冲突EXINT_LINE_MAGKEY2
}
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_LDR2Key_Deinit
具体描述： 光敏2开关外部中断线失能		//需要核对中断相关资源
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
函数名称： Hal_Get_FalldownKey_State
具体描述： 获取侧面FalldownKey开关状态
输出参数： 0 未导通，未倾覆  
           1 导通，倾覆 
----------------------------------------------------------------------------*/
uint8_t Hal_Get_FalldownKey_State(void)
{
  if(gpio_input_data_bit_read(PT_FALLDOWNKEY,IO_FALLDOWNKEY))          //按键输入
      return 0;
  else
      return 1;
}
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_FalldownKey_Init
具体描述： 倾覆开关外部中断线初始化		//需要核对中断相关资源
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
函数名称： Hal_Exit_FalldownKey_Deinit
具体描述： 倾覆开关外部中断线失能		//需要核对中断相关资源
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
//没有配
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

