#include "controler.h"
#include "usart.h"
#include "keyboard.h"

#define N   201			//�ͺ�10s��N = ts/T(�ͺ�ʱ��/����ʱ�� + 1)

float Kp;
float Ki;
float Kd;				//��ʼ��PID������keyboard�����ã���������ͨ�������ı�

float rt = 1.0;														  //����
float Err1 = 0;																//ƫ��err1
float Yk = 0, Yk_last = 0;										//Ԥ��������
float Err2 = 0, Err2_last = 0, Err2_pre = 0;	//ƫ��err2
float Uk[N] = {0};														//���������
float Yt = 0;																	//���

void Get_Err1(void)		
{
	rt = In;
	Err1 = rt - Yt;
}

void Get_Yk(void)			//Ԥ��������
{
	Yk_last = Yk;
	Yk = a*Yk_last + b*(Uk[0] - Uk[N - 1]);
}

void Get_Err2(void)
{
	Err2_pre = Err2_last;
	Err2_last = Err2;
	Err2 = Err1 - Yk;
}

float Get_Uk(void)		//�õ�������
{
	int i = 0;
	
	for (i = 0; i < N - 1; i++)
	{
		Uk[N-1-i] = Uk[N-2-i];
	}
	
	Ki = Px;
	Kp = Ix;
	
	Uk[0] = Uk[1] + Kp*(Err2 - Err2_last) + Ki*Err2 + Kd*(Err2 - 2*Err2_last + Err2_pre);
	
	if (Uk[0] >= 10)				//����������޷�
		Uk[0] = 10;
	if (Uk[0] <= -10)  		
		Uk[0] = -10;
	
//	Uk[0] = rt/K;				//���ſ�����
	
	return Uk[0];
}

