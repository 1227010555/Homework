#include "LinkStack.h"

void *initLStack(LinkStack *s) { //��ʼ��ջ
	s=(LinkStack *)malloc (sizeof(StackNode));
	s->top=NULL;
	s->count=0;
	printf("��ʼ���ɹ�\n"); 
	return s;
}

Status isEmptyLStack(LinkStack *s) { //�ж�ջ�Ƿ�Ϊ�ջ�Ϊ�� 
	if(s==NULL) {
		printf("��ջ������\n");
		return ERROR; 
	}
		if(s->count==0){
		printf("��ջΪ��\n");
		return ERROR;
	}
	return;
}

Status getTopLStack(LinkStack *s,ElemType *e) { //�õ�ջ��Ԫ��
	//��һ�����ж���ջ�Ƿ���ڻ�Ϊ�� 
	if(isEmptyLStack(s)==ERROR)
		return;
	//�ڶ��������ջ��Ԫ��
	printf("��ǰջ������Ϊ:%d\n",s->top->data);
}

void *clearLStack(LinkStack *s) { //���ջ
	//��һ�����ж���ջ�Ƿ���ڻ�Ϊ�� 
	if(isEmptyLStack(s)==ERROR)
		return s;
	//�ڶ��������ջ
	LinkStackPtr stack;
	for(s->count; s->count>0; s->count--) {
		stack=s->top;
		s->top=s->top->next;
		free(stack);
	}
	return s;
}

void *destroyLStack(LinkStack *s) { //����ջ
	//��һ�����ж���ջ�Ƿ����
	if(s==NULL) {
		printf("��ջ������\n");
		return ;
	}
	//�ڶ��������ջ
	LinkStackPtr stack;
	for(s->count; s->count>0; s->count--) {
		stack=s->top;
		s->top=s->top->next;
		free(stack);
	}
	//������������ջ
	free(s->top);
	s->top=NULL;
	s=NULL;
	return s;
}

Status LStackLength(LinkStack *s,int *length) { //���ջ����
	//��һ�����ж���ջ�Ƿ���ڻ�Ϊ�� 
	if(isEmptyLStack(s)==ERROR)
		return;
	//�ڶ��������ջ����
	printf("ջ����Ϊ:%d\n",s->count);
}

void *pushLStack(LinkStack *s,ElemType data) { //��ջ
	//��һ�����ж���ջ�Ƿ����
	if(s==NULL) {
		printf("��ջ������\n");
		return ;
	}
	//�ڶ�������ջ
	LinkStackPtr stack;
	stack=(LinkStackPtr)malloc (sizeof(StackNode));
	printf("��������\n");
	scanf("%d",&stack->data);
	stack->next=s->top;
	s->top=stack;
	s->count++;
	return s;
}

void *popLStack(LinkStack *s,ElemType *data) { //��ջ
	//��һ�����ж���ջ�Ƿ���ڻ�Ϊ�� 
	if(isEmptyLStack(s)==ERROR)
		return;
	//�ڶ�������ջ
	if(s->top->next!=NULL) {
		printf("��ջ������Ϊ:%d\n",s->top->data);
		StackNode *p;
		p=s->top;
		s->top=p->next;
		free(p);
	} else {
		printf("��ջ������Ϊ:%d\n",s->top->data);
		free(s->top);
		s->top=NULL;
	}
	s->count--;
	return s;
}



