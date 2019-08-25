#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include<unistd.h>



int main(void){
      
      //在创建 子进程前 先打开fifo文件
      int fd = open("./testfifo",O_RDONLY);
      
      
      char buffer2[256];
      
      int ret_size = read(fd,buffer2,sizeof(buffer2));
      
      while(1){
      memset(buffer2,0x00,sizeof(buffer2)); 
      ret_size = read(fd,buffer2,sizeof(buffer2));
      write(STDOUT_FILENO,buffer2,sizeof(buffer2));
      sleep(1);     
      	}	
      


      
      
 	return 0;       
           
      


    



}
