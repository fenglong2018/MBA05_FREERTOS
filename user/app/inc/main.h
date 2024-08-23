
/********************************************************************** 
*  �ļ�����:  test.h
*  �ļ�����:  ������ʼ����LED��ʼ����������⡢LED����
*  ��ʷ��¼:  
*  ����ʱ��:  2024-05-9  
*  ������:    ������
*  �޸�ʱ��:	2024-8-8
*  �޸���:		�η���
*  ����: 	  
***********************************************************************/

#ifndef __MAIN_H_
#define __MAIN_H_



#define DEBUG_MYPRINT		1


#ifdef DEBUG_MYPRINT
    #define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINT(...) // ʲôҲ����
#endif



/********************************************************************** 
ͷ�ļ���������
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
�궨��
***********************************************************************/






//=====================================================================
//IO�ڶ���
//=====================================================================
/* ���ϵ�				            LED_ERROR:PD8  */












#include "stdio.h"
#include "at32f435_437.h"



#define LOG			1















#endif
