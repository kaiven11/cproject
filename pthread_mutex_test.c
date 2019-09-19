#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void * handler1(void *args){

while(1){
   pthread_mutex_lock(&mutex);
   printf("%s\n","hello world!");
   pthread_mutex_unlock(&mutex);
   sleep(rand()%3);
   printf("%d\n",rand()%3);
}


}


void * handler2(void *args){

while(1){
  pthread_mutex_lock(&mutex);
  printf("%s\n","HELLO WORLD!");
  pthread_mutex_unlock(&mutex);
  sleep(rand()%3);
 
}


}






int main(void){

    srand((unsigned)time(NULL));
    pthread_t p1,p2;
    pthread_create(&p1,NULL,handler1,NULL);
    pthread_create(&p2,NULL,handler2,NULL);

    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_exit(NULL);






return 0;
}
