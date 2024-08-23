/********************************************************************** 
*  �ļ�����:vKeyTask.h
*  �ļ�����: 
*  ��ʷ��¼:  
*  ����ʱ��:  
*  ������:    
*  �޸�ʱ��:
*  �޸���:  
*  ����: 	  
***********************************************************************/
#ifndef _V_BUZZER_TASK_H_
#define _V_BUZZER_TASK_H_
/********************************************************************** 
ͷ�ļ���������
***********************************************************************/
#include "stdint.h"
#include 		"main.h"
/********************************************************************** 
�궨��
***********************************************************************/

#define BUZZER_TEST   1
#define KEY_STATUS_NUM 8

// /* �㸲����                  */
// #define FALLDOWNKEY_DOWN     0x01
// /* ����SOS����                */
// #define SOSKEY_DOWN          0x02
// /* ��������                   */
// #define MAG1KEY_DOWN 		     0x04   
// /* ��������2                    */
// #define MAG2KEY_DOWN         0x08
// /* ��������1                 */
// #define LDR1KEY_DOWN 	       0x10
// /* ��������2                 */
// #define LDR2KEY_DOWN         0x20
// /* ��������12                 */
// #define LDR12KEY_DOWN         0x30






/********************************************************************** 
�ṹ��ö�١�������Ƚṹ����
***********************************************************************/
typedef enum {
    FALLDOWNKEY_DOWN = 0x01,  // �㸲����
    SOSKEY_DOWN      = 0x02,  // ����SOS����
    MAG1KEY_DOWN     = 0x04,  // ��������1
    MAG2KEY_DOWN     = 0x08,  // ��������2
    LDR1KEY_DOWN     = 0x10,  // ��������1
    LDR2KEY_DOWN     = 0x20,  // ��������2
    LDR12KEY_DOWN    = 0x30,   // ��������12
		MAG12KEY_DOWN    = 0x0c,  // ��������12
} KeyStatus_t;





extern TaskHandle_t buzzer_handler;


void buzzer_task_function(void *pvParameters);
void buzzer_task_init(void);



#endif




