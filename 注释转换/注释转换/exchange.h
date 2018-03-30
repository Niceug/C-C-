#pragma once
#ifndef __EXCHANGE__
#define __EXCHANGE__

#include <stdlib.h>
#include <stdio.h>
enum STATE {
	NULL_STATE,
	C_STATE,
	CPP_STATE,
	END_STATE
};


//״̬��ת����
void exchange(FILE* pfread, FILE* pfwrite);
//����c״̬����
void DoC_State(FILE* pfread, FILE* pfwrite, enum STATE * ps);
//����cpp״̬����
void DoCPP_State(FILE* pfread, FILE* pfwrite, enum STATE * ps);
//������״̬����
void DoNULL_State(FILE* pfread, FILE* pfwrite, enum STATE * ps);
#endif // !__EXCHANGE__

