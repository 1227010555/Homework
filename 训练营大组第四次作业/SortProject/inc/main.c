#include "qgsort.h"

clock_t start, stop;
double useTime;

int main() {
    int choice=0,state=0,count=0,N=0,i=0;
    while(1) {
    	//ѡ��������� 
        while(state==0) {
            printf("1.���10000������\t2.���50000������\n");
            printf("3.���200000������\t4.100������100����\n");
            printf("5.500������100����\t6.2000������100����\n");
            printf("7.�˳�\n");
            scanf("%d",&choice);
            switch(choice) {
                case 1:
                    count=10000;
                    N=1;
                    state=1;
                    break;
                case 2:
                    count=50000;
                    N=1;
                    state=1;
                    break;
                case 3:
                    count=200000;
                    N=1;
                    state=1;
                    break;
                case 4:
                    count=100;
                    N=100;
                    state=1;
                    break;
                case 5:
                    count=100;
                    N=500;
                    state=1;
                    break;
                case 6:
                    count=100;
                    N=2000;
                    state=1;
                    break;
                case 7:
                    return;
            }
            sleep(1);
            system("cls");
            getchar();
        }
        //�������������ļ� 
        FILE *fp=fopen( "datafile.txt", "w" );
        for(i=0; i<count; i++)
            fprintf(fp,"%d\n",rand()%100+1);
        fclose(fp);
        int data[count];
        int *dataPoint=data;
        //ѡ�����򷽷� 
        while(state==1) {
            printf("1.��������\t2.�鲢����\n");
            printf("3.���ŵݹ��\t4.��������\n");
            printf("5.������������\t6.���ŷǵݹ��\n");
            printf("7.������һ��\t8.�˳�\n");
            scanf("%d",&choice);
            FILE *fi=fopen( "datafile.txt","r" );
            switch(choice) {
                case 1:
                    for(i=0; !feof(fi); i++)
                        fscanf(fi,"%d",&data[i]);
                    start=clock();
                    for(i=0; i<N; i++)
                        insertSort(dataPoint,count);
                    stop=clock();
                    useTime=(double)(stop-start)/CLK_TCK;
                    printf("����������%d������%d����������ʱ��%f\n",N,count,useTime);
                    printf("���ݴ�����insertSort.txt\n");
                    break;
                case 2:
                    for(i=0; !feof(fi); i++)
                        fscanf(fi,"%d",&data[i]);
                    start=clock();
                    for(i=0; i<N; i++)
                        MergeSort(dataPoint,0,count-1,0);
                    stop=clock();
                    useTime=(double)(stop-start)/CLK_TCK;
                    printf("�鲢������%d������%d����������ʱ��%f\n",N,count,useTime);
                    printf("���ݴ�����MergeSort.txt\n");
                    break;
                case 3:
                    for(i=0; !feof(fi); i++)
                        fscanf(fi,"%d",&data[i]);
                    start=clock();
                    for(i=0; i<N; i++)
                        QuickSort_Recursion(dataPoint,0,count-1,0);
                    stop=clock();
                    useTime=(double)(stop-start)/CLK_TCK;
                    printf("���ŵݹ���%d������%d����������ʱ��%f\n",N,count,useTime);
                    printf("���ݴ�����QuickSort_Recursion.txt\n");
                    break;
                case 4:
                    for(i=0; !feof(fi); i++)
                        fscanf(fi,"%d",&data[i]);
                    start=clock();
                    for(i=0; i<N; i++)
                        CountSort(dataPoint,count,100);
                    stop=clock();
                    useTime=(double)(stop-start)/CLK_TCK;
                    printf("����������%d������%d����������ʱ��%f\n",N,count,useTime);
                    printf("���ݴ�����CountSort.txt\n");
                    break;
                case 5:
                    for(i=0; !feof(fi); i++)
                        fscanf(fi,"%d",&data[i]);
                    start=clock();
                    for(i=0; i<N; i++)
                        RadixCountSort(dataPoint,count);
                    stop=clock();
                    useTime=(double)(stop-start)/CLK_TCK;
                    printf("����������%d������%d����������ʱ��%f\n",N,count,useTime);
                    printf("���ݴ�����RadixCountSort.txt\n");
                    break;
                case 6:
                    printf("δʵ��\n");
                    break;
                case 7:
                    state=0;
                    break;
                case 8:
                    fclose(fi);
                    return;
            }
            sleep(1);
            system("cls");
            getchar();
            fclose(fi);
        }
    }
}
