#include "qgsort.h"

void insertSort(int *a,int n) {
    int j=0,i=0,k=0,temp=0;
    for (i = 1; i < n; i++) {
        j=i-1;
        if(*(a+j)>*(a+i)) {
            for(k=i; k>0; k--) {
                if(*(a+k-1)>*(a+k)) {
                    temp=*(a+k);
                    *(a+k)=*(a+k-1);
                    *(a+k-1)=temp;
                }
            }
        }
    }
    FILE *fp=fopen("insertSort.txt","a+" );
    for(i =0; i < n; i++)
        fprintf(fp,"%d\n",*(a+i));
    fprintf(fp,"----------\n");
    fclose(fp);
}

void MergeArray(int *a,int begin,int mid,int end) {
    int i = begin;
    int j = mid + 1;
    int t = 0;
    int temp[200000];
    while(i <= mid && j<= end) {
        if(*(a+i) <= *(a+j)) {
            temp[t] = *(a+i);
            i++;
            t++;
        } else {
            temp[t] = *(a+j);
            j++;
            t++;
        }
    }
    while(i <= mid) {
        temp[t] = *(a+i);
        t++;
        i++;
    }
    while(j <= end) {
        temp[t] = *(a+j);
        j++;
        t++;
    }
    t = 0;
    int tempLeft = begin;
    while(tempLeft <= end) {
        *(a+tempLeft) = temp[t];
        t++;
        tempLeft++;
    }
}

void MergeSort(int *a,int begin,int end,int flag) {
    if(begin < end) {
        int mid = (begin + end) / 2;
        MergeSort(a, begin, mid,-1);
        MergeSort(a, mid + 1, end,-1);
        MergeArray(a, begin, mid, end);
    }
    int i;
    if(flag==0) {
        FILE *fp=fopen("MergeSort.txt","a+" );
        for(i =0; i < end+1; i++)
            fprintf(fp,"%d\n",*(a+i));
        fprintf(fp,"----------\n");
        fclose(fp);
    }
}

void QuickSort_Recursion(int *a, int begin, int end,int flag) {
    if (begin < end) {
        int standard = Partition(a, begin, end);
        QuickSort_Recursion(a, begin, standard - 1,-1);
        QuickSort_Recursion(a, standard + 1, end,-1);
    }
    int i;
    if(flag==0) {
        FILE *fp=fopen("QuickSort_Recursion.txt","a+" );
        for(i =0; i < end+1; i++)
            fprintf(fp,"%d\n",*(a+i));
        fprintf(fp,"----------\n");
        fclose(fp);
    }
}

void QuickSort(int *a,int size) {

}

int Partition(int *a, int begin, int end) {
    int key = *(a+begin);
    while (begin < end) {
        while (begin < end && *(a+end) >= key) {
            end--;
        }
        if (begin < end) {
            *(a+begin) = *(a+end);
        }
        while (begin < end && *(a+begin) <= key) {
            begin++;
        }
        if (begin < end) {
            *(a+end) = *(a+begin);
        }
    }
    *(a+begin) = key;
    return begin;
}

void CountSort(int *a, int size , int max) {
    int *c = (int *)malloc(sizeof(int) * (max + 1));
    int b[size];
    int i;
    for(i = 0; i <= max; i++)
        c[i] = 0;
    for(i = 0; i < size; i++)
        c[*(a+i)]++;
    for(i = 1; i <= max; i++)
        c[i] = c[i] + c[i - 1];
    for(i = size - 1; i >= 0; i--) {
        b[c[*(a+i)] - 1] = *(a+i);
        c[*(a+i)]--;
    }
    FILE *fp=fopen("CountSort.txt","a+" );
    for(i =0; i < size; i++)
        fprintf(fp,"%d\n",b[i]);
    fprintf(fp,"----------\n");
    fclose(fp);
}

void RadixCountSort(int *a,int size,int digit) {
    int i=0,j=0;
    int count[10];
    int temp[size];
    for(i=0; i<digit; i++) {
        if(i==0) {
            for(j=0; j<10; j++)
                count[j]=0;
            for(j=0; j<size; j++)
                count[*(a+j)%(10)]++;
            for(j=1; j<10; j++)
                count[j]=count[j]+count[j-1];
            for(j=size-1; j>=0; j--) {
                temp[count[*(a+j)%10] - 1] = *(a+j);
                count[*(a+j)%10]--;
            }
        } else if(i%2==0) {
            for(j=0; j<10; j++)
                count[j]=0;
            for(j=0; j<size; j++)
                count[((*(a+j))/(10*i))%10]++;
            for(j=1; j<10; j++)
                count[j]=count[j]+count[j-1];
            for(j=size-1; j>=0; j--) {
                temp[count[((*(a+j))/(10*i))%10] - 1] = *(a+j);
                count[((*(a+j))/(10*i))%10]--;
            }
        } else if(i%2!=0) {
            for(j=0; j<10; j++)
                count[j]=0;
            for(j=0; j<size; j++)
                count[((*(temp+j))/(10*i))%10]++;
            for(j=1; j<10; j++)
                count[j]=count[j]+count[j-1];
            for(j=size-1; j>=0; j--) {
                a[count[((*(temp+j))/(10*i))%10] - 1] = *(temp+j);
                count[((*(temp+j))/(10*i))%10]--;
            }
        }
    }
    if(digit%2==0) {
        FILE *fp=fopen("CountSort.txt","a+" );
        for(i =0; i < size; i++)
            fprintf(fp,"%d\n",*(a+i));
        fprintf(fp,"----------\n");
        fclose(fp);
    } else if(i%2!=0) {
        FILE *fp=fopen("CountSort.txt","a+" );
        for(i =0; i < size; i++)
            fprintf(fp,"%d\n",*(temp+i));
        fprintf(fp,"----------\n");
        fclose(fp);
    }
}


