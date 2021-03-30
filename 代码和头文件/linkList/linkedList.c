#include "linkedList.h"

/**
 *  @name        : void *InitList(LinkList L);
 *	@description : initialize an empty linked list with only the head node without value
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : None
 */
void *InitList(LinkedList L) {
	L=(LNode* )malloc(sizeof(LNode));
	L->next=NULL;
	printf("��ʼ������ɹ�\n");
	return L;
}

/**
 *  @name        : void *DestroyList(LinkedList L)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : None
 */
void *DestroyList(LinkedList L) {
	LinkedList p;
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
 *  @name        : void *InsertList(LNode *p, LNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : LNode
 *  @notice      : None
 */
void *InsertList(LNode *p, LNode *q) {
	LNode *pNext,*head;
	int node,n=0;
	head=p;
	//��һ�����ж������Ƿ����
	if(head==NULL) {
		printf("��������\n");
		return;
	}
	//�ڶ����������
	node=CountNode(head);
	printf("��������%d�����\n",node);
	//���������������ݺͲ��뵽�ڼ�����㲢�ж��Ƿ�Ϸ�
	q=(LNode* )malloc(sizeof(LNode));
	printf("������������:\n");
	scanf("%d",&q->data);
	if(head->next==NULL) {
		head->next=q;
		q->next=NULL;
		TraverseList(head);
		return head;
	}
	do {
		printf("����ڼ������֮��:\n");
		scanf("%d",&n);
		if(n>node)
			printf("���������������\n");
	} while(n>node);
	//���Ĳ�������
	for(n; n>0; n--)
		p=p->next;
	if(p->next==NULL) {
		p->next=q;
		q->next=NULL;
	} else {
		pNext=p->next;
		p->next=q;
		q->next=pNext;
	}
	TraverseList(head);
	return head;
}

/**
 *  @name        : void *DeleteList(LNode *p, ElemType e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : LNode
 *  @notice      : None
 */
void *DeleteList(LNode *p, ElemType e) {
	LNode *head,*pNext;
	head=p;
	//��һ�����ж������Ƿ����
	if(ExistLinkedList(head)==0)
		return head;
	//�ڶ���������ɾ��������
	printf("����ɾ��������:\n");
	scanf("%d",&e);
	//��������ɾ��
	pNext=p->next;
	while(pNext->data!=e) {
		pNext=pNext->next;
		p=p->next;
		if(pNext==NULL) {
			printf("�Ҳ�����Ҫɾ���Ľ��\n");
			return head;
		}
	}
	if(pNext->next==NULL)
		p->next=NULL;
	else {
		pNext=pNext->next;
		p->next=pNext;
	}
	TraverseList(head);
	return head;
}

/**
 *  @name        : void TraverseList(LinkedList L)
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : None
 *  @notice      : None
 */
void TraverseList(LinkedList L) {
	int node=0;
	//��һ�����ж������Ƿ����
	if(ExistLinkedList(L)==0)
		return;
	//�ڶ�������������������ͷ��㣩
	L = L->next;
	while(L!=NULL) {
		printf("��%d��������ݣ�%d\n",++node,L->data);
		L = L->next;
	}
}

/**
 *  @name        : Status SearchList(LinkedList L, ElemType e)
 *	@description : find the first node in the linked list according to e
 *	@param		 : L(the head node), e
 *	@return		 : Status
 *  @notice      : None
 */
Status SearchList(LinkedList L, ElemType e) {
	int node=0;
	//��һ�����ж������Ƿ����
	if(ExistLinkedList(L)==0)
		return;
	//�ڶ�����������ҵ�����
	printf("������ҵ�����:\n");
	scanf("%d",&e);
	//��������ɾ��
	while(L->data!=e) {
		L=L->next;
		node++;
		if(L==NULL) {
			printf("�Ҳ�����Ҫ���ҵĽ��\n");
			return;
		}
	}
	printf("��%d��������ݣ�%d\n",node,L->data);
}

/**
 *  @name        : Status ReverseList(LinkedList L)
 *	@description : reverse the linked list
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : None
 */
void *ReverseList(LinkedList L) {
	LNode *mid,*back,*top,*head;
	int node;
	head=L;
	//��һ�����ж������Ƿ����
	if(ExistLinkedList(head)==0)
		return head;
	//�ڶ�������ת
	if (head->next==NULL||L->next==NULL) {
		return head;
	} else {
		L=L->next;
		back=NULL;
		mid=L;
		top=L->next;
		while(1) {
			mid->next=back;
			if (top==NULL) {
				break;
			}
			back=mid;
			mid=top;
			top=top->next;
		}
		head->next=mid;
			TraverseList(head);
	return head;
	}
}

/**
 *  @name        : Status IsLoopList(LinkedList L)
 *	@description : judge whether the linked list is looped
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status IsLoopList(LinkedList L) {
	LNode *fast,*slow,*temp;
	int i;
	fast=slow=L;
	//��һ�����ж������Ƿ����
	if(ExistLinkedList(L)==0)
		return;
	//�ڶ�����������ɻ�
	while(fast->next!=NULL)
		fast=fast->next;
	temp=fast;
	fast->next=L->next;
	//���������ж�
	fast=L->next;
	for(fast,slow; fast->next!=NULL; fast=fast->next->next,slow=slow->next)
		if(fast==slow) {
			printf("����ɻ�\n");
			for(i=1; i<10; i++) {
				printf("��%d���������:%d\n",i,fast->data);
				fast=fast->next;
			}
			temp->next=NULL;
			return;
		}
	printf("�����ɻ�\n");
}

/**
 *  @name        : LNode *ReverseEvenList(LinkedList L)
 *	@description : reverse the nodes which value is an even number in the linked list, input: 1 -> 2 -> 3 -> 4  output: 2 -> 1 -> 4 -> 3
 *	@param		 : L(the head node)
 *	@return		 : LNode(the new head node)
 *  @notice      : choose to finish
 */
LNode *ReverseEvenList(LinkedList L) {
	int node=0,i;
	LNode *mid,*back,*top,*head,*temp;
	head=L;
	temp=head->next->next;
	//��һ�����ж������Ƿ����
	if(ExistLinkedList(L)==0)
		return;
	//�ڶ����������
	node=CountNode(L);
	//�����������ݽ����ż���������
	L=L->next;
	mid=back=top=L;
	if(node==1) {
		TraverseList(head);
		return head;
	}
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
				head->next=temp;
				TraverseList(head);
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
				top->next=NULL;
				head->next=temp;
				TraverseList(head);
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
 *  @name        : LNode *FindMidNode(LinkedList L)
 *	@description : find the middle node in the linked list
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : choose to finish
 */
LNode *FindMidNode(LinkedList L) {
	int node=0,i;
	LNode *p;
	p=L;
	p=p->next;
	//��һ�����ж������Ƿ����
	if(ExistLinkedList(L)==0)
		return;
	//�ڶ����������
	node=CountNode(L);
	//����������е�λ��
	if(node%2==0) {
		for(i=1; i<node/2; i++)
			p=p->next;
		printf("��%d�����:%d\n��%d�����:%d\n",node/2,p->data,node/2+1,p->next->data);
	} else {
		for(i=0; i<node/2; i++)
			p=p->next;
		printf("��%d�����:%d\n",node/2+1,p->data);
	}
}

/**
 *  @name        : int CountNode(LNode *head);
 *	@description : count node
 *	@param		 : head(the head node);node
 *	@return		 : int
 *  @notice      : None
 */
int CountNode(LNode *head) {
	int node=0;
	while(head->next!=NULL) {
		node++;
		head=head->next;
	}
	return node;
}

/**
 *  @name        : LNode *ExistLinkedList(LNode *head);
 *	@description : linked list is or not exist
 *	@param		 : head(the head node)
 *	@return		 : 0
 *  @notice      : None
 */
LNode *ExistLinkedList(LNode *head) {
	if(head==NULL||head->next==NULL) {
		printf("��������\n");
		return 0;
	}
}


