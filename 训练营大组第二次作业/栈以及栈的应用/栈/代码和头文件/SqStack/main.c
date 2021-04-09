#include "SqStack.h"

int main() {
	int choice=0;
	SqStack Sq;
	SqStack *head=&Sq;
	head->top=-1;
	//用1使while死循环
	while(1) {
		printf("\n1.初始化栈\t\t2.判断栈是否为空\n");
		printf("3.得到栈顶元素\t\t4.清空栈\n");
		printf("5.销毁栈\t\t6.检测栈长度\n");
		printf("7.入栈\t\t\t8.出栈\n");
		printf("9.退出\n");
		printf("输入数字\n");
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
				printf("您输入的数据有误\n");
		}
		sleep(1);
		system("cls");
		getchar();
	}
}
