#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> //?
#include <string.h>  //?
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include <stdio.h>
#include <sys/epoll.h>

int main(void){

    int lfd = socket(AF_INET,SOCK_STREAM,0);
    //bind
    struct sockaddr_in serveraddr;
    serveraddr.sin_family =AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port =htons(10000);
    bind(lfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

    //listen

    listen(lfd,20);

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    //创建文件字符表

    int efd = epoll_create(2000);
    //结构体
    struct epoll_event watchfd[2000];
    //临时变量

    struct epoll_event ev;
    ev.data.fd=lfd;
    ev.events = EPOLLIN;//读事件

    int ret = epoll_ctl(efd,EPOLL_CTL_ADD,lfd,&ev);
    if (ret<0)
    {
        /* code */
        perror("creat fd error!");
    }

    while (1)
    {   
        //挂在跟节点

      
        
        //接受请求
        int value = epoll_wait(efd,watchfd,2000,-1);
       
        for (int i = 0; i < value; i++)
        {   
            int checkfd = watchfd[i].data.fd;
            if(checkfd==lfd){

                int confd = accept(lfd,(struct sockaddr *)&client_addr,&len);
                ev.data.fd=confd;
                ev.events=EPOLLIN;
                epoll_ctl(efd,EPOLL_CTL_ADD,confd,&ev);

            }
            else{
                //这里没有排除其他事件

                // if(!all[i].events & EPOLLIN)
				// {
				// 	continue;
                // }

                char buffer[1024]={0};
                int readlen =read(checkfd,buffer,sizeof(buffer));
                if (readlen==0)
                {
                    perror("remote closed!");
                    epoll_ctl(efd,EPOLL_CTL_DEL,checkfd,NULL);//将watch[i]--》null
                    close(checkfd);
                    
                }
                else if(readlen>0)
                {
                    printf("recv message:%s",buffer);
                    send(checkfd,buffer,strlen(buffer),0);

                }
                else
                {
                    perror("read error!");
                    // exit(1);
                }

            }
        }
        
        

        
    }
    
    return 0 ;

}