

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

pthread_mutex_t lock;
pthread_t tid[2];
int counter=0;

void* fun(void *);


int main()
{
    int error,i=0;
    error=pthread_mutex_init(&lock,NULL);
    if(error!=0)
    {
        printf("Mutex is not intialized:%d",error);
        exit(0);
    }

    while(i<2)
    {
        error=pthread_create(&tid[i],NULL,&fun,NULL);

        if(error!=0)
            printf("Thread is not created properly:%d",error);
        i++;
    }

    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);

    pthread_mutex_destroy(&lock);
    return 0;
    
}


void* fun(void *arg)
{
    pthread_mutex_lock(&lock); 
    unsigned long i = 0; 
    counter += 1; 
    printf("\n Job %d has started\n", counter); 
  
    for (i = 0; i < (0xFFFFFFFF); i++) 
        ; 
  
    printf("\n Job %d has finished\n", counter); 
  
    pthread_mutex_unlock(&lock); 

    return NULL;
}