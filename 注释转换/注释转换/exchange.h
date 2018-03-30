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


//状态轮转函数
void exchange(FILE* pfread, FILE* pfwrite);
//处理c状态函数
void DoC_State(FILE* pfread, FILE* pfwrite, enum STATE * ps);
//处理cpp状态函数
void DoCPP_State(FILE* pfread, FILE* pfwrite, enum STATE * ps);
//处理无状态函数
void DoNULL_State(FILE* pfread, FILE* pfwrite, enum STATE * ps);
#endif // !__EXCHANGE__

