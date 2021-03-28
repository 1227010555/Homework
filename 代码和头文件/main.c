#include "LinkedList.h"

int main() {
	char choice;
	SinglyLinkedList *singlyHead=NULL;
	DoublyLinkedList *doublyHead=NULL;
	//用1使while死循环
	while(1) {
		printf("\n1.创建单向链表\n");
		printf("2.创建双向链表\n");
		printf("3.单链表奇偶调换\n");
		printf("4.找到单链表的中点\n");
		printf("5.判断链表是否成环\n");
		printf("6.反转链表\n");
		printf("7.退出\n");
		printf("输入数字\n");
		choice=getchar();
		switch(choice) {
			case'1':
				printf("1.创建单向链表\n");
				singlyHead=CreatSinglyLinkedList();
				break;
			case'2':
				printf("2.创建双向链表\n");
				doublyHead=CreatDoublyLinkedList();
				break;
			case'3':
				printf("3.单链表奇偶调换\n");
				singlyHead=ParitySwap(singlyHead);
				break;
			case'4':
				printf("4.找到单链表的中点\n");
				singlyHead=FindMidpoint(singlyHead); 
				break;
			case'5':
				printf("5.判断链表是否成环\n");
				singlyHead=Circle(singlyHead);
				break;
			case'6':
				printf("6.反转链表\n");
				singlyHead=Reverse(singlyHead); 
				break;
			case'7':
				printf("7.退出\n");
				FreeLinkedList(singlyHead);
				FreeLinkedList(doublyHead);
				return;
			default:
				printf("您输入的数据有误");
				;
		}
		choice=getchar();
	}
}


