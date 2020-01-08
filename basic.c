

// Basic program for threads

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

void* fun(void *argc);

int main()
{
    pthread_t thread_id;

   

    int error;
    printf("Thread id=%u\n",thread_id);
    error=pthread_create(&thread_id,NULL,*fun,NULL);
    printf("Thread id=%u\n",thread_id);
    if(error!=0)
    {
        printf("Thread is not created succesfully:");
    }

    pthread_join(thread_id,NULL);
    return 0;
}

void* fun(void *argc)
{
   // sleep(2);
     printf("Thread id=%u\n",pthread_self());
    printf("In fun\n");    
    return NULL;
}