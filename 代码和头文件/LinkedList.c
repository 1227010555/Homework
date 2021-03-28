#include "LinkedList.h"

/**
 *  @name        : SinglyLinkedList *CreatSinglyLinkedList();
 *	@description : ������������
 *	@param		 : head(ͷָ��);mid(ǰ���ָ�룬��������һ���ڴ�);back(�����ָ�룬����ָ���µ��ڴ�);node(�����);i(ѭ������)
 *	@return		 : head
 *  @notice      : None
 */
SinglyLinkedList *CreatSinglyLinkedList() {
	SinglyLinkedList *head,*mid,*back;
	int node=0,i;
	//��һ��:��������
	do {
		printf("��������\n");
		scanf("%d",&node);
		getchar();
		if(node<=0)
			printf("���������������\n");
	} while(node<=0);
	//�ڶ���������������������
	mid=back=head=(SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
	printf("��������\n");
	scanf("%d",&back->data);
	if(node!=1) {
		for(i=2; i<=node; i++) {
			mid=(SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
			back->next=mid;
			back=mid;
			printf("��������\n");
			scanf("%d",&back->data);
		}
	}
	back->next=NULL;
	//����������������
	SinglyPrint(head);
	printf("�����ɹ�\n");
	return head;
}

/**
 *  @name        : DoublyLinkedList *CreatDoublyLinkedList();
 *	@description : ����˫������
 *	@param		 : head(ͷָ��);mid(ǰ���ָ�룬��������һ���ڴ�);back(�����ָ�룬����ָ���µ��ڴ�);node(�����);i(ѭ������)
 *	@return		 : head
 *  @notice      : None
 */
DoublyLinkedList *CreatDoublyLinkedList() {
	DoublyLinkedList *head,*mid,*back;
	int node=0,i;
	//��һ��:��������
	do {
		printf("��������\n");
		scanf("%d",&node);
		getchar();
		if(node<=0)
			printf("���������������\n");
	} while(node<=0);
	//�ڶ���������������������
	mid=back=head=(DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
	printf("��������\n");
	scanf("%d",&back->data);
	mid->front=NULL;
	for(i=2; i<=node; i++) {
		mid=(DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
		back->next=mid;
		mid->front=back;
		back=mid;
		printf("��������\n");
		scanf("%d",&back->data);
	}
	back->next=NULL;
	//����������������
	DoublyPrint(head);
	printf("�����ɹ�\n");
	return head;
}

/**
 *  @name        : SinglyLinkedList *ParitySwap(SinglyLinkedList *head);
 *	@description : ��������ż����
 *	@param		 : head(ͷָ��);top(ǰ��ָ��);mid(�м�ָ��);back(����ָ��);node(�����);i(ѭ������)
 *	@return		 : head
 *  @notice      : None
 */
SinglyLinkedList *ParitySwap(SinglyLinkedList *head) {
	int node=0,i;
	SinglyLinkedList *mid,*back,*top;
	//��һ�����ж������Ƿ����
	if(ExistLinkedList(head)==0)
		return;
	//�ڶ����������
	mid=back=top=head;
	node=CountNode(head);
	//�����������ݽ����ż���������
	if(node==1) {
		SinglyPrint(head);
	}
	head=head->next;
	if(node%2==0) {
		for(i=node; i>0; i-=2) {
			if(i>3) {
				top=mid->next->next;
				mid=mid->next;
				back->next=top->next;
				mid->next=back;
				mid=back=top;
			}
			if(i==2) {
				mid=mid->next;
				back->next=NULL;
				mid->next=back;
				SinglyPrint(head);
				return head;
			}
		}
	} else {
		for(i=node; i>0; i-=2) {
			if(i==3) {
				top=mid->next->next;
				mid=mid->next;
				back->next=top;
				mid->next=back;
				mid=back=top;
				SinglyPrint(head);
				return head;
			}
			if(i>3) {
				top=mid->next->next;
				mid=mid->next;
				back->next=top->next;
				mid->next=back;
				mid=back=top;
			}
		}
	}
}

/**
 *  @name        : SinglyLinkedList *FindMidpoint(SinglyLinkedList *head);
 *	@description : �ҵ���������е�
 *	@param		 : head(ͷָ��);p(����ָ���е��ָ��);node(�����);i(ѭ������)
 *	@return		 : head
 *  @notice      : None
 */
SinglyLinkedList *FindMidpoint(SinglyLinkedList *head) {
	int node=0,i;
	SinglyLinkedList *p;
	p=head;
	//��һ�����ж������Ƿ����
	if(ExistLinkedList(head)==0)
		return;
	//�ڶ����������
	node=CountNode(head);
	//����������е�λ��
	if(node%2==0) {
		for(i=1; i<node/2; i++)
			p=p->next;
		printf("��%d�����:%d\n��%d�����%d:\n",node/2,p->data,node/2+1,p->next->data);
	} else {
		for(i=0; i<node/2; i++)
			p=p->next;
		printf("��%d�����:%d\n",node/2+1,p->data);
	}
	return head;
}

/**
 *  @name        : SinglyLinkedList *Circle(SinglyLinkedList *head);
 *	@description : �ж������Ƿ�ɻ�
 *	@param		 : head(ͷָ��);fast(��ǰ������);slow(��ǰ��һ��);temp(��¼ѭ�����);i(ѭ������)
 *	@return		 : head
 *  @notice      : None
 */
SinglyLinkedList *Circle(SinglyLinkedList *head) {
	SinglyLinkedList *fast,*slow,*temp;
	int i;
	fast=slow=head;
	//��һ�����ж������Ƿ����
	if(ExistLinkedList(head)==0)
		return;
	//�ڶ�����������ɻ�
	while(fast->next!=NULL)
		fast=fast->next;
	temp=fast;
	fast->next=head;
	//���������ж�
	fast=head;
	for(fast,slow; fast->next!=NULL; fast=fast->next->next,slow=slow->next)
		if(fast==slow) {
			printf("����ɻ�\n");
			for(i=1; i<10; i++) {
				printf("��%d���������:%d\n",i,fast->data);
				fast=fast->next;
			}
			temp->next=NULL;
			return head;
		}
	printf("�����ɻ�\n");
}

/**
 *  @name        : SinglyLinkedList *Reverse(SinglyLinkedList *head);
 *	@description : ��ת����
 *	@param		 : head(ͷָ��);mid(ǰ���ָ�룬����һ���ڴ�);back(�����ָ�룬����ָ���µ��ڴ�);node(�����)
 *	@return		 : head
 *  @notice      : None
 */
SinglyLinkedList *Reverse(SinglyLinkedList *head) {
	SinglyLinkedList *mid,*back,*top;
	int node;
	//��һ�����ж������Ƿ����
	if(ExistLinkedList(head)==0)
		return;
	//�ڶ�������ת
	if (head->next==NULL) {
		return head;
	} else {
		back=NULL;
		mid=head;
		top=head->next;
		while(1) {
			mid->next=back;
			if (top==NULL) {
				break;
			}
			back=mid;
			mid=top;
			top=top->next;
		}
		head=mid;
		SinglyPrint(head);
	}
	return head;
}

/**
 *  @name        : void SinglyPrint(SinglyLinkedList *p);
 *	@description : ������������
 *	@param		 : p(�����õ�ָ��);i(ѭ������)
 *	@return		 : none
 *  @notice      : None
 */
void SinglyPrint(SinglyLinkedList *p) {
	int i=1;
	while(p!=NULL) {
		printf("��%d���������:%d\n",i++,p->data);
		p=p->next;
	}
	return;
}

/**
 *  @name        : void DoublyPrint(DoublyLinkedList *p);
 *	@description : ����˫������
 *	@param		 : p(�����õ�ָ��);i(ѭ������)
 *	@return		 : none
 *  @notice      : None
 */
void DoublyPrint(DoublyLinkedList *p) {
	int i=1;
	while(p->next!=NULL) {
		printf("��%d���������:%d\n",i++,p->data);
		p=p->next;
	}
	printf("��%d���������:%d\n",i++,p->data);
	while(p!=NULL) {
		printf("��%d���������:%d\n",--i,p->data);
		p=p->front;
	}
	return;
}

/**
 *  @name        : int CountNode(SinglyLinkedList *head);
 *	@description : �����
 *	@param		 : head(ͷָ��);node(�����)
 *	@return		 : int
 *  @notice      : None
 */
int CountNode(SinglyLinkedList *head) {
	int node=0;
	while(head!=NULL) {
		node++;
		head=head->next;
	}
	return node;
}

/**
 *  @name        : int CountNode(SinglyLinkedList *head);
 *	@description : �����Ƿ����
 *	@param		 : head(ͷָ��)
 *	@return		 : 0
 *  @notice      : None
 */
SinglyLinkedList *ExistLinkedList(SinglyLinkedList *head) {
	if(head==NULL) {
		printf("��������\n");
		return 0;
	}
}

/**
 *  @name        : int CountNode(SinglyLinkedList *head);
 *	@description : �ͷ������ڴ�
 *	@param		 : head(ͷָ��);p(����ͷָ��ǰ���ָ��)
 *	@return		 : None
 *  @notice      : None
 */
SinglyLinkedList *FreeLinkedList(SinglyLinkedList *head) {
	SinglyLinkedList *p;
	p=head;
	while(head!=NULL) {
		p=head->next;
		free(head);
		head=p;
	}
	head=NULL;
}
