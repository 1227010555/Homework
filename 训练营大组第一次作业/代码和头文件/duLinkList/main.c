#include "duLinkedList.h"

int main() {
	int choice;
	DuLNode *head=NULL;
	//��1ʹwhile��ѭ��
	while(1) {
		printf("1.��ʼ������\t\t2.�ͷ�����\n");
		printf("3.��ǰ�������\t4.�ں��������\n");
		printf("5.ɾ�����\t\t6.��������\n");
		printf("7.�˳�\n");
		printf("��������\n");
		scanf("%d",&choice);
		switch(choice) {
			case 1:
				head=InitList_DuL(head);
				break;
			case 2:
				head=DestroyList_DuL(head);
				break;
			case 3:
				head=InsertBeforeList_DuL(head,NULL);
				break;
			case 4:
				head=InsertAfterList_DuL(head,NULL);
				break;
			case 5: 
				head=DeleteList_DuL(head,0);
				break;
			case 6:
				TraverseList_DuL(head);
				break;
			case 7:
				return;
			default:
				printf("���������������\n");
		}
		sleep(1);
		system("cls");
		getchar();
	}
}


