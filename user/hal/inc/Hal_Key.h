/********************************************************************** 
*  文件名称:  Hal_KeyLed.h
*  文件描述:  按键初始化、LED初始化、按键检测、LED驱动
*  历史记录:  
*  创建时间:  2024-05-9  
*  创建人:    江昌钤
*  修改时间:	2024-8-8
*  修改人:		何凤龙
*  描述: 	  
***********************************************************************/

#ifndef _HAL_KEY_H_
#define _HAL_KEY_H_

/********************************************************************** 
头文件引用声明
***********************************************************************/
#include    <stdint.h>
/********************************************************************** 
宏定义
***********************************************************************/
//=====================================================================
//IO口定义
//=====================================================================


/* 磁吸开关                 MAGKEY:PD0    */
#define PT_MAGKEY           GPIOD
#define IO_MAGKEY           GPIO_PINS_0
#define EXINT_PORT_MAGKEY		SCFG_PORT_SOURCE_GPIOD
#define EXINT_PIN_MAGKEY		SCFG_PINS_SOURCE0
#define EXINT_LINE_MAGKEY		EXINT_LINE_0
#define EXINT_IRQn_MAGKEY       EXINT0_IRQn


/* 磁吸开关2                 MAGKEY:PC15    */
#define PT_MAGKEY2          GPIOC
#define IO_MAGKEY2          GPIO_PINS_15
#define EXINT_PORT_MAGKEY2	SCFG_PORT_SOURCE_GPIOC
#define EXINT_PIN_MAGKEY2	SCFG_PINS_SOURCE15
#define EXINT_LINE_MAGKEY2	EXINT_LINE_15	
#define EXINT_IRQn_MAGKEY2  EXINT15_10_IRQn

/* 光敏开关1                 MAGKEY:PD2    */
#define PT_LDR1KEY 	        GPIOD
#define IO_LDR1KEY          GPIO_PINS_2
#define EXINT_PORT_LDR1KEY	SCFG_PORT_SOURCE_GPIOD
#define EXINT_PIN_LDR1KEY		SCFG_PINS_SOURCE2
#define EXINT_LINE_LDR1KEY	EXINT_LINE_2
#define EXINT_IRQn_LDR1KEY  EXINT2_IRQn

/* 光敏开关2                 MAGKEY:PB15    */
#define PT_LDR2KEY          GPIOB
#define IO_LDR2KEY          GPIO_PINS_15
#define EXINT_PORT_LDR2KEY	SCFG_PORT_SOURCE_GPIOB
#define EXINT_PIN_LDR2KEY	SCFG_PINS_SOURCE15
#define EXINT_LINE_LDR2KEY	EXINT_LINE_15		//与冲突EXINT_LINE_MAGKEY2
#define EXINT_IRQn_LDR2KEY  EXINT15_10_IRQn

/* 倾覆开关                 MAGKEY:PA5    */
#define PT_FALLDOWNKEY          GPIOA
#define IO_FALLDOWNKEY          GPIO_PINS_5
#define EXINT_PORT_FALLDOWNKEY	SCFG_PORT_SOURCE_GPIOA
#define EXINT_PIN_FALLDOWNKEY	SCFG_PINS_SOURCE5
#define EXINT_LINE_FALLDOWNKEY 	EXINT_LINE_5
#define EXINT_IRQn_FALLDOWNKEY   EXINT9_5_IRQn

/* 侧面SOS按键                 SIDEKEY:PE14    */
#define PT_SOSKEY          GPIOE
#define IO_SOSKEY          GPIO_PINS_14
#define EXINT_PORT_SOSKEY		SCFG_PORT_SOURCE_GPIOE
#define EXINT_PIN_SOSKEY		SCFG_PINS_SOURCE14
#define EXINT_LINE_SOSKEY 	EXINT_LINE_14
#define EXINT_IRQn_SOSKEY   EXINT15_10_IRQn


/********************************************************************** 
结构、枚举、公用体等结构定义
***********************************************************************/


/********************************************************************** 
源文件定义变量声明

extern 外部变量声明
***********************************************************************/

