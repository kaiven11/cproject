#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h> //?
#include <string.h>  //?
#include <unistd.h>
#include <stdlib.h>



int main(void){

    int connectfd = socket(AF_INET,SOCK_STREAM,0);

    //server 地址

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));//修改处
    serveraddr.sin_family = AF_INET;
    // serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr);
    serveraddr.sin_port = htons(10000);//修改出

    connect(connectfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));

    char *buffer = "hellow ni hao !";
    write(connectfd,buffer,strlen(buffer));
    char recvbuf[1024] ={0};
    read(connectfd,recvbuf,100);
    printf("recv message %s",recvbuf);
    close(connectfd);




    return 0;
}
