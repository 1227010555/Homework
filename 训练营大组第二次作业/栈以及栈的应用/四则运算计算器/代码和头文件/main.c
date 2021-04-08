#include "FourFundamentalRules.h"

int main() {
	char a[SIZE] = {0};
	int i = 0;
	float temp = 0;
	float j;

	DATA num;
	initStack(&num,0);

	DATA opt;
	initStack(&opt,0); 
		
	printf("������:\n");
	scanf("%s",a);

	//ѭ������a[] 
	while(a[i] != '\0' || isEmptyStack(&opt) != 1) {
		
		//�ַ������int���������ҿ���Ϊ��λ�� 
		if(a[i] >= '0' && a[i] <= '9') {
			temp = temp * 10 + a[i] - '0';
			i++;
		
		//����������ջ 
			if(a[i] < '0' || a[i] > '9') {
				pushStack(&num,temp);
				temp = 0;
			}
		} else {
			
			//ջ��Ϊ'('�����ȼ����ڷ���ջ�����ȼ��������ջ
			if((a[i] != '\0' && isEmptyStack(&opt)) || (a[i] != ')' && getTopStack(&opt) == '(') || (judge(a[i]) > judge(getTopStack(&opt)))) {
				pushStack(&opt,a[i]);
				i++;
				continue;
			}
			
			//')'��������ջ��'(' ,'('��ջ 
			if(a[i] == ')' && getTopStack(&opt) == '(') {
				popStack(&opt);
				i++;
				continue;
			}

			//�����Ż����ȼ����ڷ���ջ�����㲢������ջ 
			if(a[i] == '\0' || a[i] == ')' || judge(a[i]) <= judge(getTopStack(&opt))) {
				switch (popStack(&opt)) {
					case '*' : {
						pushStack(&num,popStack(&num)*popStack(&num));
						break;
					}
					case '/': {
						j = popStack(&num);
						pushStack(&num,popStack(&num)/j);
						break;
					}
					case '+': {
						pushStack(&num,popStack(&num)+popStack(&num));
						break;
					}
					case '-': {
						j = popStack(&num);
						pushStack(&num,popStack(&num)-j);
						break;
					}
					default: {
						break;
					}
				}
				continue;
			}
		}
	}
	printf("\n%s = %d\n",a,popStack(&num));
	system("pause");
	return 0;
}
