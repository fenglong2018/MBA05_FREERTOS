
/********************************************************************** 
*  文件名称:  test.h
*  文件描述:  按键初始化、LED初始化、按键检测、LED驱动
*  历史记录:  
*  创建时间:  2024-05-9  
*  创建人:    江昌钤
*  修改时间:	2024-8-8
*  修改人:		何凤龙
*  描述: 	  
***********************************************************************/

#ifndef __MAIN_H_
#define __MAIN_H_



#define DEBUG_MYPRINT		1


#ifdef DEBUG_MYPRINT
    #define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...) // 什么也不做
#endif



/********************************************************************** 
头文件引用声明
***********************************************************************/
#include    <stdint.h>
#include 		"test.h"

#include "FreeRTOS.h"
/* Application specific configuration options. */
#include "FreeRTOSConfig.h"
#include "task.h"

#include "at32f435_437_board.h"
#include "at32f435_437_clock.h"
#include "vKeyTask.h"
#include    "Hal_Key.h"
#include    "Hal_Buzzer.h"
#include    "Hal_Key.h"
#include    "Hal_Led.h"
#include    "vBuzTask.h"

/********************************************************************** 
宏定义
***********************************************************************/






//=====================================================================
//IO口定义
//=====================================================================
/* 故障灯				            LED_ERROR:PD8  */












#include "stdio.h"
#include "at32f435_437.h"



#define LOG			1















#endif
