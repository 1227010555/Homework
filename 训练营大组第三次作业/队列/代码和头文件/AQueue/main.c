#include "AQueue.h"

int main() {
	int choice=0;
	int t=0;
	AQueue A;
	AQueue *Q=&A;
	Q->front=-1;
	int *a=NULL;
	//用1使while死循环
	while(1) {
		printf("1.初始化队列\t\t2.销毁队列\n");
		printf("3.检查队列是否已满\t4.检查队列是否为空\n");
		printf("5.查看队头元素\t\t6.确定队列长度\n");
		printf("7.入队操作\t\t8.出队操作\n");
		printf("9.清空队列\t\t10.遍历函数操作\n");
		printf("11.退出\n");
		printf("输入数字\n");
		scanf("%d",&choice);
		switch(choice) {
			case 1:
				InitAQueue(Q);
				break;
			case 2:
				DestoryAQueue(Q);
				break;
			case 3:
				IsFullAQueue(Q);
				break;
			case 4:
				IsEmptyAQueue(Q);
				break;
			case 5:
				GetHeadAQueue(Q,NULL);
				break;
			case 6:
				LengthAQueue(Q);
				break;
			case 7 : {
				while(1) {
					printf("入队类型:\n");
					printf("1.int型\t2.char型\n");
					printf("3.float型\n");
					scanf("%d", &t);
					printf("入队数据\n");
					switch(t) {
						case 1: {
							int a;
							scanf("%d",&a);
							Q->datatype[Q->rear]=t;
							EnAQueue(Q, &a);
						}
						break ;
						case 2: {
							char a;
							getchar();
							scanf("%c",&a);
							Q->datatype[Q->rear]=t;
							EnAQueue(Q,&a);
						}
						break ;
						case 3: {
							float a ;
							scanf("%f",&a);
							Q->datatype[Q->rear]=t;
							EnAQueue(Q, &a);
						}
						break;
						default: {
							printf("您输入的数据有误\n");
							break;
						}
					}
					if(t==1||t==2||t==3)
						break;
				}
			}
			break;
			case 8 :
				DeAQueue(Q);
				break;
			case 9 :
				ClearAQueue(Q);
				break;
			case 10 :
				TraverseAQueue(Q);
				break;
			case 11:
				return;
			default:
				printf("您输入的数据有误\n");
				break;
		}
		sleep(1);
		system("cls");
		getchar();
	}
}
