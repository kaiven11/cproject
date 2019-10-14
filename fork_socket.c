#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h> //?
#include <string.h>  //?
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>






void recycle(int num){

    while (waitpid(-1,NULL,WNOHANG)>0)
    {
        /* code */
    }
    


}
int main(){
    

    //创建捕捉信号
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = recycle;
    sigemptyset(&act.sa_mask);  

    


    //创建socket

    int lfd = socket(AF_INET,SOCK_STREAM,0);


    //bind
    struct sockaddr_in serveraddr;
    serveraddr.sin_family =  AF_INET;
    serveraddr.sin_port = htons(10000);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");


    int retvalue = bind(lfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if (retvalue<0)
    {
        /* code */
        perror("bind address error!");
        exit(100);
    }
    

    //listen

    int ret = listen(lfd,20);
    if (ret<0)
    {
        /* code */
        perror("listen error!");
    }
    



    //accept循环接受连接，当有描述符返回时，就直接fork一个子进程处理
    struct sockaddr_in client_addr;
    int client_len = sizeof(client_addr);
    while (1)
    {   
        
        int confd = accept(lfd,(struct sockaddr  *)&client_addr,&client_len);
        if (confd<0)
        {
           continue;
        }

        pid_t pid = fork();
        if (pid==0)
        {
            /*子进程 */
            //关闭不需要的文件描述符
            close(lfd);

            while (1)
            {
                /* 处理数据 */
                char recive_buffer[1024]={0};
                int recivelen = read(confd,recive_buffer,sizeof(recive_buffer));
                if (recivelen==0)
                {
                    /* 接受数据为零，表示对方关闭链接 */
                    close(confd);
                    break;//修改了这里
                }
                else if (recivelen==-1)
                {
                    /* error */
                    perror("connect error\n");
                    exit(2);
                }
                
                else{
                printf("recive message:%s\n",recive_buffer);

                write(confd,recive_buffer,recivelen);
                
                }

               
            }

            
            

           
        }
        
        else if (pid>0)
        {
            /* 父进程逻辑代码 */
            //回收子进程即可
            //wait or waitpid 这里用信号实现

            //int sigaction(int signum, const struct sigaction *act,
                    //  struct sigaction *oldact);

           close(confd);//关闭多余描述符
           sigaction(SIGCHLD,&act,NULL);
        }
        

        

    }
    

    return 0;
}



