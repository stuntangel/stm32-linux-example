/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <math.h>

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
	var_type main_var;
	
  HAL_Init();
 
  SystemClock_Config();

	InitializePeriphrials(); // initializes GPIO ports
	
	LedCycle(); // cycles through counting to 15 in binary on 4 LEDs 3 times
	
	while(1) {
		GPIOC->BSRR = (GPIO_PIN_0);            // turn on PC0
		main_var = TestFunction(15);           // call test function
		GPIOC->BRR = (GPIO_PIN_0);             // turn on PC0
		main_var++;														 // ensures main_var does not be seen as unused by compiler
	}
	return 0;
}

var_type TestFunction(var_type num) {
	var_type test_var;  				// local variable
 
  GPIOC->BSRR = (GPIO_PIN_1);             // turn on PC1
  
	test_var = num+1;												// dummmy test instruction
	
	GPIOC->BRR = (GPIO_PIN_1);              // turn off PC1
  
  return test_var;
}

void LedCycle(void) {
	for (Byte_t loopsCounted = 0; loopsCounted <= 3; loopsCounted++) { // loops 3 times
		const uint32_t countTo = 15; // To binary count through 4 LEDs, 16 states are needed (16-1=15)
		for (uint32_t count = 0; count <= countTo; count++) {
			/*
				counts in binary using 4 LEDs
				cycle back to 0 after reaching maximum value to count to
				count up until maximum value is reached
			*/
			// Alternative Method to turn on and off the LEDs:
			LED_PORT->BRR = (LED_PIN_0 | LED_PIN_1 | LED_PIN_2 | LED_PIN_3); // reset all LEDs to off
			if(count & 0x1) LED_PORT->BSRR = (LED_PIN_0); // if first bit of count on, turn on first LED
			if(count & 0x2) LED_PORT->BSRR = (LED_PIN_1); // if second bit of count on, turn on second LED
			if(count & 0x4) LED_PORT->BSRR = (LED_PIN_2); // if third bit of count on, turn on third LED
			if(count & 0x8) LED_PORT->BSRR = (LED_PIN_3); // if fourth bit of count on, turn on fourth LED
			//LED_PORT->BSRR = ((~count >> 4) | count); // resets LEDs where bits are a 0 and turns off those with 1s
			for(long int i =0; i < 40000; i++) { // count to large number to waste time to act as delay
				; // nop
				/*
					0xFFFFFFFF is maximum value for an unsigned long int
					acts as a large value to count to, to spend time on execution cycles
					such that a human can see the led light up
					1200000 is a good value for humans to see as the clock is at 80MHz, so for loop approx 0.2 secs
				*/
			}
		}
	}
}

void InitializePeriphrials(void) {
	RCC->AHB2ENR   |=  (RCC_AHB2ENR_GPIOCEN);
  GPIOC->MODER   &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1 | GPIO_MODER_MODE2 | GPIO_MODER_MODE3);
  GPIOC->MODER   |=  (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0 | GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0);
  GPIOC->OTYPER  &= ~(GPIO_OTYPER_OT0 | GPIO_OTYPER_OT1 | GPIO_OTYPER_OT2 | GPIO_OTYPER_OT3);
  GPIOC->PUPDR   &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1 | GPIO_PUPDR_PUPD2 | GPIO_PUPDR_PUPD3);
  GPIOC->OSPEEDR |=  ((3 << GPIO_OSPEEDR_OSPEED0_Pos) |
                      (3 << GPIO_OSPEEDR_OSPEED1_Pos) |
											(3 << GPIO_OSPEEDR_OSPEED2_Pos) |
											(3 << GPIO_OSPEEDR_OSPEED3_Pos));
  GPIOC->BRR = (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); // preset PC0, PC1, PC2, PC3 to 0
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 80000000
  *            HCLK(Hz)                       = 80000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 1
  *            PLL_N                          = 20
  *            PLL_P                          = 7
  *            PLL_Q                          = 4
  *            PLL_R                          = 2
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
