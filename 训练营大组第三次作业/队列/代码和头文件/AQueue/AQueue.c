#include "AQueue.h"

void InitAQueue(AQueue *Q) {
	if(Q->front==0) {
		printf("�����Ѵ���\n");
		return ;
	}
	int i;
	for(i=0; i<MAXQUEUE; i++)
		Q->data[i]=(void *)malloc(21);
	Q->front=0;
	Q->rear=0;
	Q->length=MAXQUEUE;
	printf("��ʼ�����гɹ�\n");
	return ;
}

void DestoryAQueue(AQueue *Q) {
	if(Q->front==-1) {
		printf("���в�����\n");
		return ;
	}
	int i;
	for(i=0; i<MAXQUEUE; i++)
		free(Q->data[i]);
	Q->front=-1;
	return ;
}

Status IsFullAQueue(const AQueue *Q) {
	if(Q->front==-1) {
		printf("���в�����\n");
		return TRUE;
	}
	if(Q->front==(Q->rear+1)%Q->length) {
		printf("��������\n");
		return TRUE;
	} else
		return FALSE;
}

Status IsEmptyAQueue(const AQueue *Q) {
	if(Q->front==-1) {
		printf("���в�����\n");
		return TRUE;
	}
	if(Q->front==Q->rear) {
		printf("����Ϊ��\n");
		return TRUE;
	}
	return FALSE;
}

Status GetHeadAQueue(AQueue *Q, void *e) {
	if(IsEmptyAQueue(Q)==TRUE)
		return FALSE;
	if(Q->datatype[Q->front]== 1)
		printf("->%d",*(int*)Q->data[Q->front]);
	if(Q->datatype[Q->front]== 2)
		printf("->%c",*(char*)Q->data[Q->front]);
	if(Q->datatype[Q->front]== 3)
		printf("->%.2f",*(float*)Q->data[Q->front]);
	return TRUE;
}

int LengthAQueue(AQueue *Q) {
	if(IsEmptyAQueue(Q)==TRUE)
		return FALSE;
	printf("���г���%d\n",Q->rear-Q->front);
	return TRUE;
}

Status EnAQueue(AQueue *Q, void *data) {
	if(IsFullAQueue(Q)==TRUE)
		return FALSE;
	if(Q->front==-1) {
		printf("���в�����\n");
		return FALSE;
	}
	memcpy(Q->data[Q->rear],data,20);
	Q->rear=(Q->rear+1)%Q->length;
	return TRUE;
}

Status DeAQueue(AQueue *Q) {
	if(IsEmptyAQueue(Q)==TRUE)
		return FALSE;
	Q->front=(Q->front+1)%Q->length;
	return TRUE;
}

void ClearAQueue(AQueue *Q) {
	if(IsEmptyAQueue(Q)==TRUE)
		return ;
	Q->front=Q->rear=0;
	return;
}

Status TraverseAQueue(const AQueue *Q) {
	if(IsEmptyAQueue(Q)==TRUE)
		return FALSE;
	int i=Q->front;
	while(i%Q->length!=Q->rear) {
		if(Q->datatype[i]== 1)
			printf("->%d",*(int*)Q->data[i]);
		if(Q->datatype[i]== 2)
			printf("->%c",*(char*)Q->data[i]);
		if(Q->datatype[i]== 3)
			printf("->%.2f",*(float*)Q->data[i]);
		i++;
	}
	return TRUE;
}

