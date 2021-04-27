#include "duLinkedList.h"

int main() {
	int choice;
	DuLNode *head=NULL;
	//用1使while死循环
	while(1) {
		printf("1.初始化链表\t\t2.释放链表\n");
		printf("3.在前面插入结点\t4.在后面插入结点\n");
		printf("5.删除结点\t\t6.遍历链表\n");
		printf("7.退出\n");
		printf("输入数字\n");
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
				printf("您输入的数据有误\n");
		}
		sleep(1);
		system("cls");
		getchar();
	}
}