/********************************************************************** 
源文件函数声明

extern 外部函数声明
***********************************************************************/
/*----------------------------------------------------------------------------
函数名称： Hal_Key_Init
具体描述： 按键初始化
----------------------------------------------------------------------------*/
void Hal_Key_Init(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_SOS_Init
具体描述： 侧面开关外部中断线初始化
----------------------------------------------------------------------------*/
void Hal_Exit_SOS_Init(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_SOS_Deinit
具体描述： 侧面开关外部中断线失能
----------------------------------------------------------------------------*/
void Hal_Exit_SOS_Deinit(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Get_MagKey_State
具体描述： 获取磁感应开关状态
输出参数： 1 有磁感应   
           0 无磁感应
----------------------------------------------------------------------------*/
uint8_t Hal_Get_Mag1Key_State(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Get_MagKey_State
具体描述： 获取磁感应开关状态
输出参数： 1 有磁感应   
           0 无磁感应
----------------------------------------------------------------------------*/
uint8_t Hal_Get_Mag2Key_State(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_MagKey_Init
具体描述： 磁吸开关1外部中断线初始化
----------------------------------------------------------------------------*/
void Hal_Exit_Mag1Key_Init(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_MagKey_Deinit
具体描述： 磁吸开关1外部中断线失能		//需要核对中断相关资源
----------------------------------------------------------------------------*/
void Hal_Exit_Mag1Key_Deinit(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_MagKey2_Init
具体描述： 磁吸开关2外部中断线初始化		//需要核对中断相关资源
----------------------------------------------------------------------------*/
void Hal_Exit_Mag2Key_Init(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_MagKey2_Deinit
具体描述： 磁吸开关2外部中断线失能		//需要核对中断相关资源
----------------------------------------------------------------------------*/
void Hal_Exit_Mag2Key_Deinit(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_LDR1Key_Init
具体描述： 光敏1开关外部中断线初始化		//需要核对中断相关资源
----------------------------------------------------------------------------*/
void Hal_Exit_LDR1Key_Init(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_LDR1Key_Deinit
具体描述： 光敏1开关外部中断线失能		//需要核对中断相关资源
----------------------------------------------------------------------------*/
void Hal_Exit_LDR1Key_Deinit(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_LDR2Key_Init
具体描述： 光敏2开关外部中断线初始化		//需要核对中断相关资源
----------------------------------------------------------------------------*/
void Hal_Exit_LDR2Key_Init(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_LDR2Key_Deinit
具体描述： 光敏2开关外部中断线失能		//需要核对中断相关资源
----------------------------------------------------------------------------*/
void Hal_Exit_LDR2Key_Deinit(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_FalldownKey_Init
具体描述： 倾覆开关外部中断线初始化		//需要核对中断相关资源
----------------------------------------------------------------------------*/
void Hal_Exit_FalldownKey_Init(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Exit_FalldownKey_Deinit
具体描述： 倾覆开关外部中断线失能		//需要核对中断相关资源
----------------------------------------------------------------------------*/
void Hal_Exit_FalldownKey_Deinit(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Get_SOSKey_State
具体描述： 获取侧面开关状态
输出参数： 1 按下   
           0 弹开
----------------------------------------------------------------------------*/
uint8_t Hal_Get_SOSKey_State(void);

/*----------------------------------------------------------------------------
函数名称： Hal_Get_LDR1Key_State
具体描述： 告警显示LED使能
输入参数： u8Enable  使能
----------------------------------------------------------------------------*/
uint8_t Hal_Get_LDR1Key_State(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Get_LDR2Key_State
具体描述： 告警显示LED使能
输入参数： u8Enable  使能
----------------------------------------------------------------------------*/
uint8_t Hal_Get_LDR2Key_State(void);
/*----------------------------------------------------------------------------
函数名称： Hal_Get_FalldownKey_State
具体描述： 获取倾覆开关状态
输出参数： 1 按下   
           0 弹开
----------------------------------------------------------------------------*/
uint8_t Hal_Get_FalldownKey_State(void);
#endif




