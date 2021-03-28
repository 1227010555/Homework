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
 *	@description : ������������
 *	@param		 : head(ͷָ��);mid(ǰ���ָ�룬��������һ���ڴ�);back(�����ָ�룬����ָ���µ��ڴ�);node(�����);i(ѭ������)
 *	@return		 : head
 *  @notice      : None
 */
extern SinglyLinkedList *CreatSinglyLinkedList();

/**
 *  @name        : DoublyLinkedList *CreatDoublyLinkedList();
 *	@description : ����˫������
 *	@param		 : head(ͷָ��);mid(ǰ���ָ�룬��������һ���ڴ�);back(�����ָ�룬����ָ���µ��ڴ�);node(�����);i(ѭ������)
 *	@return		 : head
 *  @notice      : None
 */
extern DoublyLinkedList *CreatDoublyLinkedList();

/**
 *  @name        : SinglyLinkedList *ParitySwap(SinglyLinkedList *head);
 *	@description : ��������ż����
 *	@param		 : head(ͷָ��);top(ǰ��ָ��);mid(�м�ָ��);back(����ָ��);node(�����);i(ѭ������)
 *	@return		 : head
 *  @notice      : None
 */
extern SinglyLinkedList *ParitySwap(SinglyLinkedList *head);

/**
 *  @name        : SinglyLinkedList *FindMidpoint(SinglyLinkedList *head);
 *	@description : �ҵ���������е�
 *	@param		 : head(ͷָ��);p(����ָ���е��ָ��);node(�����);i(ѭ������)
 *	@return		 : head
 *  @notice      : None
 */
extern SinglyLinkedList *FindMidpoint(SinglyLinkedList *head);

/**
 *  @name        : SinglyLinkedList *Circle(SinglyLinkedList *head);
 *	@description : �ж������Ƿ�ɻ�
 *	@param		 : head(ͷָ��);fast(��ǰ������);slow(��ǰ��һ��);temp(��¼ѭ�����);i(ѭ������)
 *	@return		 : head
 *  @notice      : None
 */
extern SinglyLinkedList *Circle(SinglyLinkedList *head);

/**
 *  @name        : SinglyLinkedList *Reverse(SinglyLinkedList *head);
 *	@description : ��ת����
 *	@param		 : head(ͷָ��);mid(ǰ���ָ�룬����һ���ڴ�);back(�����ָ�룬����ָ���µ��ڴ�);node(�����)
 *	@return		 : head
 *  @notice      : None
 */
extern SinglyLinkedList *Reverse(SinglyLinkedList *head);

/**
 *  @name        : void SinglyPrint(SinglyLinkedList *p);
 *	@description : ������������
 *	@param		 : p(�����õ�ָ��);i(ѭ������)
 *	@return		 : none
 *  @notice      : None
 */
extern void SinglyPrint(SinglyLinkedList *p);

/**
 *  @name        : void DoublyPrint(DoublyLinkedList *p);
 *	@description : ����˫������
 *	@param		 : p(�����õ�ָ��);i(ѭ������)
 *	@return		 : none
 *  @notice      : None
 */
extern void DoublyPrint(DoublyLinkedList *p);

/**
 *  @name        : int CountNode(SinglyLinkedList *head);
 *	@description : �����
 *	@param		 : head(ͷָ��);node(�����)
 *	@return		 : int
 *  @notice      : None
 */
extern int CountNode(SinglyLinkedList *head);

/**
 *  @name        : int CountNode(SinglyLinkedList *head);
 *	@description : �����Ƿ���� 
 *	@param		 : head(ͷָ��)
 *	@return		 : 0
 *  @notice      : None
 */
extern SinglyLinkedList *ExistLinkedList(SinglyLinkedList *head);

/**
 *  @name        : int CountNode(SinglyLinkedList *head);
 *	@description : �ͷ������ڴ� 
 *	@param		 : head(ͷָ��);p(����ͷָ��ǰ���ָ��) 
 *	@return		 : None 
 *  @notice      : None
 */
extern SinglyLinkedList *FreeLinkedList(SinglyLinkedList *head);
