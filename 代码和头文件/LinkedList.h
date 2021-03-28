/***************************************************************************************
 *	File Name				:	linkedList.h
 *	CopyRight				:	2020 QG Studio
 *	SYSTEM					:   win10
 *	Create Data				:	2020.3.28
 *
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *
 *
 ***************************************************************************************/
 
/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#define LINKEDLIST_H_INCLUDED

/**************************************************************
*	Macro Define Section
**************************************************************/

#define OVERFLOW -1

/**************************************************************
*	Struct Define Section
**************************************************************/
 
#include <stdio.h>
#include <stdlib.h>

  
// define element type
typedef int element;

// define struct of singly linked list
typedef struct SinglyLinkedList {
    element  data;
    struct SinglyLinkedList *next;
}SinglyLinkedList;

// define struct of doubly linked list
typedef struct DoublyLinkedList {
    element  data;
    struct DoublyLinkedList *next,*front;
}DoublyLinkedList;

/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : SinglyLinkedList *CreatSinglyLinkedList();
 *	@description : 创建单向链表
 *	@param		 : head(头指针);mid(前面的指针，用来开辟一块内存);back(后面的指针，用来指向新的内存);node(结点数);i(循环变量)
 *	@return		 : head
 *  @notice      : None
 */
extern SinglyLinkedList *CreatSinglyLinkedList();

/**
 *  @name        : DoublyLinkedList *CreatDoublyLinkedList();
 *	@description : 创建双向链表
 *	@param		 : head(头指针);mid(前面的指针，用来开辟一块内存);back(后面的指针，用来指向新的内存);node(结点数);i(循环变量)
 *	@return		 : head
 *  @notice      : None
 */
extern DoublyLinkedList *CreatDoublyLinkedList();

/**
 *  @name        : SinglyLinkedList *ParitySwap(SinglyLinkedList *head);
 *	@description : 单链表奇偶调换
 *	@param		 : head(头指针);top(前面指针);mid(中间指针);back(后面指针);node(结点数);i(循环变量)
 *	@return		 : head
 *  @notice      : None
 */
extern SinglyLinkedList *ParitySwap(SinglyLinkedList *head);

/**
 *  @name        : SinglyLinkedList *FindMidpoint(SinglyLinkedList *head);
 *	@description : 找到单链表的中点
 *	@param		 : head(头指针);p(用来指向中点的指针);node(结点数);i(循环变量)
 *	@return		 : head
 *  @notice      : None
 */
extern SinglyLinkedList *FindMidpoint(SinglyLinkedList *head);

/**
 *  @name        : SinglyLinkedList *Circle(SinglyLinkedList *head);
 *	@description : 判断链表是否成环
 *	@param		 : head(头指针);fast(往前走两格);slow(往前走一个);temp(记录循环结点);i(循环变量)
 *	@return		 : head
 *  @notice      : None
 */
extern SinglyLinkedList *Circle(SinglyLinkedList *head);

/**
 *  @name        : SinglyLinkedList *Reverse(SinglyLinkedList *head);
 *	@description : 反转链表
 *	@param		 : head(头指针);mid(前面的指针，用来一块内存);back(后面的指针，用来指向新的内存);node(结点数)
 *	@return		 : head
 *  @notice      : None
 */
extern SinglyLinkedList *Reverse(SinglyLinkedList *head);

/**
 *  @name        : void SinglyPrint(SinglyLinkedList *p);
 *	@description : 遍历单向链表
 *	@param		 : p(遍历用的指针);i(循环变量)
 *	@return		 : none
 *  @notice      : None
 */
extern void SinglyPrint(SinglyLinkedList *p);

/**
 *  @name        : void DoublyPrint(DoublyLinkedList *p);
 *	@description : 遍历双向链表
 *	@param		 : p(遍历用的指针);i(循环变量)
 *	@return		 : none
 *  @notice      : None
 */
extern void DoublyPrint(DoublyLinkedList *p);

/**
 *  @name        : int CountNode(SinglyLinkedList *head);
 *	@description : 数结点
 *	@param		 : head(头指针);node(结点数)
 *	@return		 : int
 *  @notice      : None
 */
extern int CountNode(SinglyLinkedList *head);

/**
 *  @name        : int CountNode(SinglyLinkedList *head);
 *	@description : 链表是否存在 
 *	@param		 : head(头指针)
 *	@return		 : 0
 *  @notice      : None
 */
extern SinglyLinkedList *ExistLinkedList(SinglyLinkedList *head);

/**
 *  @name        : int CountNode(SinglyLinkedList *head);
 *	@description : 释放链表内存 
 *	@param		 : head(头指针);p(跑在头指针前面的指针) 
 *	@return		 : None 
 *  @notice      : None
 */
extern SinglyLinkedList *FreeLinkedList(SinglyLinkedList *head);
