#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> //?
#include <string.h>  //?
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include <stdio.h>

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

    //文件描述表
    fd_set reads,temp;
    FD_ZERO(&reads);//初始化
    FD_SET(lfd,&reads);
    
    int maxfd = lfd;//修改处

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    

    while (1)
    {   temp = reads;
        select(maxfd+1,&temp,NULL,NULL,NULL);
        if (FD_ISSET(lfd,&temp))
        {
            int confd = accept(lfd,(struct sockaddr *)&client_addr,&len);
            FD_SET(confd,&reads);//加到原来的文件描述符中
            maxfd = maxfd < confd ? confd : maxfd;

        }
    
        //reads 里除了lfd之外全都是连接套接字
        //循环reads，然后找到标志位为1的
        for (int  i = lfd+1; i < maxfd+1; i++)
        {
            if (FD_ISSET(i,&temp))
            {
                //缓冲区收到消息
                char buffer[1024]={0};
                int readlen =read(i,buffer,sizeof(buffer));
                if (readlen==0)
                {
                    perror("remote closed!");
                    close(i);
                    FD_CLR(i,&reads);//从原来保留的描述符中删除
                }
                else if(readlen>0)
                {
                    printf("recv message:%s",buffer);
                    write(i,buffer,strlen(buffer));

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