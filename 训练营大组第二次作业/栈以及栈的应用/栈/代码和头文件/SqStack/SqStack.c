#include "SqStack.h"
void *initStack(SqStack *s,int sizes) { //初始化
	s->elem = (ElemType *)malloc(sizes * sizeof(ElemType));
	s->top  = -1;
	s->size = sizes;
	return s;
}

Status isEmptyStack(SqStack *s) { //判断栈是否为空
	if(s->elem==NULL||s->top==-1) {
		printf("栈为空\n");
		return 0;
	}
	return 1;
}

Status getTopStack(SqStack *s,ElemType *e) { //得到栈顶元素
	//第一步：判断栈是否存在
	if(isEmptyStack(s)==0)
		return;
	//第二步：得到栈顶元素
	printf("栈顶元素为:%d\n",s->elem[s->top]);
}

void *clearStack(SqStack *s) { //清空栈
	//第一步：判断栈是否存在
	if(isEmptyStack(s)==0)
		return;
	//第二步：清空栈
	s->top=-1;
	return s;
}

void *destroyStack(SqStack *s) { //销毁栈
	//第一步：判断栈是否存在
	if(s->elem==NULL) {
		printf("栈为空\n");
		return;
	}
	//第二步：销毁栈
	s->top=-1;
	free(s->elem);
	return s;
}

Status stackLength(SqStack *s,int *length) { //检测栈长度
	//第一步：判断栈是否存在
	if(s->elem==NULL) {
		printf("栈为空\n");
		return;
	}
	//第二步：检测栈长度
	printf("栈长度:%d\n",s->top+1); 
}

void *pushStack(SqStack *s,ElemType data) { //入栈
	//第一步：判断栈是否存在
	if(s->elem==NULL) {
		printf("栈为空\n");
		return;
	}
	//第二步：入栈
	printf("输入数据:");
	scanf("%d",&data);
	s->top++;
	s->elem[s->top]=data;
	return s;
}

void *popStack(SqStack *s,ElemType *data) { //出栈
	//第一步：判断栈是否存在
	if(isEmptyStack(s)==0)
		return;
	//第二步：出栈
	printf("出栈数据为:%d",s->elem[s->top]);
	s->top--;
	return s;
}

