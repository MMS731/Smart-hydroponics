/*
 * pH_value.c
 *
 *  Created on: May 23, 2024
 *      Author: makesh
 */
#include "pH_value.h"
#include "main.h"


ADC_HandleTypeDef *_pH_adc;
UART_HandleTypeDef *_pH_uart2;


void pH_Init(ADC_HandleTypeDef *hadc) {
	_pH_adc = hadc;
}

void pH_uart2(ADC_HandleTypeDef *huart2) {
	_pH_uart2 = huart2;
}

uint16_t AD_RES = 0;
uint16_t received_data[50];
uint16_t received_data_01[50];

float Get_pH_value()
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  // Start ADC Conversion
	  HAL_ADC_Start(_pH_adc);
	         // Poll ADC1 Perihperal & TimeOut = 1mSec
	  HAL_ADC_PollForConversion(_pH_adc, 1);
	  AD_RES = HAL_ADC_GetValue(_pH_adc);
	  TIM2->CCR1 = (AD_RES<<4);
	  HAL_Delay(1);

	  char arr[20];
	  sprintf(arr, "AnalogRead:%u\n\r", AD_RES);
	  HAL_UART_Transmit(_pH_uart2,(uint8_t*)arr,strlen(arr),10);

	  char buffer[10];
	  for(int i = 0; i <= 9; i++)
	  {
		  HAL_ADC_Start(_pH_adc);
		         // Poll ADC1 Perihperal & TimeOut = 1mSec
		  HAL_ADC_PollForConversion(_pH_adc, 1);
		  AD_RES = HAL_ADC_GetValue(_pH_adc);
		  TIM2->CCR1 = (AD_RES<<4);
		  HAL_Delay(1);
		  received_data[i] = AD_RES;
		  sprintf(buffer, "Received data [%d] %d \r \n", i,  received_data[i]);
		  HAL_UART_Transmit(_pH_uart2, (uint16_t *)buffer, strlen(buffer), 10000);
		  HAL_Delay(1000);
	  }



	  uint16_t temp = 0;
	  char buffer_01[10];
	  for(int i=0;i<9;i++)        //sort the analog from small to large
	    {
	      for(int j=i+1;j<10;j++)
	      {
	        if( received_data[i] > received_data[j])
	        {
	          temp= received_data[i] ;
	          received_data[i] = received_data[j];
	          received_data[j] = temp;
	        }
	      }
		  sprintf(buffer, "Ascending received data [%d] %d \r \n", i,  received_data[i]);
		  //HAL_UART_Transmit(&huart2, (uint16_t *)buffer_01, strlen(buffer_01), 1000);
	    }


	  uint16_t avg_value = 0;
	  for(int i = 2; i < 8; i++)
	  {
		  avg_value = avg_value + received_data[i];
	  }

	  float phValue = (float)avg_value*5.0/4096/6;
	  phValue = 3.5 * phValue;

	  char buffer_02[10];
	  sprintf(buffer_02, "Received pH value: %f \r \n", phValue);
	  //HAL_UART_Transmit(&huart2, (uint16_t *)buffer_02, strlen(buffer_02), 1000);
	  //HAL_Delay(1000);

/*
	  char buffer_01[10];
	  for(int j=0; j<9; j++)
	  {
		  sprintf(buffer, "Received data [%d] %d \r \n", j,  received_data[j]);
		  HAL_UART_Transmit(&huart2, (uint16_t *)buffer_01, strlen(buffer_01), 1000);
	  }

*/
	  return phValue;
  }
