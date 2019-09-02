#include <stdio.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/time.h>
#include <signal.h>
//通过信号进行父与子之间的信息传递
//通过signal 提供的自定义信号
//父与子 内部的数据是不共享的，读时共享，写时复制。

int i =0;
int flag =0;
void handler_parent(int num){
        sleep(1);
	flag =1;
	printf("from parent %d\n",i);
	i+=2;
}

void handler_son(int num){

    sleep(1);
    flag=1;
    printf("from son:%d\n",i);
    i+=2;

}


int main(void){

	pid_t pid = fork();
        struct sigaction act;
	act.sa_flags =0;
	//act.sa_handler=handler;
	sigemptyset(&act.sa_mask);
        i=1;
	if (pid>0){
        act.sa_handler = handler_parent;
        sigaction(SIGUSR1,&act,NULL);

        while (1){
	//i++;
	if (flag == 1){
	kill(pid,SIGUSR2);
	flag =0;
		}
	}
	
	}
	else if(pid==0){
        i=2;
        act.sa_handler=handler_son;
	sigaction(SIGUSR2,&act,NULL);
	flag =1;
	while(1){
	if (flag ==1){
	kill(getppid(),SIGUSR1);
	flag =0;
		}
	}
	
	
	}
 


   return 0;

}
