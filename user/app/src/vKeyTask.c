/************************************************************************
*  �ļ�����: demo.c
*  �ļ�����: 
*  ��ʷ��¼:  
*  ����ʱ��: 
*  ������:   
*  �޸�ʱ��:
*  �޸���:  
*  ����:
*************************************************************************/

/************************************************************************
ͷ�ļ���������
*************************************************************************/
#include    <stdint.h>
#include    <stdio.h>
#include 		"main.h"
#include    "Hal_Led.h"
#include "at32f435_437_board.h"
#include "at32f435_437_clock.h"
#include "FreeRTOS.h"
#include "task.h"
#include "vKeyTask.h"
#include "FreeRTOSConfig.h"
/************************************************************************
�궨��
*************************************************************************/




/************************************************************************
�ڲ��ṹ��ö�١�������Ƚṹ����
*************************************************************************/

/************************************************************************
�ڲ���̬��������

ȫ�ֱ�������

extern �ⲿ��������

*************************************************************************/

/************************************************************************
��̬��������

extern �ⲿ��������
*************************************************************************/

/************************************************************************
��������
*************************************************************************/


TaskHandle_t key_handler;





void key_task_init(void)
{
/* create led2 task */
  if(xTaskCreate((TaskFunction_t )key_task_function,
                 (const char*    )"LED2_task",
                 (uint16_t       )512,
                 (void*          )NULL,
                 (UBaseType_t    )2,
                 (TaskHandle_t*  )&key_handler) != pdPASS)
  {
    DEBUG_PRINT("key task could not be created as there was insufficient heap memory remaining.\r\n");
  }
  else
  {
    DEBUG_PRINT("key task was created successfully.\r\n");
  }
}


/* key task function */
/* ��ȡ������״̬ */


void key_task_function(void *pvParameters)
{
	uint32_t key_status = 0;	
	Hal_Key_Init();
  while(1)
  {
		key_status = 0;
//		DEBUG_PRINT("key task running...\r\n");
		if(Hal_Get_FalldownKey_State())
		{
			key_status |= 0x01<<0;
		}
		else
		{
			key_status &= 0xFE;
		}
		if(Hal_Get_SOSKey_State())
		{
			key_status |= 0x01<<1;
		}
		else
		{
			key_status &= 0xFD;
		}
		if(Hal_Get_Mag1Key_State())
		{
			key_status |= 0x01<<2;
		}
		else
		{
			key_status &= 0xFB;
		}
		if(Hal_Get_Mag2Key_State())
		{
			key_status |= 0x01<<3;
		}
		else
		{
			key_status &= 0xF7;
		}
		if(Hal_Get_LDR1Key_State())
		{
			key_status |= 0x01<<4;
		}
		else
		{
			key_status &= 0xEF;
		}
		if(Hal_Get_LDR2Key_State())
		{
			key_status |= 0x01<<5;
		}
		else
		{
			key_status &= 0xDF;
		}	
		xTaskNotify(buzzer_handler, key_status, eSetValueWithOverwrite);
    vTaskDelay(1000);
  }
}














