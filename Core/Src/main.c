/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct BI_MSG{
    uint8_t cmd;
    uint16_t param1;
    uint16_t param2;
}BI_MSG_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define RXBUFFERSIZE  256     //�?大接收字节数
char RxBuffer[RXBUFFERSIZE];   //接收数据
uint8_t aRxBuffer;			//接收中断缓冲
uint16_t Uart1_Rx_Cnt = 0;		//接收缓冲计数
int8_t rv_ok = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int BI_SP_Send_Msg(BI_MSG_t *request,BI_MSG_t *respone);
HAL_StatusTypeDef BI_SP_Send_cmd(uint8_t *tBuff,uint16_t tSize,uint8_t *rBuff,uint16_t rSize);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  //use interrupt received
//  rv_ok = 0;
//  HAL_UART_Receive_IT(&huart1, (uint8_t *)&RxBuffer, RXBUFFERSIZE);
  HAL_HalfDuplex_EnableTransmitter(&huart1);
  printf("\n\r UART Printf Example: retarget the C library printf function to the UART\n\r");
  printf("** Test finished successfully. ** \n\r");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int count = 0;
  uint8_t rvByte = 0;
  uint8_t rvBuff[10] = {0};
  int step = 10;
  BI_MSG_t request;
  BI_MSG_t respone;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // if(HAL_UART_Receive(&huart1,(uint8_t *)RxBuffer,8,100)==HAL_OK){
    //   HAL_UART_Transmit(&huart1,(uint8_t *)RxBuffer,8,0xFFFF);
    // }
    request.cmd = 0;
    int ret = BI_SP_Send_Msg(&request,&respone);
    if(ret==0){
      request.cmd = 1;
      request.param1 = 0;
      //播放
      BI_SP_Send_Msg(&request,&respone);
    }
    for(int i=0;i<10;i++){
      HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
      HAL_Delay(1100);
    }
    // HAL_HalfDuplex_EnableReceiver(&huart1);
//     HAL_StatusTypeDef status = HAL_UART_Receive(&huart1,rvBuff,10,100);
// //          if(status == HAL_OK){
// //    //        rvBuff[count] = rvByte;
// //            count +=10;
// //          }
//     // step = 10;
//     // while(step>0){
//     //   rvByte = 0;

//     //   step --;
//     // }
//     HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//     if(status == HAL_OK){
//       HAL_HalfDuplex_EnableTransmitter(&huart1);
//       status = HAL_UART_Transmit(&huart1,rvBuff,10,0xffff);
//       memset(rvBuff,0,10);
//     }
//	HAL_Delay(100);
//    if(count >=10){
//      HAL_HalfDuplex_EnableTransmitter(&huart1);
//      HAL_UART_Transmit(&huart1,rvBuff,count%10,0xffff);
//      // printf("Toggle Led\r\n");
//      memset(rvBuff,0,10);
//      count = 0;
//      HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//      HAL_Delay(50);
//      HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//      HAL_Delay(50);
//      HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//      HAL_Delay(50);
//      HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//      HAL_Delay(50);
//    }
    
	// rv_ok = 0;
	// Uart1_Rx_Cnt = 0;
	// HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);   //再开启接收中�?
	// while(rv_ok!=1){
	// 	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	// 	HAL_Delay(50);
	// }
	// HAL_UART_Transmit(&huart1, (uint8_t *)RxBuffer, Uart1_Rx_Cnt,0xFFFF);
	// memset(RxBuffer,0x00,sizeof(RxBuffer));
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

int BI_SP_Send_Msg(BI_MSG_t *request,BI_MSG_t *respone){
  uint8_t tBuff[10] = {0};
  uint8_t rBuff[10] = {0};
  tBuff[0] = 0x55;
  tBuff[1] = request->cmd;
  tBuff[2] = (uint8_t)(request->param1&0xff);
  tBuff[3] = (uint8_t)((request->param1>>8)&0xff);
  tBuff[4] = (uint8_t)(request->param2&0xff);
  tBuff[5] = (uint8_t)((request->param2>>8)&0xff);
  tBuff[6] = 0xff;
  tBuff[7] = 0xff;
  tBuff[8] = 0x0d;
  tBuff[9] = 0x0a;
  HAL_StatusTypeDef status = BI_SP_Send_cmd(tBuff,10,rBuff,10);
  if(status == HAL_OK){
    respone->cmd = rBuff[1];
    respone->param1 = (rBuff[2]|(rBuff[3]<<8))&0xffff;
    respone->param2 = (rBuff[4]|(rBuff[5]<<8))&0xffff;
    return 0;
  }
  return -1;
}

/***
 * @brief send speaker control cmd to ad158.
 * @param tBuff tx buffer address
 * @param tSize tx buff size is 10
 * @param rBuff respone buff
 * @param rSize respone size is 10
 * @retval HAL_OK means succcess
 * **/
HAL_StatusTypeDef BI_SP_Send_cmd(uint8_t *tBuff,uint16_t tSize,uint8_t *rBuff,uint16_t rSize){
  HAL_StatusTypeDef status = HAL_OK;
  HAL_HalfDuplex_EnableTransmitter(&huart1);
  status = HAL_UART_Transmit(&huart1,tBuff,tSize,800);
  if(status != HAL_OK){
    //logd("BI_Semd_cmd faild")
    return status;
  }
  HAL_HalfDuplex_EnableReceiver(&huart1);
  status = HAL_UART_Receive(&huart1,rBuff,rSize,1000);
  return status;
}
// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// {
//   /* Prevent unused argument(s) compilation warning */
//   UNUSED(huart);
//   /* NOTE: This function Should not be modified, when the callback is needed,
//            the HAL_UART_TxCpltCallback could be implemented in the user file
//    */
// //  char buff[50]={0};
// //  sprintf(buff,"rev st:%d it:%d\r\n",(int)huart->RxState,(int)huart->ErrorCode);
// //  HAL_UART_Transmit(&huart1, (uint8_t *)buff, strlen(buff),0xFFFF);
// //  rv_ok = 1;
//    if(Uart1_Rx_Cnt >= 255)  //溢出判断
// 	 {
// 	 	Uart1_Rx_Cnt = 0;
// 	 	memset(RxBuffer,0x00,sizeof(RxBuffer));
// 	 	HAL_UART_Transmit(&huart1, (uint8_t *)"memmeryout", 10,0xFFFF);
        
// 	 }
// 	 else
// 	 {
// 	 	RxBuffer[Uart1_Rx_Cnt++] = aRxBuffer;   //接收数据转存
	
// 	 	if((RxBuffer[Uart1_Rx_Cnt-1] == 0x0A)&&(RxBuffer[Uart1_Rx_Cnt-2] == 0x0D)) //判断结束�?
// 	 	{
// 	 		rv_ok = 1;
// 	 		return;
// 	 	}
// 	 }
//    if(rv_ok==0){
// 	   HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);   //再开启接收中�?
//    }
// }
/* USER CODE END 4 */

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

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

