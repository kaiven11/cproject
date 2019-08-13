#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>



int add(int a, int b) {

	return a + b;
}


int minus(int a, int b) {
	return a - b;
}



int cheng(int a, int b) {

	return a * b;
}


int div(int a, int b) {
	return a / b;
}


//»Øµ÷º¯Êý
void getresult(int a, int b, int(*compute)(int a,int b)) {

	int temp1 = a;
	int temp2 = b;

	int retvalue = compute(temp1, temp2);

	printf("the result is :%d", retvalue);

}


int main(void) {

	typedef int(*fun) (int a, int b);
	fun consult = NULL;
	int a;
	char b;
	int c;
	


	scanf("%d %d %c", &a,&c,&b);
	printf("%d\n",a);
	printf("%c\n",b);
	printf("%d\n",c);
	switch (b)
	{
		
	case '+':
	 consult = add;
	break;
	
	case '-':
	consult = minus;
	break;
	case '*':
	consult = cheng;
	break;
	case '/':
	consult = div;
	break;

	default:
		printf("%s", "you had put error!");
		break;
	}


	getresult(a, c, consult);




	return 0;


}



