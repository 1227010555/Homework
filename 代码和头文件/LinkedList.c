#include "LinkedList.h"

/**
 *  @name        : SinglyLinkedList *CreatSinglyLinkedList();
 *	@description : 创建单向链表
 *	@param		 : head(头指针);mid(前面的指针，用来开辟一块内存);back(后面的指针，用来指向新的内存);node(结点数);i(循环变量)
 *	@return		 : head
 *  @notice      : None
 */
SinglyLinkedList *CreatSinglyLinkedList() {
	SinglyLinkedList *head,*mid,*back;
	int node=0,i;
	//第一步:输入结点数
	do {
		printf("输入结点数\n");
		scanf("%d",&node);
		getchar();
		if(node<=0)
			printf("您输入的数据有误\n");
	} while(node<=0);
	//第二步：创建链表输入数据
	mid=back=head=(SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
	printf("输入数据\n");
	scanf("%d",&back->data);
	if(node!=1) {
		for(i=2; i<=node; i++) {
			mid=(SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
			back->next=mid;
			back=mid;
			printf("输入数据\n");
			scanf("%d",&back->data);
		}
	}
	back->next=NULL;
	//第三步：遍历链表
	SinglyPrint(head);
	printf("创建成功\n");
	return head;
}

/**
 *  @name        : DoublyLinkedList *CreatDoublyLinkedList();
 *	@description : 创建双向链表
 *	@param		 : head(头指针);mid(前面的指针，用来开辟一块内存);back(后面的指针，用来指向新的内存);node(结点数);i(循环变量)
 *	@return		 : head
 *  @notice      : None
 */
DoublyLinkedList *CreatDoublyLinkedList() {
	DoublyLinkedList *head,*mid,*back;
	int node=0,i;
	//第一步:输入结点数
	do {
		printf("输入结点数\n");
		scanf("%d",&node);
		getchar();
		if(node<=0)
			printf("您输入的数据有误\n");
	} while(node<=0);
	//第二步：创建链表输入数据
	mid=back=head=(DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
	printf("输入数据\n");
	scanf("%d",&back->data);
	mid->front=NULL;
	for(i=2; i<=node; i++) {
		mid=(DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
		back->next=mid;
		mid->front=back;
		back=mid;
		printf("输入数据\n");
		scanf("%d",&back->data);
	}
	back->next=NULL;
	//第三步：遍历链表
	DoublyPrint(head);
	printf("创建成功\n");
	return head;
}

/**
 *  @name        : SinglyLinkedList *ParitySwap(SinglyLinkedList *head);
 *	@description : 单链表奇偶调换
 *	@param		 : head(头指针);top(前面指针);mid(中间指针);back(后面指针);node(结点数);i(循环变量)
 *	@return		 : head
 *  @notice      : None
 */
SinglyLinkedList *ParitySwap(SinglyLinkedList *head) {
	int node=0,i;
	SinglyLinkedList *mid,*back,*top;
	//第一步：判断链表是否存在
	if(ExistLinkedList(head)==0)
		return;
	//第二步：数结点
	mid=back=top=head;
	node=CountNode(head);
	//第三步：根据结点奇偶分情况处理
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
 *	@description : 找到单链表的中点
 *	@param		 : head(头指针);p(用来指向中点的指针);node(结点数);i(循环变量)
 *	@return		 : head
 *  @notice      : None
 */
SinglyLinkedList *FindMidpoint(SinglyLinkedList *head) {
	int node=0,i;
	SinglyLinkedList *p;
	p=head;
	//第一步：判断链表是否存在
	if(ExistLinkedList(head)==0)
		return;
	//第二步：数结点
	node=CountNode(head);
	//第三步输出中点位置
	if(node%2==0) {
		for(i=1; i<node/2; i++)
			p=p->next;
		printf("第%d个结点:%d\n第%d个结点%d:\n",node/2,p->data,node/2+1,p->next->data);
	} else {
		for(i=0; i<node/2; i++)
			p=p->next;
		printf("第%d个结点:%d\n",node/2+1,p->data);
	}
	return head;
}

/**
 *  @name        : SinglyLinkedList *Circle(SinglyLinkedList *head);
 *	@description : 判断链表是否成环
 *	@param		 : head(头指针);fast(往前走两格);slow(往前走一个);temp(记录循环结点);i(循环变量)
 *	@return		 : head
 *  @notice      : None
 */
SinglyLinkedList *Circle(SinglyLinkedList *head) {
	SinglyLinkedList *fast,*slow,*temp;
	int i;
	fast=slow=head;
	//第一步：判断链表是否存在
	if(ExistLinkedList(head)==0)
		return;
	//第二步：让链表成环
	while(fast->next!=NULL)
		fast=fast->next;
	temp=fast;
	fast->next=head;
	//第三步：判断
	fast=head;
	for(fast,slow; fast->next!=NULL; fast=fast->next->next,slow=slow->next)
		if(fast==slow) {
			printf("链表成环\n");
			for(i=1; i<10; i++) {
				printf("第%d个结点数据:%d\n",i,fast->data);
				fast=fast->next;
			}
			temp->next=NULL;
			return head;
		}
	printf("链表不成环\n");
}

/**
 *  @name        : SinglyLinkedList *Reverse(SinglyLinkedList *head);
 *	@description : 反转链表
 *	@param		 : head(头指针);mid(前面的指针，用来一块内存);back(后面的指针，用来指向新的内存);node(结点数)
 *	@return		 : head
 *  @notice      : None
 */
SinglyLinkedList *Reverse(SinglyLinkedList *head) {
	SinglyLinkedList *mid,*back,*top;
	int node;
	//第一步：判断链表是否存在
	if(ExistLinkedList(head)==0)
		return;
	//第二步：反转
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
 *	@description : 遍历单向链表
 *	@param		 : p(遍历用的指针);i(循环变量)
 *	@return		 : none
 *  @notice      : None
 */
void SinglyPrint(SinglyLinkedList *p) {
	int i=1;
	while(p!=NULL) {
		printf("第%d个结点数据:%d\n",i++,p->data);
		p=p->next;
	}
	return;
}

/**
 *  @name        : void DoublyPrint(DoublyLinkedList *p);
 *	@description : 遍历双向链表
 *	@param		 : p(遍历用的指针);i(循环变量)
 *	@return		 : none
 *  @notice      : None
 */
void DoublyPrint(DoublyLinkedList *p) {
	int i=1;
	while(p->next!=NULL) {
		printf("第%d个结点数据:%d\n",i++,p->data);
		p=p->next;
	}
	printf("第%d个结点数据:%d\n",i++,p->data);
	while(p!=NULL) {
		printf("第%d个结点数据:%d\n",--i,p->data);
		p=p->front;
	}
	return;
}

/**
 *  @name        : int CountNode(SinglyLinkedList *head);
 *	@description : 数结点
 *	@param		 : head(头指针);node(结点数)
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
 *	@description : 链表是否存在
 *	@param		 : head(头指针)
 *	@return		 : 0
 *  @notice      : None
 */
SinglyLinkedList *ExistLinkedList(SinglyLinkedList *head) {
	if(head==NULL) {
		printf("链表不存在\n");
		return 0;
	}
}

/**
 *  @name        : int CountNode(SinglyLinkedList *head);
 *	@description : 释放链表内存
 *	@param		 : head(头指针);p(跑在头指针前面的指针)
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
