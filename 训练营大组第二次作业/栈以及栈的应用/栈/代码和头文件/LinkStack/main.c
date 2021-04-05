#include "LinkStack.h"

int main() {
	int choice=0;
	LinkStack *head=NULL;
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
				printf("您输入的数据有误\n");
		}
		getchar();
	}
}
