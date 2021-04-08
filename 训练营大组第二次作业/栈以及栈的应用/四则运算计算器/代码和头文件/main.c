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
		
	printf("请输入:\n");
	scanf("%s",a);

	//循环遍历a[] 
	while(a[i] != '\0' || isEmptyStack(&opt) != 1) {
		
		//字符换算成int类型数据且可能为多位数 
		if(a[i] >= '0' && a[i] <= '9') {
			temp = temp * 10 + a[i] - '0';
			i++;
		
		//把数入数字栈 
			if(a[i] < '0' || a[i] > '9') {
				pushStack(&num,temp);
				temp = 0;
			}
		} else {
			
			//栈顶为'('或优先级大于符号栈顶优先级，入符号栈
			if((a[i] != '\0' && isEmptyStack(&opt)) || (a[i] != ')' && getTopStack(&opt) == '(') || (judge(a[i]) > judge(getTopStack(&opt)))) {
				pushStack(&opt,a[i]);
				i++;
				continue;
			}
			
			//')'遇到符号栈顶'(' ,'('出栈 
			if(a[i] == ')' && getTopStack(&opt) == '(') {
				popStack(&opt);
				i++;
				continue;
			}

			//将括号或优先级低于符号栈顶计算并入数字栈 
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
