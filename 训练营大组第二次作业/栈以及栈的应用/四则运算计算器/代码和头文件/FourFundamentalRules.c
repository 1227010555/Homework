#include "FourFundamentalRules.h"

//初始化
int initStack(DATA *s,int sizes) {
	s->data = (int *)malloc(sizes * sizeof(int));
	s->top  = -1;
	s->size = sizes;
	return 0;
}

//判断栈是否为空
int isEmptyStack(DATA *s) {
	if(s == NULL) {
		return -1;
	}
	return s->top == -1;
}

//入栈
int pushStack(DATA *s,int data) {
	if(s == NULL) {
		return -1;
	}

	s->top++;
	s->data[s->top] = data;

	return 0;
}

//出栈
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

//得到栈顶元素
int getTopStack(DATA *s) {
	if(s == NULL) {
		return -1;
	}
	if(isEmptyStack(s) != 0) {
		return -1;
	}

	return s->data[s->top];
}

//判断优先级
//根据四则运算中，先算括号，再乘除，再加减的原则 
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
