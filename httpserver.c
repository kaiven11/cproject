#include <stdio.h>
#include <stdlib.h>
#include "epoll_func.h"

int main(void){

    // if (argc<2)
    // {
    //     printf("Useage ./a.out port");
    // }

    // int port = atoi(argv[1]);
    // printf("%s",argv[1]);
    // printf("the port is %d ",port);
    //启动服务

    int port = 10000;
    runserver(port);

    // printf("%d",port);
   
    return 0;
    
}