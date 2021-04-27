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
	//��1ʹwhile��ѭ��
	while(1) {
		printf("1.��ʼ������\t\t2.���ٶ���\n");
		printf("3.�������Ƿ�Ϊ��\t4.�鿴��ͷԪ��\n");
		printf("5.ȷ�����г���\t\t6.��Ӳ���\n");
		printf("7.���Ӳ���\t\t8.��ն���\n");
		printf("9.������������\t\t10.�˳�\n");
		printf("��������\n");
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
					printf("���в�����\n");
					break;
				}
				while(1) {
					printf("�������:\n");
					printf("1.����\t2.�ַ���\n");
					printf("3.������\n");
					scanf("%d", &t);
					printf("�������\n");
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
							printf("���������������\n");
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
				printf("���������������\n");
				break;
		}
		sleep(1);
		system("cls");
		getchar();
	}
}
