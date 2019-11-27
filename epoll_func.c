/*
 * @Author: mikey.zhaopeng 
 * @Date: 2019-11-10 04:28:50 
 * @Last Modified by:   mikey.zhaopeng 
 * @Last Modified time: 2019-11-10 04:28:50 
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include <stdio.h>
#include <sys/epoll.h>
#include "epoll_func.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include<sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

#define MAX_EVENTS 2000



struct mapping maps[]={
    {"html","text/html"},
    {"img","image/jpeg"},
    {"mp4","video/mp4"},
    {"bmp","image/bmp"},
    {"gif","image/gif"},
    {"ico","image/x-icon"},
    {"avi","video/avi"},
    {"css","text/css"},
    {"dll","application/x-msdownload"},
    {"mp3","audio/mp3"},
    {"mpg","video/mpg"},
    {"png","image/png"},
    {"ppt","application/vnd.ms-powerpoint"},
    {"wmv","video/x-ms-wmv"},


};
struct epoll_event ev, watchfd[MAX_EVENTS];

int createlfd(int port){

    int lfd = socket(AF_INET,SOCK_STREAM,0);
    int optval = 1; 
    setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));
    
    chdir("/root/cproject/httpserver");

    struct sockaddr_in serveraddr;
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr("0.0.0.0");
    serveraddr.sin_port=htons(port);
    bind(lfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
    //监听服务
    listen(lfd,20);
    return lfd;
}


//添加fd到时间树上,返回二叉树
int addfdtoevets(int efd,int lfd){
    
    ev.events=EPOLLIN | EPOLLET;
    ev.data.fd=lfd;
    epoll_ctl(efd,EPOLL_CTL_ADD,lfd,&ev);
    return efd;
}

int runserver(int port){
    //开启监听服务
    int efd = epoll_create(MAX_EVENTS);

    int lfd = createlfd(port);
    addfdtoevets(efd,lfd);
    
    //根据内核返回的信息进行处理
   while (1)
   {
    int value = epoll_wait(efd,watchfd,2000,-1);
  
    for (int  i = 0; i < value; i++)
    {
        //判断是否时客户端的读事件
         
        int checkfd = watchfd[i].data.fd;            
        if (checkfd == lfd)
        {
            //接受请求
            struct sockaddr_in clientaddr;
            int len = sizeof(clientaddr);
            int confd = accept(lfd,(struct sockaddr *)&clientaddr,&len);
            
            int flag = fcntl(confd, F_GETFL);
            flag |= O_NONBLOCK;
            fcntl(confd, F_SETFL, flag);
            addfdtoevets(efd,confd);
           
        }

        else
        {   
             if(! watchfd[i].events & EPOLLIN)
				{
					continue;
                }

               printf("the request is comming!!\n");
               parsecontent(checkfd,efd);  
          
        }

    }

   }
}


// 16进制数转化为10进制
int hexit(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    return 0;
}

/*
 *  这里的内容是处理%20之类的东西！是"解码"过程。
 *  %20 URL编码中的‘ ’(space)
 *  %21 '!' %22 '"' %23 '#' %24 '$'
 *  %25 '%' %26 '&' %27 ''' %28 '('......
 *  相关知识html中的‘ ’(space)是&nbsp
 */
void encode_str(char* to, int tosize, const char* from)
{
    int tolen;

    for (tolen = 0; *from != '\0' && tolen + 4 < tosize; ++from) 
    {
        if (isalnum(*from) || strchr("/_.-~", *from) != (char*)0) 
        {
            *to = *from;
            ++to;
            ++tolen;
        } 
        else 
        {
            sprintf(to, "%%%02x", (int) *from & 0xff);
            to += 3;
            tolen += 3;
        }

    }
    *to = '\0';
}


void decode_str(char *to, char *from)
{
    for ( ; *from != '\0'; ++to, ++from  ) 
    {
        if (from[0] == '%' && isxdigit(from[1]) && isxdigit(from[2])) 
        { 

            *to = hexit(from[1])*16 + hexit(from[2]);

            from += 2;                      
        } 
        else
        {
            *to = *from;

        }

    }
    *to = '\0';

}


