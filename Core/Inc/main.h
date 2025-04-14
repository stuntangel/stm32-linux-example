/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

#define LED_PORT GPIOC
#define LED_PIN_0  GPIO_PIN_0
#define LED_PIN_1  GPIO_PIN_1
#define LED_PIN_2  GPIO_PIN_2
#define LED_PIN_3  GPIO_PIN_3

typedef unsigned char Byte_t;
typedef int32_t var_type;

void SystemClock_Config(void);
var_type TestFunction(var_type num);
void LedCycle(void);
void InitializePeriphrials(void);

void Error_Handler(void);

/* USER CODE BEGIN EFP */
	
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
