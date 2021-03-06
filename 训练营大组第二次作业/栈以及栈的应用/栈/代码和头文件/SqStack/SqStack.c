#include "SqStack.h"
void *initStack(SqStack *s,int sizes) { //初始化
	s->elem = (ElemType *)malloc(sizes * sizeof(ElemType));
	s->top  = 0;
	s->size = sizes;
	printf("初始化栈成功");
	return s;
}

Status isEmptyStack(SqStack *s) { //判断栈是否为空
	if(s->top==-1) {
		printf("栈不存在\n");
		return ERROR;
	}
	if(s->top==0) {
		printf("栈为空\n");
		return ERROR;
	}
	return SUCCESS;
}

Status getTopStack(SqStack *s,ElemType *e) { //得到栈顶元素
	//第一步：判断栈是否存在或为空 
	if(isEmptyStack(s)==ERROR)
		return;
	//第二步：得到栈顶元素
	printf("栈顶元素为:%d\n",s->elem[s->top]);
	return;
}

void *clearStack(SqStack *s) { //清空栈
	//第一步：判断栈是否存在或为空 
	if(isEmptyStack(s)==ERROR)
		return s;
	//第二步：清空栈
	s->top=0;
	printf("清空栈成功\n"); 
	return s;
}

void *destroyStack(SqStack *s) { //销毁栈
	//第一步：判断栈是否存在
	if(s->top==-1) {
		printf("栈不存在\n");
		return s;
	}
	//第二步：销毁栈
	s->top=-1;
	free(s->elem);
	printf("销毁栈成功\n"); 
	return s;
}

Status stackLength(SqStack *s,int *length) { //检测栈长度
	//第一步：判断栈是否存在
	if(s->top==-1) {
		printf("栈不存在\n");
		return;
	}
	//第二步：检测栈长度
	printf("栈长度:%d\n",s->top);
	return;
}

void *pushStack(SqStack *s,ElemType data) { //入栈
	//第一步：判断栈是否存在
	if(s->top==-1) {
		printf("栈不存在\n");
		return s;
	}
	//第二步：入栈
	printf("输入数据:");
	scanf("%d",&data);
	s->top++;
	s->elem[s->top]=data;
	printf("入栈成功\n");
	return s;
}

void *popStack(SqStack *s,ElemType *data) { //出栈
	//第一步：判断栈是否存在或为空 
	if(isEmptyStack(s)==ERROR)
		return s;
	//第二步：出栈
	printf("出栈数据为:%d",s->elem[s->top]);
	s->top--;
	return s;
}

