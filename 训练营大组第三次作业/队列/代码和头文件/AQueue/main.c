#include "AQueue.h"

int main() {
	int choice=0;
	int t=0;
	AQueue A;
	AQueue *Q=&A;
	Q->front=-1;
	int *a=NULL;
	//��1ʹwhile��ѭ��
	while(1) {
		printf("1.��ʼ������\t\t2.���ٶ���\n");
		printf("3.�������Ƿ�����\t4.�������Ƿ�Ϊ��\n");
		printf("5.�鿴��ͷԪ��\t\t6.ȷ�����г���\n");
		printf("7.��Ӳ���\t\t8.���Ӳ���\n");
		printf("9.��ն���\t\t10.������������\n");
		printf("11.�˳�\n");
		printf("��������\n");
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
					printf("�������:\n");
					printf("1.int��\t2.char��\n");
					printf("3.float��\n");
					scanf("%d", &t);
					printf("�������\n");
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
							printf("���������������\n");
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
				printf("���������������\n");
				break;
		}
		sleep(1);
		system("cls");
		getchar();
	}
}
