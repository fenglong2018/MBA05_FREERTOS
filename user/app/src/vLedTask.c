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


/* led2 task function */
void key_task_function(void *pvParameters)
{
	Hal_Key_Init();
	Hal_Buz_Init();
	// BUZ_ON();
  while(1)
  {
//    at32_led_toggle(LED2);
//		DEBUG_PRINT("key task running...\r\n");

		if( Hal_Get_LDR1Key_State()==1)
		{
			BUZ_ON();
			DEBUG_PRINT("BUZ_ON\r\n");
		}
		else
		{
			BUZ_OFF();
			DEBUG_PRINT("BUZ_OFF\r\n");
		}
		if( Hal_Get_LDR2Key_State()==1)
		{
			BUZ_ON();
			DEBUG_PRINT("BUZ_ON\r\n");
		}
		else
		{
			BUZ_OFF();
			DEBUG_PRINT("BUZ_OFF\r\n");
		}		
    vTaskDelay(1000);
  }
}














