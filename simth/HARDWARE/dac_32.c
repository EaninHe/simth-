#include "dac_32.h"

void Dac1_Init(void)
{
  
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��PORTAͨ��ʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //ʹ��DACͨ��ʱ�� 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // �˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 //ģ������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);						//PA.4 �����
					
	DAC_InitType.DAC_Trigger=DAC_Trigger_None;	//��ʹ�ô������� TEN1=0
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1�������ر� BOFF1=1
  DAC_Init(DAC_Channel_1,&DAC_InitType);	 //��ʼ��DACͨ��1

	DAC_Cmd(DAC_Channel_1, ENABLE);  //ʹ��DAC1
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12λ�Ҷ������ݸ�ʽ����DACֵ

}

//����ѹת����ֵ����DA����
//���룺DA��ѹֵ
void VoltoDA(float Vol)
{
	unsigned int DaValue;
	
	DaValue = Vol * 4095 / 3.3;		//3.3V�ο���ѹ
	
	if (DaValue >= 3720)					//3.0V�޷�
		DaValue = 3720;
	if (DaValue <= 0)
		DaValue = 0;							//0V�޷�
	
	DAC_SetChannel1Data(DAC_Align_12b_R, (int)DaValue);//��ʼֵΪ0	
}

//��һ��Yt��1��λYt��Ӧ0.01V,Yt��Ϊ��-150~~~150��
//���룺Yt
//���أ�DA��ѹֵ
float RangeToDA(float send)
{
	float data;	
	
	if (send >= 10)
		send = 10;
	if (send <= -10)		//�޷�
		send = -10;
	
	if (-10 <= send && send < 0)
		data = (10+send) * 0.15;
	else if (0 <= send && send <= 10)
		data = 1.5 + send * 0.15;
	return data;
}


