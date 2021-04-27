#include "linkedList.h"

int main() {
	int choice;
	LNode *head=NULL;
	//��1ʹwhile��ѭ��
	while(1) {
		printf("1.��ʼ������\t\t2.�ͷ�����\n");
		printf("3.������\t\t4.ɾ�����\n");
		printf("5.��������\t\t6.���ҽ��\n");
		printf("7.��ת����\t\t8.�����Ƿ�ɻ�\n");
		printf("9.��ż��ת\t\t10.�������е�\n");
		printf("11.�˳�\n");
		printf("��������\n");
		scanf("%d",&choice);
		switch(choice) {
			case 1:
				head=InitList(head);
				break;
			case 2:
				head=DestroyList(head);
				break;
			case 3:
				head=InsertList(head,NULL);
				break;
			case 4:
				head=DeleteList(head,0);
				break;
			case 5: 
				TraverseList(head);
				break;
			case 6:
				SearchList(head,0);
				break;
			case 7:
				head=ReverseList(head);
				break;
			case 8:
				IsLoopList(head);
				break;
			case 9:
				head=ReverseEvenList(head);
				break;
			case 10:
				FindMidNode(head);
				break;
			case 11:
				return;
			default:
				printf("���������������\n");
		}
		sleep(1);
		system("cls");
		getchar();
	}
}


