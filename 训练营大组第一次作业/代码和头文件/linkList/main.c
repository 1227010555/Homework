#include "linkedList.h"

int main() {
	int choice;
	LNode *head=NULL;
	//用1使while死循环
	while(1) {
		printf("1.初始化链表\t\t2.释放链表\n");
		printf("3.插入结点\t\t4.删除结点\n");
		printf("5.遍历链表\t\t6.查找结点\n");
		printf("7.反转链表\t\t8.链表是否成环\n");
		printf("9.奇偶反转\t\t10.找链表中点\n");
		printf("11.退出\n");
		printf("输入数字\n");
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
				printf("您输入的数据有误\n");
		}
		sleep(1);
		system("cls");
		getchar();
	}
}


