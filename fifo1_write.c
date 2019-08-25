#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include<unistd.h>



int main(void){
      
      //在创建 子进程前 先打开fifo文件
      int fd = open("./testfifo",O_WRONLY);
      char buffer1[256]; 
      int i =1;
      while(i){
	memset(buffer1,0x00,sizeof(buffer1));
      sprintf(buffer1,"this is from 1 process %04d",i++);
      write(fd,buffer1,strlen(buffer1));
      sleep(1);


      	}


      close(fd);
      
 	return 0;       
           
}
