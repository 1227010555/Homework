#include "duLinkedList.h"

/**
 *  @name        : void *InitList_DuL(DuLinkedList L)
 *	@description : initialize an empty linked list with only the head node
 *	@param		 : L(the head node)
 *	@return		 : DuLNode
 *  @notice      : None
 */
void *InitList_DuL(DuLinkedList L) {
	L=(DuLNode* )malloc(sizeof(DuLNode));
	L->next=NULL;
	L->prior=NULL;
	printf("��ʼ������ɹ�\n");
	return L;

}

/**
 *  @name        : void *DestroyList_DuL(DuLinkedList L)
 *	@description : destroy a linked list
 *	@param		 : L(the head node)
 *	@return		 : status
 *  @notice      : None
 */
void *DestroyList_DuL(DuLinkedList L) {
	DuLinkedList p;
	p=L;
	while(L!=NULL) {
		p=L->next;
		free(L);
		L=p;
	}
	L=NULL;
	printf("�ͷ�����ɹ�\n");
	return L;
}

/**
 *  @name        : void *InsertBeforeList_DuL(DuLNode *p, DuLNode *q)
 *	@description : insert node q before node p
 *	@param		 : p, q
 *	@return		 : DuLNode
 *  @notice      : None
 */
void *InsertBeforeList_DuL(DuLNode *p, DuLNode *q) {
	DuLNode *pPrior,*head;
	int node,n=0;
	head=p;
	//��һ�����ж������Ƿ���ڻ��������ͷ���
	if(ExistLinkedList==0)
		return;
	if(head->next==NULL) {
		printf("���������ͷ��㣬���ڽ��������\n");
		return head;
	}
	//�ڶ����������
	node=CountNode(head);
	printf("��������%d�����\n",node);
	//���������������ݺͲ��뵽�ڼ�����㲢�ж��Ƿ�Ϸ�
	q=(DuLNode* )malloc(sizeof(DuLNode));
	printf("������������:\n");
	scanf("%d",&q->data);
	do {
		printf("����ڼ������֮ǰ:\n");
		scanf("%d",&n);
		if(n>node||n==1)
			printf("���������������\n");
	} while(n>node||n==1);
	//���Ĳ�������
	for(n; n>1; n--)
		p=p->next;
	pPrior=p->prior;
	pPrior->next=q;
	q->prior=pPrior;
	p->prior=q;
	q->next=p;
	TraverseList_DuL(head);
	return head;
}

/**
 *  @name        : void *InsertAfterList_DuL(DuLNode *p, DuLNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : DuLNode
 *  @notice      : None
 */
void *InsertAfterList_DuL(DuLNode *p, DuLNode *q) {
	DuLNode *pNext,*head;
	int node,n=0;
	head=p;
	//��һ�����ж������Ƿ����
	if(ExistLinkedList==0)
		return;
	//�ڶ����������
	node=CountNode(head);
	printf("��������%d�����\n",node);
	//���������������ݺͲ��뵽�ڼ�����㲢�ж��Ƿ�Ϸ�
	q=(DuLNode* )malloc(sizeof(DuLNode));
	printf("������������:\n");
	scanf("%d",&q->data);
	do {
		printf("����ڼ������֮��:\n");
		scanf("%d",&n);
		if(n>node)
			printf("���������������\n");
	} while(n>node);
	//���Ĳ�������
	for(n; n>1; n--)
		p=p->next;
	if(p->next==NULL) {
		p->next=q;
		q->prior=p;
		q->next=NULL;
	} else {
		pNext=p->next;
		p->next=q;
		q->prior=p;
		pNext->prior=q;
		q->next=pNext;
	}
	TraverseList_DuL(head);
	return head;
}

/**
 *  @name        : void *DeleteList_DuL(DuLNode *p, ElemType e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : DuLNode
 *  @notice      : None
 */
void *DeleteList_DuL(DuLNode *p, ElemType e) {
	DuLNode *head,*pNext;
	head=p;
	//��һ�����ж������Ƿ����
	if(ExistLinkedList==0)
		return;
	//�ڶ���������ɾ��������
	printf("����ɾ��������:\n");
	scanf("%d",&e);
	//��������ɾ��
	while(p->next->data!=e) {
		p=p->next;
		if(p->next==NULL) {
			printf("�Ҳ�����Ҫɾ���Ľ��\n");
			return head;
		}
	}
	if(p->next->next==NULL)
		p->next=NULL;
	else{
		pNext=p->next->next;
		p->next=pNext;
		pNext->prior=p;
}
	TraverseList_DuL(head);
	return head;
}

/**
 *  @name        : void TraverseList_DuL(DuLinkedList L)
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : Status
 *  @notice      : None
 */
void TraverseList_DuL(DuLinkedList L) {
	int node=0;
	//��һ�����ж������Ƿ����
	if(ExistLinkedList==0)
		return;
	//�ڶ�����������������ͷ��㣩
	while(L!=NULL) {
		if(node==0) {
			printf("ͷ������ݣ�%d\n",L->data);
			node++;
		} else
			printf("��%d��������ݣ�%d\n",++node,L->data);
		L = L->next;
	}
}

/**
 *  @name        : int CountNode(DuLNode *head);
 *	@description : count node
 *	@param		 : head(the head node);node
 *	@return		 : int
 *  @notice      : None
 */
int CountNode(DuLNode *head) {
	int node=0;
	while(head!=NULL) {
		node++;
		head=head->next;
	}
	return node;
}

/**
 *  @name        : DuLNode *ExistLinkedList(DuLNode *head);
 *	@description : linked list is or not exist
 *	@param		 : head(the head node)
 *	@return		 : 0
 *  @notice      : None
 */
DuLNode *ExistLinkedList(DuLNode *head) {
	if(head==NULL) {
		printf("��������\n");
		return 0;
	}
}
