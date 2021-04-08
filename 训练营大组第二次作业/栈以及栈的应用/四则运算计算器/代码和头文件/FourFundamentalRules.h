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

int initStack(DATA *p,int sizes);//初始化栈
int isEmptyStack(DATA *p);//判断栈是否为空
int pushStack(DATA *p,int data);//入栈
int popStack(DATA *p);//出栈
int getTopStack(DATA *p);//得到栈顶元素
int judge(char ch);//判断优先级

#endif
