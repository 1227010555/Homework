#include "SqStack.h"

int main() {
	int choice=0;
	SqStack Sq;
	SqStack *head=&Sq;
	head->top=-1;
	//��1ʹwhile��ѭ��
	while(1) {
		printf("\n1.��ʼ��ջ\t\t2.�ж�ջ�Ƿ�Ϊ��\n");
		printf("3.�õ�ջ��Ԫ��\t\t4.���ջ\n");
		printf("5.����ջ\t\t6.���ջ����\n");
		printf("7.��ջ\t\t\t8.��ջ\n");
		printf("9.�˳�\n");
		printf("��������\n");
		scanf("%d",&choice);
		switch(choice) {
			case 1:
				head=initStack(head,0);
				break;
			case 2:
				isEmptyStack(head);
				break;
			case 3:
				getTopStack(head,NULL);
				break;
			case 4:
				head=clearStack(head);
				break;
			case 5:
				head=destroyStack(head);
				break;
			case 6:
				stackLength(head,0);
				break;
			case 7 :
				head=pushStack(head,0);
				break;
			case 8 :
				head=popStack(head,0);
				break;
			case 9:
				return;
			default:
				printf("���������������\n");
		}
		sleep(1);
		system("cls");
		getchar();
	}
}
