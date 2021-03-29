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
#ifndef LINKEDLIST_H_INCLUDED
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
typedef int ElemType;

// define struct of singly linked list
typedef struct LNode {
    ElemType  data;
    struct LNode *next;
}LNode, *LinkedList;

// define Status
typedef enum Status {
	ERROR,
	SUCCESS
} Status;

/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : void *InitList(LinkList *L);
 *	@description : initialize an empty linked list with only the head node without value
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : None
 */
void *InitList(LinkedList L);

/**
 *  @name        : void *DestroyList(LinkedList *L)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : None
 */
void *DestroyList(LinkedList L);

/**
 *  @name        : void *InsertList(LNode *p, LNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : LNode
 *  @notice      : None
 */
void *InsertList(LNode *p, LNode *q);

/**
 *  @name        : void *DeleteList(LNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : LNode
 *  @notice      : None
 */
void *DeleteList(LNode *p, ElemType *e);
 
 /**
 *  @name        : void TraverseList(LinkedList L)
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : None
 *  @notice      : None
 */
void TraverseList(LinkedList L);

/**
 *  @name        : Status SearchList(LinkedList L, ElemType e)
 *	@description : find the first node in the linked list according to e
 *	@param		 : L(the head node), e
 *	@return		 : Status
 *  @notice      : None
 */
Status SearchList(LinkedList L, ElemType *e);

 /**
 *  @name        : void *ReverseList(LinkedList *L)
 *	@description : reverse the linked list
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : None
 */
void *ReverseList(LinkedList L);

/**
 *  @name        : Status IsLoopList(LinkedList L)
 *	@description : judge whether the linked list is looped
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status IsLoopList(LinkedList L);

/**
 *  @name        : LNode *ReverseEvenList(LinkedList L)
 *	@description : reverse the nodes which value is an even number in the linked list, input: 1 -> 2 -> 3 -> 4  output: 2 -> 1 -> 4 -> 3
 *	@param		 : L(the head node)
 *	@return		 : LNode(the new head node)
 *  @notice      : choose to finish
 */
LNode *ReverseEvenList(LinkedList L);

/**
 *  @name        : LNode* FindMidNode(LinkedList *L)
 *	@description : find the middle node in the linked list
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : choose to finish
 */
LNode *FindMidNode(LinkedList L);

/**
 *  @name        : int CountNode(LNode *head);
 *	@description : count node
 *	@param		 : head(the head node);node
 *	@return		 : int
 *  @notice      : None
 */
int CountNode(LNode *head);

/**
 *  @name        : LNode *ExistLinkedList(LNode *head);
 *	@description : linked list is or not exist 
 *	@param		 : head(the head node)
 *	@return		 : 0
 *  @notice      : None
 */
LNode *ExistLinkedList(LNode *head);


 /**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif
