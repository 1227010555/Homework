#include "LinkStack.h"

void *initLStack(LinkStack *s) { //初始化栈
	s=(LinkStack *)malloc (sizeof(StackNode));
	s->top=NULL;
	s->count=0;
	printf("初始化成功\n"); 
	return s;
}

Status isEmptyLStack(LinkStack *s) { //判断栈是否为空或为空 
	if(s==NULL) {
		printf("链栈不存在\n");
		return ERROR; 
	}
		if(s->count==0){
		printf("链栈为空\n");
		return ERROR;
	}
	return;
}

Status getTopLStack(LinkStack *s,ElemType *e) { //得到栈顶元素
	//第一步：判断链栈是否存在或为空 
	if(isEmptyLStack(s)==ERROR)
		return;
	//第二步：输出栈顶元素
	printf("当前栈顶数据为:%d\n",s->top->data);
}

void *clearLStack(LinkStack *s) { //清空栈
	//第一步：判断链栈是否存在或为空 
	if(isEmptyLStack(s)==ERROR)
		return s;
	//第二步：清空栈
	LinkStackPtr stack;
	for(s->count; s->count>0; s->count--) {
		stack=s->top;
		s->top=s->top->next;
		free(stack);
	}
	return s;
}

void *destroyLStack(LinkStack *s) { //销毁栈
	//第一步：判断链栈是否存在
	if(s==NULL) {
		printf("链栈不存在\n");
		return ;
	}
	//第二步：清空栈
	LinkStackPtr stack;
	for(s->count; s->count>0; s->count--) {
		stack=s->top;
		s->top=s->top->next;
		free(stack);
	}
	//第三步：销毁栈
	free(s->top);
	s->top=NULL;
	s=NULL;
	return s;
}

Status LStackLength(LinkStack *s,int *length) { //检测栈长度
	//第一步：判断链栈是否存在或为空 
	if(isEmptyLStack(s)==ERROR)
		return;
	//第二步：检测栈长度
	printf("栈长度为:%d\n",s->count);
}

void *pushLStack(LinkStack *s,ElemType data) { //入栈
	//第一步：判断链栈是否存在
	if(s==NULL) {
		printf("链栈不存在\n");
		return ;
	}
	//第二步：入栈
	LinkStackPtr stack;
	stack=(LinkStackPtr)malloc (sizeof(StackNode));
	printf("输入数据\n");
	scanf("%d",&stack->data);
	stack->next=s->top;
	s->top=stack;
	s->count++;
	return s;
}

void *popLStack(LinkStack *s,ElemType *data) { //出栈
	//第一步：判断链栈是否存在或为空 
	if(isEmptyLStack(s)==ERROR)
		return;
	//第二步：出栈
	if(s->top->next!=NULL) {
		printf("出栈的数据为:%d\n",s->top->data);
		StackNode *p;
		p=s->top;
		s->top=p->next;
		free(p);
	} else {
		printf("出栈的数据为:%d\n",s->top->data);
		free(s->top);
		s->top=NULL;
	}
	s->count--;
	return s;
}



