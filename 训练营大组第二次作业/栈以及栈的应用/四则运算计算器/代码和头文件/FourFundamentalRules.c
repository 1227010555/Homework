#include "FourFundamentalRules.h"

//��ʼ��
int initStack(DATA *s,int sizes) {
	s->data = (int *)malloc(sizes * sizeof(int));
	s->top  = -1;
	s->size = sizes;
	return 0;
}

//�ж�ջ�Ƿ�Ϊ��
int isEmptyStack(DATA *s) {
	if(s == NULL) {
		return -1;
	}
	return s->top == -1;
}

//��ջ
int pushStack(DATA *s,int data) {
	if(s == NULL) {
		return -1;
	}

	s->top++;
	s->data[s->top] = data;

	return 0;
}

//��ջ
int popStack(DATA *s) {
	if(s == NULL) {
		return -1;
	}
	if(isEmptyStack(s) != 0) {
		return -1;
	}
	int data;
	data = s->data[s->top];
	s->top--;

	return data;
}

//�õ�ջ��Ԫ��
int getTopStack(DATA *s) {
	if(s == NULL) {
		return -1;
	}
	if(isEmptyStack(s) != 0) {
		return -1;
	}

	return s->data[s->top];
}

//�ж����ȼ�
//�������������У��������ţ��ٳ˳����ټӼ���ԭ�� 
int judge(char ch) {
	switch (ch) {
		case '(' : {
			return 3;
		}
		case '*' : {
			return 2;
		}
		case '/' : {
			return 2;
		}
		case '+' : {
			return 1;
		}
		case '-' : {
			return 1;
		}
		default : {
			return -1;
		}
	}
}
