#include "LinkedList.h"

int main() {
	char choice;
	SinglyLinkedList *singlyHead=NULL;
	DoublyLinkedList *doublyHead=NULL;
	//��1ʹwhile��ѭ��
	while(1) {
		printf("\n1.������������\n");
		printf("2.����˫������\n");
		printf("3.��������ż����\n");
		printf("4.�ҵ���������е�\n");
		printf("5.�ж������Ƿ�ɻ�\n");
		printf("6.��ת����\n");
		printf("7.�˳�\n");
		printf("��������\n");
		choice=getchar();
		switch(choice) {
			case'1':
				printf("1.������������\n");
				singlyHead=CreatSinglyLinkedList();
				break;
			case'2':
				printf("2.����˫������\n");
				doublyHead=CreatDoublyLinkedList();
				break;
			case'3':
				printf("3.��������ż����\n");
				singlyHead=ParitySwap(singlyHead);
				break;
			case'4':
				printf("4.�ҵ���������е�\n");
				singlyHead=FindMidpoint(singlyHead); 
				break;
			case'5':
				printf("5.�ж������Ƿ�ɻ�\n");
				singlyHead=Circle(singlyHead);
				break;
			case'6':
				printf("6.��ת����\n");
				singlyHead=Reverse(singlyHead); 
				break;
			case'7':
				printf("7.�˳�\n");
				FreeLinkedList(singlyHead);
				FreeLinkedList(doublyHead);
				return;
			default:
				printf("���������������");
				;
		}
		choice=getchar();
	}
}


