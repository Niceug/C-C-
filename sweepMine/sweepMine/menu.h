#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int showMenu()
{
	int option;
	printf("*******************************\n");
	printf("****1.��ʼ��Ϸ   0.�˳���Ϸ****\n");
	printf("*******************************\n");
	printf("����������ѡ��>");
	scanf("%d", &option);
	return option;
}