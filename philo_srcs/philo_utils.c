#include "philo.h"

long long	get_time(void)
{
	struct timeval	timer;
	long long		result;

	gettimeofday(&timer, NULL);
	result = (long long)timer.tv_sec * 1000000;
	result = result + (long long)timer.tv_usec;
	result = result / 1000;
	return (result);
}