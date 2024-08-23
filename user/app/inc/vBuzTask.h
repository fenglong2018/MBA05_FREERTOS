/********************************************************************** 
*  文件名称:vKeyTask.h
*  文件描述: 
*  历史记录:  
*  创建时间:  
*  创建人:    
*  修改时间:
*  修改人:  
*  描述: 	  
***********************************************************************/
#ifndef _V_BUZZER_TASK_H_
#define _V_BUZZER_TASK_H_
/********************************************************************** 
头文件引用声明
***********************************************************************/
#include "stdint.h"
#include 		"main.h"
/********************************************************************** 
宏定义
***********************************************************************/

#define BUZZER_TEST   1
#define KEY_STATUS_NUM 8

// /* 倾覆开关                  */
// #define FALLDOWNKEY_DOWN     0x01
// /* 侧面SOS按键                */
// #define SOSKEY_DOWN          0x02
// /* 磁吸开关                   */
// #define MAG1KEY_DOWN 		     0x04   
// /* 磁吸开关2                    */
// #define MAG2KEY_DOWN         0x08
// /* 光敏开关1                 */
// #define LDR1KEY_DOWN 	       0x10
// /* 光敏开关2                 */
// #define LDR2KEY_DOWN         0x20
// /* 光敏开关12                 */
// #define LDR12KEY_DOWN         0x30






/********************************************************************** 
结构、枚举、公用体等结构定义
***********************************************************************/
typedef enum {
    FALLDOWNKEY_DOWN = 0x01,  // 倾覆开关
    SOSKEY_DOWN      = 0x02,  // 侧面SOS按键
    MAG1KEY_DOWN     = 0x04,  // 磁吸开关1
    MAG2KEY_DOWN     = 0x08,  // 磁吸开关2
    LDR1KEY_DOWN     = 0x10,  // 光敏开关1
    LDR2KEY_DOWN     = 0x20,  // 光敏开关2
    LDR12KEY_DOWN    = 0x30,   // 光敏开关12
		MAG12KEY_DOWN    = 0x0c,  // 磁吸开关12
} KeyStatus_t;





extern TaskHandle_t buzzer_handler;


void buzzer_task_function(void *pvParameters);
void buzzer_task_init(void);



#endif




