#include "SqStack.h"
void *initStack(SqStack *s,int sizes) { //��ʼ��
	s->elem = (ElemType *)malloc(sizes * sizeof(ElemType));
	s->top  = 0;
	s->size = sizes;
	return s;
}

Status isEmptyStack(SqStack *s) { //�ж�ջ�Ƿ�Ϊ��
	if(s->top==-1) {
		printf("ջ������\n");
		return 0;
	}
	if(s->top==0) {
		printf("ջΪ��\n");
		return 0;
	}
	return 1;
}

Status getTopStack(SqStack *s,ElemType *e) { //�õ�ջ��Ԫ��
	//��һ�����ж�ջ�Ƿ���ڻ�Ϊ�� 
	if(isEmptyStack(s)==0)
		return;
	//�ڶ������õ�ջ��Ԫ��
	printf("ջ��Ԫ��Ϊ:%d\n",s->elem[s->top]);
}

void *clearStack(SqStack *s) { //���ջ
	//��һ�����ж�ջ�Ƿ���ڻ�Ϊ�� 
	if(isEmptyStack(s)==0)
		return s;
	//�ڶ��������ջ
	s->top=0;
	return s;
}

void *destroyStack(SqStack *s) { //����ջ
	//��һ�����ж�ջ�Ƿ����
	if(s->top==-1) {
		printf("ջ������\n");
		return s;
	}
	//�ڶ���������ջ
	s->top=-1;
	free(s->elem);
	return s;
}

Status stackLength(SqStack *s,int *length) { //���ջ����
	//��һ�����ж�ջ�Ƿ����
	if(s->top==-1) {
		printf("ջ������\n");
		return;
	}
	//�ڶ��������ջ����
	printf("ջ����:%d\n",s->top);
}

void *pushStack(SqStack *s,ElemType data) { //��ջ
	//��һ�����ж�ջ�Ƿ����
	if(s->top==-1) {
		printf("ջ������\n");
		return s;
	}
	//�ڶ�������ջ
	printf("��������:");
	scanf("%d",&data);
	s->top++;
	s->elem[s->top]=data;
	return s;
}

void *popStack(SqStack *s,ElemType *data) { //��ջ
	//��һ�����ж�ջ�Ƿ���ڻ�Ϊ�� 
	if(isEmptyStack(s)==0)
		return s;
	//�ڶ�������ջ
	printf("��ջ����Ϊ:%d",s->elem[s->top]);
	s->top--;
	return s;
}

