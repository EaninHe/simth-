#include "key.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "keyboard.h"
#include "controler.h"


int Key1=0, Key2=0, Key3=0, Key4=0,Key5=0;

void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTBʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
	
	/**********�ж��߳�ʼ��*****************/
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6);
  EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_Init(&EXTI_InitStructure);	 

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource7);
  EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_Init(&EXTI_InitStructure);	 
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource8);
  EXTI_InitStructure.EXTI_Line=EXTI_Line8;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_Init(&EXTI_InitStructure);	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource9);
  EXTI_InitStructure.EXTI_Line=EXTI_Line9;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_Init(&EXTI_InitStructure);	 
	/*******���ȼ���ʼ��**************************/
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line6)!=RESET)
	{
		delay_ms(15);//����
		if(KEY1==0)	 //����KEY1
		{
			LED1=!LED1;
			Key1=1;
		}
		EXTI_ClearITPendingBit(EXTI_Line6);  //���LINE6�ϵ��жϱ�־λ
	}		
	
	else if(EXTI_GetITStatus(EXTI_Line7)!=RESET)
	{ 
		delay_ms(15);//����
		if(KEY2==0)	 //����KEY2
		{
			LED2=!LED2;
			Key2=1;
		}	
		EXTI_ClearITPendingBit(EXTI_Line7);  //���LINE7�ϵ��жϱ�־λ
	}		
	 
	else if(EXTI_GetITStatus(EXTI_Line8)!=RESET)
	{ 
		delay_ms(15);//����
		if(KEY3==0)	 //����KEY3
		{
			LED1=!LED1;
			Key3=1;
		}
		EXTI_ClearITPendingBit(EXTI_Line8);  //���LINE8�ϵ��жϱ�־λ
	}		
	 
	 else if(EXTI_GetITStatus(EXTI_Line9)!=RESET)
	{ 
		delay_ms(15);//����
		if(KEY4==0)	 //����KEY4
		{
			LED2=!LED2;
			Key4=1;
		}	
		EXTI_ClearITPendingBit(EXTI_Line9);  //���LINE9�ϵ��жϱ�־λ
	}
}
 