char * send_dir(int confd,char * Path, int flag){
    printf("senddir path %s\n",Path);

    
    char buffer[8096] ="<html><body>";
    char tmp[1024]={0};
    struct dirent *direntp;
    char  filepath[1024]={0};


 
 
    DIR* sdir = opendir(Path);
    //如果返回NULL，表示打开目录失败
    if (!sdir)
    {
        //这里表示是文件
        //发送文件到客户端
        perror("can't open the file!\n");
        return NULL ;
       
    }

    


    sprintf(buffer+strlen(buffer),"%s","<table>");
    while( (direntp = readdir(sdir)) != NULL )
    {   
        if( strcmp(direntp->d_name,".")==0||strcmp(direntp->d_name,"..")==0)
            continue;


         char * name = direntp->d_name;
            char enstr[1024]={0};
            encode_str(enstr, sizeof(enstr), name);
        if (direntp->d_type & DT_DIR)
        {
            /* code */
           
           
            sprintf(buffer+strlen(buffer),"<tr><td><a href=%s/>%s</a></td></tr>",name,name);
            

        }


        else{
        
            sprintf(buffer+strlen(buffer),"<tr><td><a href=%s>%s</a></td></tr>",name,name);
        }
        
    }
    
    sprintf(buffer+strlen(buffer),"%s","</table>");
    sprintf(buffer+strlen(buffer),"%s","</body></html>");
    char * ret = buffer;
    closedir(sdir); 
    return ret; 


}




//发送响应头
void send_response_header(char * filetype ,long content_length,int confd){

    char response_header[1024]={0};
    sprintf(response_header,"HTTP/1.1 200 Ok\r\n");
    write(confd,response_header,strlen(response_header));
    sprintf(response_header,"content-Type:%s\r\n",filetype);
    sprintf(response_header+strlen(response_header),"Content-Length:%ld\r\n",content_length);
    write(confd,response_header,strlen(response_header));
    send(confd, "\r\n", 2, 0);
}


//计算文件大小



int get_file_size(int f)
{
    struct stat st;
    fstat(f, &st);
    return st.st_size;
}



//计算字符串长度
int countlengh(char * str){
    
    int length = 0;

    while (*str)
    {
        length++;
        str++;
    }
    
    return length;

}


//send file if the request for file

void  send_file(int confd,const char * path){

   

    printf("the file path is %s\n",path);
    
   

    int fd = open(path,O_RDONLY);
    
    if (fd==-1)
    {
        /* code */
        perror("Not Found The File,Please Check Path!");
        return ;
    }

    char buffer[4096]={0};
    int len=0;

    while ((len=read(fd,buffer,sizeof(buffer)))>0)
    {
        write(confd,buffer,len);
    }
    if (len==-1)
    {
        perror("read file error!");
        exit(1);
    }
    close(fd);
    



    

}


char * orgnizefiletype(char* filename){

    printf("filename is %s\n",filename);
    // char * name = strtok(filename,".");
    // char * filetype = strtok(NULL,filename);

    while (*filename)
    {
        if (*filename=='.')
        {
            break;
        }
        
        filename++;
    }
    filename+=1;
    


    printf("file type is %s\n",filename);
    for (int i = 0; i < sizeof(maps)/sizeof(maps[0]); i++)
    {    
        printf("maps is %s\n",maps[i].filetype);
        if (!strcmp(maps[i].filetype,filename))
        {
            return maps[i].contentname;
        }
        
    }
    
    return "text/plain; charset=utf-8";

   
}

void parsecontent(int confd,int efd){
            
   //
            char buffer[1024]={0};
            FILE * handler = fdopen(confd,"r"); 
            // int readlen= read(confd,buffer,sizeof(buffer));
            char *header = fgets(buffer,1024,handler);
            if (!header)
            {
                /* code */
                return;
            }
            
            
            printf("%s\n",header);

            //解析头部

            /*

            请求方法，请求资源, 协议版本，
            */
            char* delim = " ";
            char* p;
            printf("method:%s\n", strtok(header, delim));
            //printf("method:%s\n", strtok(s, delim));
            
            char* uri = strtok(NULL, delim);
            decode_str(uri, uri);
            char* file = uri+1;
            printf("uri :%s\n",uri);

            char* protocal = strtok(NULL, delim);
            printf("protocal :%s\n", protocal);                
            //解析请求行
            int flag =0;

              if(strcmp(uri, "/") == 0)
                {
                    // file的值, 资源目录的当前位置
                    file = "./";
                }
                if (!strcmp(uri,"/favicon.ico"))
                {
                    //如果两个值相等，则返回，不响应此请求；
                    return;
                }


            //判断是文件还是目录

            struct stat s_buf;
            stat(file,&s_buf);
           if(S_ISDIR(s_buf.st_mode)){
                printf("it is hrere..............\n");
                char * retval = send_dir(confd,file,flag);
                send_response_header("text/html",countlengh(retval),confd);
                //发送响应行
                write(confd,retval,countlengh(retval));
               
           }

           else{
               
                int   fp = open(file,O_RDWR);
                int size = get_file_size(fp);
                char  tmp[1024] ={0};
                strcpy(tmp,file);
                char * filetype = orgnizefiletype(tmp);
                printf("The Last FileType is %s\n",filetype);
                send_response_header(filetype,size,confd);
                send_file(confd,file);
                
           }
            
          
        


}











