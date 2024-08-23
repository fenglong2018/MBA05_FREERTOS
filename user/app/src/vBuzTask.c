/************************************************************************
*  文件名称: demo.c
*  文件描述: 
*  历史记录:  
*  创建时间: 
*  创建人:   
*  修改时间:
*  修改人:  
*  描述:
*************************************************************************/

/************************************************************************
头文件引用声明
*************************************************************************/
#include    <stdint.h>
#include    <stdio.h>
#include 		"main.h"
#include    "vBuzTask.h"
#include "FreeRTOSConfig.h"
/************************************************************************
宏定义
*************************************************************************/




/************************************************************************
内部结构、枚举、公用体等结构声明
*************************************************************************/

/************************************************************************
内部静态变量定义

全局变量定义

extern 外部变量声明

*************************************************************************/

/************************************************************************
静态函数声明

extern 外部函数声明
*************************************************************************/

/************************************************************************
函数定义
*************************************************************************/


TaskHandle_t buzzer_handler;





void buzzer_task_init(void)
{
/* create led2 task */
  if(xTaskCreate((TaskFunction_t )buzzer_task_function,
                 (const char*    )"BUZZER_task",
                 (uint16_t       )512,
                 (void*          )NULL,
                 (UBaseType_t    )2,
                 (TaskHandle_t*  )&buzzer_handler) != pdPASS)
  {
    DEBUG_PRINT("buzzer task could not be created as there was insufficient heap memory remaining.\r\n");
  }
  else
  {
    DEBUG_PRINT("buzzer task was created successfully.\r\n");
  }
}


/* led2 task function */
void buzzer_task_function(void *pvParameters)
{
	uint32_t ulNotificationKeyValue;
	Hal_Buz_Init();
  while(1)
  {
		xTaskNotifyWait(0, 0xff, &ulNotificationKeyValue, 1000);

		if(ulNotificationKeyValue)
		{
			if(FALLDOWNKEY_DOWN & ulNotificationKeyValue)
			{
				DEBUG_PRINT("FALLDOWNKEY_DOWN\r\n");
			}
			if(SOSKEY_DOWN & ulNotificationKeyValue)
			{
				DEBUG_PRINT("SOSKEY_DOWN\r\n");
			}	
			if(LDR12KEY_DOWN & ulNotificationKeyValue)
			{
				DEBUG_PRINT("LDR12KEY_DOWN\r\n");
//				BUZ_ON();
			}
			if(MAG12KEY_DOWN & ulNotificationKeyValue)
			{
				DEBUG_PRINT("MAG12KEY_DOWN\r\n");
//				BUZ_ON();
			}
			if(MAG1KEY_DOWN & ulNotificationKeyValue)
			{
				DEBUG_PRINT("MAG1KEY_DOWN\r\n");

			}
			if(MAG2KEY_DOWN & ulNotificationKeyValue)
			{
				DEBUG_PRINT("MAG2KEY_DOWN\r\n");

			}
			if(LDR1KEY_DOWN & ulNotificationKeyValue)
			{
				DEBUG_PRINT("LDR1KEY_DOWN\r\n");
			}
			if(LDR2KEY_DOWN & ulNotificationKeyValue)
			{
				DEBUG_PRINT("LDR2KEY_DOWN\r\n");
			}
		}
		else
		{
			DEBUG_PRINT("NO_KEY_DOWN\r\n");
			BUZ_OFF();
		}
		if( (MAG12KEY_DOWN & ulNotificationKeyValue)==0 && (LDR12KEY_DOWN & ulNotificationKeyValue)==0)
		{
			BUZ_OFF();
		}

  }
}














