//while executing write sudo ./executable_filename

#include<stdio.h>
#include<pthread.h>

void *my(void *i)
{
	printf("\nI am in %d thread\n",(int *)i);

}

main()
{

	pthread_t tid;
	struct sched_param param;
	int priority,policy,ret;

	ret = pthread_getschedparam (pthread_self(),&policy,&param);
	printf("\n----------------Main Thread--------------\n Policy : %d\t Priority : %d \n",policy,param.sched_priority);
	policy = SCHED_FIFO;
	param.sched_priority = 3;
	ret = pthread_setschedparam (pthread_self(),policy,&param);
	if(ret!=0)
	{
		perror("getschedparam");
	}
	
	ret = pthread_getschedparam (pthread_self(),&policy,&param);
	if(ret!=0)
	{
		perror("getschedparam");
	}
	printf("\n----------------Main Thread--------------\n Policy : %d\t Priority : %d \n",policy,param.sched_priority);
}
