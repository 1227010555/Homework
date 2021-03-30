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
	printf("初始化链表成功\n");
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
	printf("释放链表成功\n");
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
	//第一步：判断链表是否存在或链表仅有头结点
	if(ExistLinkedList==0)
		return;
	if(head->next==NULL) {
		printf("该链表仅有头结点，请在结点后面插入\n");
		return head;
	}
	//第二步：数结点
	node=CountNode(head);
	printf("该链表有%d个结点\n",node);
	//第三步：输入数据和插入到第几个结点并判断是否合法
	q=(DuLNode* )malloc(sizeof(DuLNode));
	printf("输入插入的数据:\n");
	scanf("%d",&q->data);
	do {
		printf("插入第几个结点之前:\n");
		scanf("%d",&n);
		if(n>node||n==1)
			printf("你输入的数据有误\n");
	} while(n>node||n==1);
	//第四步：插入
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
	//第一步：判断链表是否存在
	if(ExistLinkedList==0)
		return;
	//第二步：数结点
	node=CountNode(head);
	printf("该链表有%d个结点\n",node);
	//第三步：输入数据和插入到第几个结点并判断是否合法
	q=(DuLNode* )malloc(sizeof(DuLNode));
	printf("输入插入的数据:\n");
	scanf("%d",&q->data);
	do {
		printf("插入第几个结点之后:\n");
		scanf("%d",&n);
		if(n>node)
			printf("你输入的数据有误\n");
	} while(n>node);
	//第四步：插入
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
	//第一步：判断链表是否存在
	if(ExistLinkedList==0)
		return;
	//第二步：输入删除的数据
	printf("输入删除的数据:\n");
	scanf("%d",&e);
	//第三步：删除
	while(p->next->data!=e) {
		p=p->next;
		if(p->next==NULL) {
			printf("找不到需要删除的结点\n");
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
	//第一步：判断链表是否存在
	if(ExistLinkedList==0)
		return;
	//第二步：遍历链表（包括头结点）
	while(L!=NULL) {
		if(node==0) {
			printf("头结点数据：%d\n",L->data);
			node++;
		} else
			printf("第%d个结点数据：%d\n",++node,L->data);
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
		printf("链表不存在\n");
		return 0;
	}
}
