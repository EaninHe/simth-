#ifndef __CONTROLER_H
#define __CONTROLER_H

#include "sys.h"

extern float a, b;
extern float rt;									//����
extern float Err1;											//ƫ��err1
extern float Yk, Yk_last;								//Ԥ��������
extern float Err2, Err2_last, Err2_pre;	//ƫ��err2
extern float Uk[];											//���������
extern float Yt;												//���
extern float K;

void Get_Err1(void);
void Get_Yk(void);
void Get_Err2(void);
float Get_Uk(void);

#endif
