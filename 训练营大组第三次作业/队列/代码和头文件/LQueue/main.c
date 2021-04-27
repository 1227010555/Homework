#include "LQueue.h"

int main() {
	int choice=0;
	int t=0;
	LQueue A;
	LQueue *Q=&A;
	Q->front=Q->rear=NULL;
	int i;
	char c;
	float f;
	//用1使while死循环
	while(1) {
		printf("1.初始化队列\t\t2.销毁队列\n");
		printf("3.检查队列是否为空\t4.查看队头元素\n");
		printf("5.确定队列长度\t\t6.入队操作\n");
		printf("7.出队操作\t\t8.清空队列\n");
		printf("9.遍历函数操作\t\t10.退出\n");
		printf("输入数字\n");
		scanf("%d",&choice);
		switch(choice) {
			case 1:
				InitLQueue(Q);
				break;
			case 2:
				DestoryLQueue(Q);
				break;
			case 3:
				IsEmptyLQueue(Q);
				break;
			case 4:
				GetHeadLQueue(Q);
				break;
			case 5:
				LengthLQueue(Q);
				break;
			case 6 :
				if(Q->front==NULL) {
					printf("队列不存在\n");
					break;
				}
				while(1) {
					printf("入队类型:\n");
					printf("1.整型\t2.字符型\n");
					printf("3.浮点型\n");
					scanf("%d", &t);
					printf("入队数据\n");
					switch(t) {
						case 1: {
							scanf("%d",&i);
							Q->length=4;
							EnLQueue(Q,&i);
							Q->rear->datatype=t;
						}
						break;
						case 2: {
							getchar();
							scanf("%c",&c);
							Q->length=1;
							EnLQueue(Q,&c);
							Q->rear->datatype=t;
						}
						break;
						case 3: {
							scanf("%f",&f);
							Q->length=8;
							EnLQueue(Q,&f);
							Q->rear->datatype=t;
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
				break;
			case 7 :
				DeLQueue(Q);
				break;
			case 8 :
				ClearLQueue(Q);
				break;
			case 9 :
				TraverseLQueue(Q);
				break;
			case 10:
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
