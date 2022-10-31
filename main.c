#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


int mail = 0;
pthread_mutex_t mutex;

void	*routine()
{
	for (int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mail++;
		pthread_mutex_unlock(&mutex);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	pthread_t	thread[4];
	int i;
	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < 4)
	{
		if (pthread_create(&thread[i], NULL, &routine, NULL) != 0)
		{
			printf ("failed to create thread\n");
			return (0);
		}
		i++;
		printf ("Thread %d has started\n", i);
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(thread[i], NULL);
		i++;
		printf ("Thread %d has finished\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("num of mails %d\n", mail);
}
