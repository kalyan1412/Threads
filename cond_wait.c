

// C program to implement cond(), signal() 
// and wait() functions 
#include <pthread.h> 
#include <stdio.h> 
#include <unistd.h> 

// Declaration of thread condition variable 
pthread_cond_t cond1;

// declaring mutex 
pthread_mutex_t lock;
int done = 1; 

// Thread function 
void* foo() 
{ 

	// acquire a lock 
	pthread_mutex_lock(&lock); 
    printf("Hi\n");
     printf("Thread id=%u\n",pthread_self());
	if (done == 1) { 

		// let's wait on conition variable cond1 
		done = 2; 
		printf("Waiting on condition variable cond1\n"); 
		pthread_cond_wait(&cond1, &lock); 
        printf("Unblocked\n");
	} 
	else { 

		// Let's signal condition variable cond1 
		printf("Signaling condition variable cond1\n"); 
		pthread_cond_signal(&cond1); 
        printf("Its done\n");
	} 

	// release lock 
	pthread_mutex_unlock(&lock); 

	printf("Returning thread\n"); 

	return NULL; 
} 

// Driver code 
int main() 
{ 
	pthread_t tid1, tid2; 
    int error;
    error=pthread_mutex_init(&lock,NULL);
    if(error!=0)
        printf("Mutex Intilization is failed\n");  

    error=pthread_cond_init(&cond1,NULL);
    if(error!=0)
        printf("Condtion Intilization is failed\n");

	// Create thread 1 
	pthread_create(&tid1, NULL, foo, NULL); 
    printf("Thread id1=%u\n",tid1);

	// sleep for 1 sec so that thread 1 
	// would get a chance to run first 
	sleep(1); 

	// Create thread 2 
	pthread_create(&tid2, NULL, foo, NULL); 
    printf("Thread id2=%u\n",tid2);
    sleep(1); 
	// wait for the completion of thread 2 
    pthread_join(tid1, NULL); 
	pthread_join(tid2, NULL); 

	return 0; 
} 
