/*
 * Copyright (C) 2015 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

/**
 * @file
 * @date 01 Aug, 2015
 * @version 0.1.0
 *
 * @brief XMC1300 Boot kit blinky GPIO demo example
 *
 * The blinky example flashes the leds of the board with a periodic rate.
 * LED1 is connected to P0.6
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */


#include "xmc_gpio.h"
#include "core_cm0.h"
#include "probe_scope.h"
#include "probe_scope_cfg.h"
#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 500
uint16_t Count = 0, Count1 = 0;

#define LED1 P0_6
uint8_t __attribute__ ((section (".myDataSection"))) sum;
void __attribute__((section (".ram_code"))) SysTick_Handler(void)
{
	Count++;
	Count1+=2;
  static uint32_t ticks = 0;
  ticks++;
  if (ticks == TICKS_WAIT)
  {
    XMC_GPIO_ToggleOutput(LED1);
    ticks = 0;
  }
  ProbeScope_Sampling();
}


int main(void)
{
	ProbeScope_Init(10000);
	uint32_t __attribute__ ((unused)) DURATION_TIME;
	float __attribute__ ((unused)) result1;
  XMC_GPIO_CONFIG_t config;
  SysTick_Type __attribute__ ((unused)) systic_config;
  systic_config.CTRL = 0;
  systic_config.LOAD = 0xffffff;
  systic_config.CTRL = 0x5;
  systic_config.VAL = 0;
  //result1 = arm_sin_f32(0.5f);
  DURATION_TIME = SysTick->VAL; /* Get duration time */
  SysTick->CTRL = 0; /* Disable SysTick */




  config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;

  XMC_GPIO_Init(LED1, &config);

  config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;

    /* System timer configuration */
  //SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);
  SysTick_Config(SystemCoreClock/10000);
  sum = 0;
  while(1)
  {

	  /* Infinite loop */
  }
}
