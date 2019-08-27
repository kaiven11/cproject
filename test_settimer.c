#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
//用setitimer 实现alarm的功能

struct timeval p1;
struct timeval p2;
struct itimerval args;

void prinf_sinal(int a){

printf("捕获到了--->%d信号\n",a);

}



int main(void){
	 struct itimerval *args;
    
         args = malloc(sizeof(struct itimerval));
	 args->it_interval.tv_sec = 3;
	 args->it_interval.tv_usec= 0;

	 args->it_value.tv_sec = 3;
	 args->it_value.tv_usec = 0;
         signal(SIGALRM,prinf_sinal); 
	 setitimer(ITIMER_REAL,args,NULL);//此时的效果应该是初始5秒后开始及时，之后每隔3秒进行动作
         //这里捕获信号
	 //signal(14,prinf_sinal);

         while(1){
	 
	 printf("i am happy!\n");
         sleep(1);
         
	 }


}
