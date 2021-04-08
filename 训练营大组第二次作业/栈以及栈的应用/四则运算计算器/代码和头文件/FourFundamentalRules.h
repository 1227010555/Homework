#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define SIZE      100

#include <stdio.h>
#include <stdlib.h>
#include <process.h>

typedef struct {
	float *data;
	int top;
	int size;
} DATA;

int initStack(DATA *p,int sizes);//��ʼ��ջ
int isEmptyStack(DATA *p);//�ж�ջ�Ƿ�Ϊ��
int pushStack(DATA *p,int data);//��ջ
int popStack(DATA *p);//��ջ
int getTopStack(DATA *p);//�õ�ջ��Ԫ��
int judge(char ch);//�ж����ȼ�

#endif
