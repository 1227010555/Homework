#include "LinkStack.h"

int main() {
	int choice=0;
	LinkStack *head=NULL;
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
				head=initLStack(head);
				break;
			case 2:
				isEmptyLStack(head);
				break;
			case 3:
				getTopLStack(head,NULL);
				break;
			case 4:
				head=clearLStack(head);
				break;
			case 5:
				head=destroyLStack(head);
				break;
			case 6:
				LStackLength(head,0);
				break;
			case 7 :
				head=pushLStack(head,0);
				break;
			case 8 :
				head=popLStack(head,0);
				break;
			case 9:
				return;
			default:
				printf("���������������\n");
		}
		getchar();
	}
}
