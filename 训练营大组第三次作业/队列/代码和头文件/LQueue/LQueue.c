#include "LQueue.h"

void InitLQueue(LQueue *Q) {
	if(Q->front!=NULL) {
		printf("队列已存在\n");
		return ;
	}
	Q->front=Q->rear=(Node*)malloc(sizeof(Node));
	Q->rear->next=NULL;
	printf("初始化队列成功\n");
	return ;
}

void DestoryLQueue(LQueue *Q) {
	if(Q->front==NULL) {
		printf("队列不存在\n");
		return ;
	}
	do {
		free(Q->front);
		Q->front=Q->front->next;
	} while(Q->front==Q->rear);
	Q->front=Q->rear=NULL;
	printf("销毁队列成功\n"); 
	return ;
}

Status IsEmptyLQueue(const LQueue *Q) {
	if(Q->front==NULL) {
		printf("队列不存在\n");
		return TRUE;
	}
	if(Q->front==Q->rear) {
		printf("队列为空\n");
		return TRUE;
	}
	return FALSE;
}

Status GetHeadLQueue(LQueue *Q) {
	if(IsEmptyLQueue(Q)==TRUE)
		return FALSE;
	if(Q->front->next->datatype==1)
		printf("->%d",*(int*)Q->front->next->data);
	if(Q->front->next->datatype==2)
		printf("->%c",*(char*)Q->front->next->data);
	if(Q->front->next->datatype==3)
		printf("->%.2f",*(float*)Q->front->next->data);
	return TRUE;
}

int LengthLQueue(LQueue *Q) {
	if(IsEmptyLQueue(Q)==TRUE)
		return FALSE;
	Node *p;
	int node;
	p=Q->front->next;
	while(p!=NULL) {
		node++;
		p=p->next;
	}
	printf("队列长度%d\n",node);
	return TRUE;
}

Status EnLQueue(LQueue *Q,void *data) {
	if(Q->front==NULL) {
		printf("队列不存在\n");
		return FALSE;
	}
	Node *p=(Node*)malloc(sizeof(Node));
	Q->rear->next=p;
	p->next=NULL;
	Q->rear=p;
	p->data = (void *)malloc(Q->length);
	memcpy(p->data, data, Q->length);
	printf("入队成功\n");
	return TRUE;
}

Status DeLQueue(LQueue *Q) {
	if(IsEmptyLQueue(Q)==TRUE)
		return FALSE;
	Node *p;
	p=Q->front;
	Q->front=Q->front->next;
	p->next=NULL;
	free(p);
	printf("出队成功\n");
	return TRUE;
}

void ClearLQueue(LQueue *Q) {
	if(IsEmptyLQueue(Q)==TRUE)
		return ;
	Q->rear=Q->front;
	Q->front->next=NULL;
	printf("清空队列成功\n"); 
	return;
}

Status TraverseLQueue(const LQueue *Q) {
	if(IsEmptyLQueue(Q)==TRUE)
		return FALSE;
	Node *p;
	p=Q->front->next;
	for(p; p!=NULL; p=p->next) {
		if(p->datatype== 1)
			printf("->%d",*(int*)p->data);
		if(p->datatype== 2)
			printf("->%c",*(char*)p->data);
		if(p->datatype== 3)
			printf("->%.2f",*(float*)p->data);
	}
	return TRUE;
}

