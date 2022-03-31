#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>
#include<bits/types.h>
#include<unistd.h>
#include<errno.h>

static pthread_spinlock_t spinlock;
volatile int slock;


void *spinlockThread(void *t)
{
	int rc;
	int count =0;	
	printf("Entered thread %d,getting spinlock\n",(int *)1);

	rc = pthread_spin_lock(&spinlock);

	printf("%d thread unlock the spin lock\n",(int *)1);

	rc= pthread_spin_unlock(&spinlock);

	printf("%d thread complete\n",(int *)1);
	return NULL;
}

int main()
{
	int rc =0;
	pthread_t thread,thread1;
	if(pthread_spin_init(&spinlock,PTHREAD_PROCESS_PRIVATE)!=0)
		perror("init");
	printf("Main, get spin lock\n");
	rc = pthread_spin_lock(&spinlock);

	printf("Main, create the spinlock thread\n");
	rc = pthread_create(&thread,NULL,spinlockThread,(int *)1);

	printf("Main, wait a bit holding the spin lock\n");
	sleep(10);

	printf("Main, Now unlock the spin lock\n");
	rc = pthread_spin_unlock(&spinlock);

	if(rc==0)
	{
		printf("\n Main Thread Successfully unlocked\n");
	}
	else
	{
		printf("\n Main Thread unSuccessfully unlocked\n");
	}

	printf("Main wait for the thread to end\n");
	rc = pthread_join(thread,NULL);
	printf("main complete\n");
	return 0;

}
