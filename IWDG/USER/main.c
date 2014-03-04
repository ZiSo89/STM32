
/****************************************Copyright (c)****************************************************
** replays this file main.c in this path is:\HY-MiniSTM32V 2011.2.13\IWDG\USER
** and then run with ÏVision V4 KEIL: \HY-MiniSTM32V 2011.2.13\IWDG\MDK-ARM\Project.uvproj
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            IWDG 
**                            
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-10-30
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Zisoglou Athanasios for ATH 
** Modified date:           2012-01-15
** Version:                 v1.0
** Descriptions:            Unipolar Stepper Motor
**
motor-unipolar stepper:MSJE200A53 Sankyo Mitsubichi Disk Drive stepper
This motor was pulled from a 5 1/4 disk drive assembly. 
Specifications
Nominal Voltage		12
Resistance (Ohms)	100
Wires				5
Condition			pulled
Steps / Revolution	200
Made in				Japan
weight				160 grams
Step Size (degrees)	1.8

I control this with ULN2003
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "systick.h"
#include <stdio.h>

const int del=100; 	/* step Delay */

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private function prototypes -----------------------------------------------*/
void GPIO_Configuration(void);
void IWDG_Configuration(void);
void USART_Configuration(void);


/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
int main(void)
{
  delay_init();
  GPIO_Configuration();
  IWDG_Configuration(); 
  USART_Configuration();
  												  
  /* System Reset   */
  if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)   
  {	
     printf("IWDG RESET \r\n");
	 RCC_ClearFlag();
  }

  /* Infinite loop */
  
  while(1)
  {	
  
   /* LED1 PB6 and Step 1*/
    GPIO_SetBits(GPIOB , GPIO_Pin_6);   //set "1" the Coil 1 	
	GPIO_ResetBits(GPIOB , GPIO_Pin_8);	//set "0" the Coil 2
	GPIO_ResetBits(GPIOC , GPIO_Pin_10);//set "0" the Coil 3
	GPIO_ResetBits(GPIOC , GPIO_Pin_12);//set "0" the Coil 4
	delay_ms(del);
	/* LED2 PB8 and Step 2*/
	GPIO_ResetBits(GPIOB , GPIO_Pin_6);		 
    GPIO_SetBits(GPIOB , GPIO_Pin_8);	   
    GPIO_ResetBits(GPIOC , GPIO_Pin_10);
	GPIO_ResetBits(GPIOC , GPIO_Pin_12);
	delay_ms(del);

	/* LED3 PC10 and Step 3*/	 
    GPIO_ResetBits(GPIOB , GPIO_Pin_6);	
	GPIO_ResetBits(GPIOB , GPIO_Pin_8);	
	GPIO_SetBits(GPIOC , GPIO_Pin_10); 	   
    GPIO_ResetBits(GPIOC , GPIO_Pin_12); 
	delay_ms(del);

	/* LED4 PC12 and Step 4*/	 
    GPIO_ResetBits(GPIOB , GPIO_Pin_6);	
	GPIO_ResetBits(GPIOB , GPIO_Pin_8);
	GPIO_ResetBits(GPIOC , GPIO_Pin_10);	
	GPIO_SetBits(GPIOC , GPIO_Pin_12);	  
   	delay_ms(del);	 
	
	/*	Key input 
    if( !GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) )   //keyA
    {
	   	delay_ms(20);                           
		if( !GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) )
		IWDG_ReloadCounter();	   
    }	
		
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2))   // keyB 
    {
	   	delay_ms(20);                              
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2))
		IWDG_ReloadCounter();	  
	}	
	*/
  }//whille
}//main

/*******************************************************************************
* Function Name  : IWDG_Configuration
* Description    : ?/AA?∑AaOA
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void IWDG_Configuration(void)
{
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); 	/* ?/Ee0x5555,OAOUOE?i?∑?∑?A/????/Ee?¶AU */
  IWDG_SetPrescaler(IWDG_Prescaler_256);            /* AU≤?µIEUE±OO256∑O?µ 40K/256=156HZ(6.4ms) */ 
  /* ?/AA?∑∂®E±??Oc≥oE±?a */
  IWDG_SetReload(781);							    /* I??∑E±?a 5s/6.4MS=781 .??Oa≤ªAU/oOU0xfff*/
  IWDG_ReloadCounter();								/* I??∑*/
  IWDG_Enable(); 									/* E?AU?/AA?∑*/
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC , ENABLE); // Port that you want such as ABCDE now we enable B and C						 
  /**
  *	 LED1 -> PB0   LED2 -> PB1
  */					 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8;  // Pin that you will use 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		// if is OUT 
  GPIO_Init(GPIOB, &GPIO_InitStructure);				// the port for the pin that you write up
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);			// the same for port C

  /**
  *  KeyA -> PC13 , KeyB -> PB2
  */				
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : USART_Configuration
* Description    : Configure USART1 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_Configuration(void)
{ 
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure; 

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);
  /*
  *  USART1_TX -> PA9 , USART1_RX ->	PA10
  */				
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);		   

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART1, &USART_InitStructure); 
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
  USART_Cmd(USART1, ENABLE);
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
