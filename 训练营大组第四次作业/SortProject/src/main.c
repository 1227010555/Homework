#include "qgsort.h"

clock_t start, stop;
double useTime;

int main() {
    int choice=0,state=0,count=0,N=0,i=0;
    while(1) {
    	//选择测试数据 
        while(state==0) {
            printf("1.输出10000个数字\t2.输出50000个数字\n");
            printf("3.输出200000个数字\t4.100个数组100个数\n");
            printf("5.500个数组100个数\t6.2000个数组100个数\n");
            printf("7.退出\n");
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
        //创建测试数据文件 
        FILE *fp=fopen( "datafile.txt", "w" );
        for(i=0; i<count; i++)
            fprintf(fp,"%d\n",rand()%100+1);
        fclose(fp);
        int data[count];
        int *dataPoint=data;
        //选择排序方法 
        while(state==1) {
            printf("1.插入排序\t2.归并排序\n");
            printf("3.快排递归版\t4.计数排序\n");
            printf("5.基数计数排序\t6.快排非递归版\n");
            printf("7.返回上一级\t8.退出\n");
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
                    printf("插入排序在%d个数组%d个数据所用时间%f\n",N,count,useTime);
                    printf("数据储存在insertSort.txt\n");
                    break;
                case 2:
                    for(i=0; !feof(fi); i++)
                        fscanf(fi,"%d",&data[i]);
                    start=clock();
                    for(i=0; i<N; i++)
                        MergeSort(dataPoint,0,count-1,0);
                    stop=clock();
                    useTime=(double)(stop-start)/CLK_TCK;
                    printf("归并排序在%d个数组%d个数据所用时间%f\n",N,count,useTime);
                    printf("数据储存在MergeSort.txt\n");
                    break;
                case 3:
                    for(i=0; !feof(fi); i++)
                        fscanf(fi,"%d",&data[i]);
                    start=clock();
                    for(i=0; i<N; i++)
                        QuickSort_Recursion(dataPoint,0,count-1,0);
                    stop=clock();
                    useTime=(double)(stop-start)/CLK_TCK;
                    printf("快排递归在%d个数组%d个数据所用时间%f\n",N,count,useTime);
                    printf("数据储存在QuickSort_Recursion.txt\n");
                    break;
                case 4:
                    for(i=0; !feof(fi); i++)
                        fscanf(fi,"%d",&data[i]);
                    start=clock();
                    for(i=0; i<N; i++)
                        CountSort(dataPoint,count,100);
                    stop=clock();
                    useTime=(double)(stop-start)/CLK_TCK;
                    printf("计数排序在%d个数组%d个数据所用时间%f\n",N,count,useTime);
                    printf("数据储存在CountSort.txt\n");
                    break;
                case 5:
                    for(i=0; !feof(fi); i++)
                        fscanf(fi,"%d",&data[i]);
                    start=clock();
                    for(i=0; i<N; i++)
                        RadixCountSort(dataPoint,count);
                    stop=clock();
                    useTime=(double)(stop-start)/CLK_TCK;
                    printf("计数排序在%d个数组%d个数据所用时间%f\n",N,count,useTime);
                    printf("数据储存在RadixCountSort.txt\n");
                    break;
                case 6:
                    printf("未实现\n");
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
