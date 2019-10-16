#include <sys/types.h>
#include <pthread.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
//-----------------------
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> //?
#include <string.h>  //?
#include <unistd.h>

#define MAXVALUE 1024
char buffer[1024] = {0};
void * handler(void *arg){
    int confd = *(int*)arg;
    while (1)
    {   
        
        int readlen = read(confd,buffer,sizeof(buffer));
        if (readlen==0)
        {
            close(confd);
            break;
        }
        else if (readlen==-1)
        {
            perror("read error!\n");
            pthread_exit(NULL);
        }
        else
        {
            printf("recv buffer : %s\n",buffer);
            write(confd,buffer,sizeof(buffer));
           
            
        }
         
    }
}


int main(){

    //lfd
    int lfd = socket(AF_INET,SOCK_STREAM,0);

    //bind

    struct sockaddr_in serversocket;
    serversocket.sin_family = AF_INET;
    serversocket.sin_port =htons(10000);
    serversocket.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret = bind(lfd,(struct sockaddr *)&serversocket,sizeof(serversocket));
    if (ret<0)
    {
        /* code */
        perror("bind error!");
        exit(2);
    }

    //listen

    int value = listen(lfd,20);
    if (value<0)
    {
        /* code */
        perror("listen error");
        exit(1);
    }


    struct sockaddr_in client_addr;
    client_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    client_addr.sin_family=AF_INET;
    client_addr.sin_port = htons(10000);

    socklen_t len = sizeof(client_addr);
    int i=0;
    pthread_t pt[MAXVALUE];
    while (i<MAXVALUE)
    {
        /* code */
       

        int connectfd = accept(lfd,(struct sockaddr *)&client_addr,&len);
        pthread_create(&pt[i],NULL,handler,&connectfd);
        pthread_detach(pt[i]);
        i++;

    }
    
    printf("herer...");
    








    


return 0 ;

}