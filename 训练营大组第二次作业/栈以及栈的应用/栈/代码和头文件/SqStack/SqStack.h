#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef enum SS_status 
{
	ERROR = 0, SUCCESS = 1
} SS_status;

typedef int ElemType;

typedef struct SqStack 
{
	ElemType *elem;
	int top;
	int size;
} SqStack;


//���������˳��ջ
void *initStack(SqStack *s,int sizes);//��ʼ��ջ
Status isEmptyStack(SqStack *s);//�ж�ջ�Ƿ�Ϊ��
Status getTopStack(SqStack *s,ElemType *e); //�õ�ջ��Ԫ��
void *clearStack(SqStack *s);//���ջ
void *destroyStack(SqStack *s);//����ջ
Status stackLength(SqStack *s,int *length);//���ջ����
void *pushStack(SqStack *s,ElemType data);//��ջ
void *popStack(SqStack *s,ElemType *data);//��ջ


#endif 
