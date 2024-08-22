/**
  **************************************************************************
  * @file     at32f435_437_clock.c
  * @brief    system clock config program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* includes ------------------------------------------------------------------*/
#include "at32f435_437_clock.h"

/**
  * @brief  system clock config program
  * @note   the system clock is configured as follow:
  *         system clock (sclk)   = (hext * pll_ns)/(pll_ms * pll_fr)
  *         system clock source   = pll (hext)
  *         - hext                = HEXT_VALUE
  *         - sclk                = 288000000
  *         - ahbdiv              = 1
  *         - ahbclk              = 288000000
  *         - apb2div             = 2
  *         - apb2clk             = 144000000
  *         - apb1div             = 2
  *         - apb1clk             = 144000000
  *         - pll_ns              = 144
  *         - pll_ms              = 1
  *         - pll_fr              = 4
  * @param  none
  * @retval none
  */
void system_clock_config(void)
{
  	
	/* ʱ������ */
  crm_reset();

  /* ����PWC��Χʱ�� */
  crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);

  /* ���õ�ѹ */
  pwc_ldo_output_voltage_set(PWC_LDO_OUTPUT_1V3);

  /* ����FLASHʱ�ӷ�Ƶ */
  flash_clock_divider_set(FLASH_CLOCK_DIV_3);

	/* ʹ���ⲿʱ�� */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

  /* �ȴ��ⲿʱ�Ӿ��� */
  while(crm_hext_stable_wait() == ERROR)
  {
  }

  /* ����PLLʱ����Դ ��*/
  crm_pll_config(CRM_PLL_SOURCE_HEXT, 96, 2, CRM_PLL_FR_8);

  /* ʹ��PLL */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

  /* �ȴ�PLL���� */
  while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
  {
  }

  /* ����AHB��Ƶ */
  crm_ahb_div_set(CRM_AHB_DIV_1);

  /* ����APB2ʱ�ӣ�/1=144MHZ  */
  crm_apb2_div_set(CRM_APB2_DIV_1);

  /* ����APB1ʱ�ӣ�/1=144MHZ  */
  crm_apb1_div_set(CRM_APB1_DIV_1);

  /* ʹ���Զ�����ģʽ */
  crm_auto_step_mode_enable(TRUE);

  /* ѡ��PLLΪϵͳʱ�� */
  crm_sysclk_switch(CRM_SCLK_PLL);

  /* �ȴ�PLLʱ��Ϊϵͳʱ�� */
  while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL)
  {
  }

  /* ʧ���Զ�����ģʽ */
  crm_auto_step_mode_enable(FALSE);

  /* ����ϵͳʱ��ȫ�ֱ��� */
  system_core_clock_update();
	
//  /* ����GPIOAʱ�� */
//  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK,TRUE);
//  /* ����GPIOBʱ�� */
//  crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK,TRUE);
//  /* ����GPIOCʱ�� */
//  crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK,TRUE);
//  /* ����GPIOHʱ�� */
//  crm_periph_clock_enable(CRM_GPIOH_PERIPH_CLOCK,TRUE);
//  /* ����GPIOEʱ�� */
//  crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK,TRUE);  
//	
//  /* ����GPIODʱ�� */
//  crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK,TRUE);  
//  crm_periph_clock_enable(CRM_SCFG_PERIPH_CLOCK, TRUE);
  
//  systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV);
//  SysTick_Config(SystemCoreClock/1000); 

}


/**
  * @brief  config periph clock
  * @param  none
  * @retval none
  */
void wk_periph_clock_config(void)
{
  /* enable gpioa periph clock */
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

  /* enable gpiob periph clock */
  crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

  /* enable gpioh periph clock */
  crm_periph_clock_enable(CRM_GPIOH_PERIPH_CLOCK, TRUE);
}

/**
  * @brief  nvic config
  * @param  none
  * @retval none
  */
void wk_nvic_config(void)
{
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);

  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));
}








