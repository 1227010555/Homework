/***************************************************************************************
 *	File Name				:	duLinkedList.h
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

#ifndef DULINKEDLIST_H_INCLUDED
#define DULINKEDLIST_H_INCLUDED

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

// define struct of linked list
typedef struct DuLNode {
	ElemType data;
  	struct DuLNode *prior,  *next;
} DuLNode, *DuLinkedList;

// define status
typedef enum Status {
	ERROR,
	SUCCESS,
} Status;


/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : void *InitList_DuL(DuLinkedList L)
 *	@description : initialize an empty linked list with only the head node
 *	@param		 : L(the head node)
 *	@return		 : DuLNode
 *  @notice      : None
 */
void *InitList_DuL(DuLinkedList L);

/**
 *  @name        : void *DestroyList_DuL(DuLinkedList L)
 *	@description : destroy a linked list
 *	@param		 : L(the head node)
 *	@return		 : status
 *  @notice      : None
 */
void *DestroyList_DuL(DuLinkedList L);

/**
 *  @name        : void *InsertBeforeList_DuL(DuLNode *p, DuLNode *q)
 *	@description : insert node q before node p
 *	@param		 : p, q
 *	@return		 : DuLNode
 *  @notice      : None
 */
void *InsertBeforeList_DuL(DuLNode *p, DuLNode *q);

/**
 *  @name        : void *InsertAfterList_DuL(DuLNode *p, DuLNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : DuLNode
 *  @notice      : None
 */
void *InsertAfterList_DuL(DuLNode *p, DuLNode *q);

/**
 *  @name        : void *DeleteList_DuL(DuLNode *p, ElemType e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : DuLNode
 *  @notice      : None
 */
void *DeleteList_DuL(DuLNode *p, ElemType e);

/**
 *  @name        : void TraverseList_DuL(DuLinkedList L)
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node)
 *	@return		 : None
 *  @notice      : None
 */
void TraverseList_DuL(DuLinkedList L);

/**
 *  @name        : int CountNode(DuLNode *head);
 *	@description : count node
 *	@param		 : head(the head node);node
 *	@return		 : int
 *  @notice      : None
 */
int CountNode(DuLNode *head);

/**
 *  @name        : DuLNode *ExistLinkedList(LNode *head);
 *	@description : linked list is or not exist 
 *	@param		 : head(the head node)
 *	@return		 : 0
 *  @notice      : None
 */
DuLNode *ExistLinkedList(DuLNode *head);


 /**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif
