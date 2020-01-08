

// Printing Even and Odd numbers using threads

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

pthread_mutex_t lock; // Declartion of Mutex lock
pthread_cond_t cond;  // Declartion of Condtion variable

int x=1; // Global variable

void* even(void *arg);
void* odd(void *arg);

int main()
{
    pthread_t tid1,tid2;
    int error;
    error=pthread_mutex_init(&lock,NULL);
    if(error!=0)
        printf("Mutex Intilization is failed\n");
    error=pthread_cond_init(&cond,NULL);
    if(error!=0)
        printf("Condtion Intilization is failed\n");
    pthread_create(&tid1,NULL,&even,NULL);
    pthread_create(&tid2,NULL,&odd,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}


void* even(void *arg)
{
    printf("Even\n");
    pthread_mutex_lock(&lock);
    while(x<=10)
    {
        printf("[[[[]]]\n");
        if(x%2==0)
        {
            printf("%d is even\n",x);
            x++;
            
        }
        else
        {
            printf("----------\n");
             pthread_cond_wait(&cond,&lock);
             printf("/////////\n");
        }

         pthread_cond_signal(&cond);
    
    }  
     pthread_mutex_unlock(&lock);
}

void* odd(void *arg)
{
    printf("Odd\n");
    pthread_mutex_lock(&lock);
    while(x<=10)
    {
        if(x%2!=0)
        {
            printf("%d is odd\n",x);
            x++;
           
        }
        else
        {
            printf("*************\n");
            pthread_cond_wait(&cond,&lock);
              printf("&&&&&&&&&\n");
        }
         printf("###########\n");
         pthread_cond_signal(&cond);    
    }    
    pthread_mutex_unlock(&lock);
}