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
#ifndef _V_KEY_TASK_H_
#define _V_KEY_TASK_H_
/********************************************************************** 
头文件引用声明
***********************************************************************/
#include "stdint.h"
/********************************************************************** 
宏定义
***********************************************************************/
#define KEY_TEST   1			//光敏开关测试

// /* 倾覆开关                  */
// #define PT_FALLDOWNKEY     0x01
// /* 侧面SOS按键                */
// #define PT_SOSKEY          0x02
// /* 磁吸开关                   */
// #define MAG1KEY_DOWN       0x04   
// /* 磁吸开关2                    */
// #define PT_MAG2KEY         0x08
// /* 光敏开关1                 */
// #define PT_LDR1KEY 	       0x10
// /* 光敏开关2                 */
// #define PT_LDR2KEY         0x20
/********************************************************************** 
结构、枚举、公用体等结构定义
***********************************************************************/









void key_task_init(void);
void key_task_function(void *pvParameters);





#endif




